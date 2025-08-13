#include <Arduino.h>

// --- CONFIG ---
#define DEBOUNCE_MS 12   // change this to find the minimum 

// LED bar pins (ESP32-safe set)
byte ledPins[] = {15, 2, 0, 4, 5, 18, 19, 21, 22, 23};
const int ledCount = sizeof(ledPins) / sizeof(ledPins[0]);

// Pushbuttons (active-LOW, using internal pull-ups)
const int BTN_PLUS  = 25;
const int BTN_MINUS = 26;
const int BTN_MUTE  = 27;

// Volume state
int volume = 5;
int savedVolume = 5;
bool muted = false;

// --- Simple non-blocking debouncer (per button) ---
struct Debounce {
  int pin;
  int lastReading;
  int stableState;            // debounced state
  unsigned long lastChange;   // last time the raw reading flipped
};

Debounce bPlus  {BTN_PLUS,  HIGH, HIGH, 0};
Debounce bMinus {BTN_MINUS, HIGH, HIGH, 0};
Debounce bMute  {BTN_MUTE,  HIGH, HIGH, 0};

bool pressedOnce(Debounce &d) {
  unsigned long now = millis();
  int raw = digitalRead(d.pin);
  if (raw != d.lastReading) {
    d.lastChange = now;            // reading changed: restart debounce timer
  }
  if ((now - d.lastChange) >= DEBOUNCE_MS && raw != d.stableState) {
    d.stableState = raw;           // debounced state just changed
    d.lastReading = raw;
    return (d.stableState == LOW); // report a press exactly once per physical press
  }
  d.lastReading = raw;
  return false;
}

// --- UI ---
void renderVolume() {
  int showCount = muted ? 0 : volume;
  for (int i = 0; i < ledCount; i++) {
    digitalWrite(ledPins[i], (i < showCount) ? HIGH : LOW);
  }
  Serial.print("LEDs: ");
  for (int i = 0; i < ledCount; i++) Serial.print((i < showCount) ? "█" : "-");
  Serial.print("  Vol: ");  Serial.print(volume);
  Serial.print("  Saved: ");Serial.print(savedVolume);
  Serial.print("  Muted: ");Serial.print(muted ? "YES" : "NO");
  Serial.print("  (DEBOUNCE_MS="); Serial.print(DEBOUNCE_MS); Serial.println(")");
}

void setup() {
  Serial.begin(115200);
  for (int i = 0; i < ledCount; i++) {
    pinMode(ledPins[i], OUTPUT);
    digitalWrite(ledPins[i], LOW);
  }

  pinMode(BTN_PLUS,  INPUT_PULLUP);
  pinMode(BTN_MINUS, INPUT_PULLUP);
  pinMode(BTN_MUTE,  INPUT_PULLUP);

  // Init debouncers with current readings
  bPlus.lastReading  = bPlus.stableState  = digitalRead(BTN_PLUS);
  bMinus.lastReading = bMinus.stableState = digitalRead(BTN_MINUS);
  bMute.lastReading  = bMute.stableState  = digitalRead(BTN_MUTE);

  renderVolume();
}

void loop() {
  if (pressedOnce(bPlus)) {
    if (!muted && volume < ledCount) volume++;
    if (muted && savedVolume < ledCount) savedVolume++;
    Serial.println("PLUS press detected");
    renderVolume();
  }

  if (pressedOnce(bMinus)) {
    if (!muted && volume > 1) volume--;
    if (muted && savedVolume > 1) savedVolume--;
    Serial.println("MINUS press detected");
    renderVolume();
  }

  if (pressedOnce(bMute)) {
    muted = !muted;
    if (muted) savedVolume = volume;
    else       volume = savedVolume;
    Serial.println("MUTE press detected (toggle mute)");
    renderVolume();
  }
}
