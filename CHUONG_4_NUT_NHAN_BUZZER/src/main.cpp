#include <Arduino.h>
// ===================== PIN MAP =====================
#define PIN_BTN_START 34   // pull-up ngoai tren board, nhan = LOW
#define PIN_BTN_MODE  35   // pull-up ngoai tren board, nhan = LOW
#define PIN_BUZZER    15   // dieu khien qua transistor NPN

// ===================== BUZZER (LEDC, giong file test) =====================
#define CH_BUZZ         8
#define PWM_FREQ_BUZZ   2000   // tan so mac dinh (Hz)
#define PWM_RES_BUZZ    8      // do phan giai PWM cho buzzer

void buzzerInit() {
    ledcSetup(CH_BUZZ, PWM_FREQ_BUZZ, PWM_RES_BUZZ);
    ledcAttachPin(PIN_BUZZER, CH_BUZZ);
    ledcWriteTone(CH_BUZZ, 0); // tat
}

// Keu "times" tieng, moi tieng phat tan so freqHz trong durationMs, cach nhau gapMs
void buzzerBeep(int times, uint16_t freqHz = 2000, int durationMs = 150, int gapMs = 100) {
    for (int i = 0; i < times; i++) {
        ledcWriteTone(CH_BUZZ, freqHz);
        delay(durationMs);
        ledcWriteTone(CH_BUZZ, 0); // tat tieng
        if (i < times - 1) delay(gapMs);
    }
}

class Button {
public:
    void begin(int gpio, bool activeLow = true, bool usePullup = false) {
        pin = gpio;
        this->activeLow = activeLow;
        if (usePullup) pinMode(pin, INPUT_PULLUP);
        else            pinMode(pin, INPUT); // dung pull-up ngoai co san tren board
        lastReading = rawRead();
        debounced   = lastReading;
        lastChange  = millis();
    }

    // Goi thuong xuyen; tra ve trang thai da debounce (true = dang nhan)
    bool update() {
        bool r = rawRead();
        uint32_t now = millis();
        if (r != lastReading) {
            lastReading = r;
            lastChange = now;
        }
        if ((now - lastChange) > debounceMs) debounced = r;

        bool pressedNow = (activeLow ? !debounced : debounced);

        if (wasPressed && !pressedNow) {
            lastReleaseHoldMs = now - pressStart;
            wasPressed = false;
            releasedFlag = true; // one-shot, tieu thu boi releasedEvent()
        }
        if (!wasPressed && pressedNow) {
            wasPressed = true;
            pressStart = now;
        }
        return pressedNow;
    }

    // One-shot: true dung 1 lan khi VUA tha va da giu >= minHoldMs
    bool releasedEvent(uint16_t minHoldMs = 100) {
        update();
        if (releasedFlag && lastReleaseHoldMs >= minHoldMs) {
            releasedFlag = false;
            return true;
        }
        releasedFlag = false;
        return false;
    }

private:
    int pin = -1;
    bool activeLow = true;
    const uint16_t debounceMs = 25;
    bool lastReading = true;
    bool debounced = true;
    uint32_t lastChange = 0;

    bool wasPressed = false;
    uint32_t pressStart = 0;
    bool releasedFlag = false;
    uint32_t lastReleaseHoldMs = 0;

    bool rawRead() const { return digitalRead(pin); }
};

Button btnStart, btnMode;

// ===================== SETUP / LOOP =====================
void setup() {
    Serial.begin(9600); 
    delay(100);
    Serial.println("\n[Test nut + buzzer] Bat dau...");

    btnStart.begin(PIN_BTN_START);   // mac dinh: khong bat pull-up noi
    btnMode.begin(PIN_BTN_MODE);

    buzzerInit();

    Serial.println("Nhan tha BTN_START -> beep 1 tieng");
    Serial.println("Nhan tha BTN_MODE  -> beep 2 tieng");
}

void loop() {
    if (btnStart.releasedEvent()) {
        Serial.println("[BTN_START] released -> beep 1");
        buzzerBeep(1);
    }

    if (btnMode.releasedEvent()) {
        Serial.println("[BTN_MODE] released -> beep 2");
        buzzerBeep(2);
    }
}