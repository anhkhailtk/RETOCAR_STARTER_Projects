#include <Arduino.h>

// ===================================================================
// TEST RIENG: CHI 2 NUT NHAN (BTN_START, BTN_MODE)
// In trang thai ra Serial khi nhan/tha. Khong lien quan buzzer.
// ===================================================================

// ===================== PIN MAP =====================
#define PIN_BTN_START 34   // pull-up ngoai tren board, nhan = LOW
#define PIN_BTN_MODE  35   // pull-up ngoai tren board, nhan = LOW

// ===================== BUTTON (copy tu file test) =====================
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
    Serial.println("\n[Test nut nhan] Bat dau...");

    btnStart.begin(PIN_BTN_START);
    btnMode.begin(PIN_BTN_MODE);

    Serial.println("Nhan tha BTN_START hoac BTN_MODE de xem ket qua tren Serial.");
}

void loop() {
    // In trang thai tho moi 300ms, de xac nhan wiring/pull-up dung
    static unsigned long lastDebug = 0;
    if (millis() - lastDebug > 300) {
        Serial.print("[DEBUG] BTN_START = ");
        Serial.print(digitalRead(PIN_BTN_START) == LOW ? "NHAN" : "NHA");
        Serial.print(" | BTN_MODE = ");
        Serial.println(digitalRead(PIN_BTN_MODE) == LOW ? "NHAN" : "NHA");
        lastDebug = millis();
    }

    if (btnStart.releasedEvent()) {
        Serial.println(">>> BTN_START released <<<");
    }

    if (btnMode.releasedEvent()) {
        Serial.println(">>> BTN_MODE released <<<");
    }
}