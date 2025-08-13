#include <Arduino.h>

// LED bar pins
byte ledPins[] = {15, 2, 0, 4, 5, 18, 19, 21, 22, 23};
const int ledCount = sizeof(ledPins) / sizeof(ledPins[0]);

// Pushbutton pins (active LOW)
const int BTN_PLUS  = 25; 
const int BTN_MINUS = 26; 
const int BTN_MUTE  = 27; 

// Volume state
int volume = 5;        // start level
int savedVolume = 5;   // for mute toggle
bool muted = false;

void renderVolume() {
  int showCount = muted ? 0 : volume;
  for (int i = 0; i < ledCount; i++) {
    digitalWrite(ledPins[i], (i < showCount) ? HIGH : LOW);
  }

  // Print LED state to Serial Monitor
  Serial.print("LEDs ON: ");
  for (int i = 0; i < ledCount; i++) {
    Serial.print((i < showCount) ? "█" : "-");
  }
  Serial.print("   Volume: ");
  Serial.print(volume);
  Serial.print("   Saved: ");
  Serial.print(savedVolume);
  Serial.print("   Muted: ");
  Serial.println(muted ? "YES" : "NO");
}

void setup() {
  Serial.begin(115200);
  Serial.println("Volume Bar Test Starting...");

  for (int i = 0; i < ledCount; i++) {
    pinMode(ledPins[i], OUTPUT);
    digitalWrite(ledPins[i], LOW);
  }

  pinMode(BTN_PLUS,  INPUT_PULLUP);
  pinMode(BTN_MINUS, INPUT_PULLUP);
  pinMode(BTN_MUTE,  INPUT_PULLUP);

  renderVolume();
}

void loop() {
  // Increase volume
  if (digitalRead(BTN_PLUS) == LOW) {
    if (!muted && volume < ledCount) volume++;
    if (muted && savedVolume < ledCount) savedVolume++;
    Serial.println("Button PLUS pressed");
    renderVolume();
    delay(200);
  }

  // Decrease volume (min 1 LED)
  if (digitalRead(BTN_MINUS) == LOW) {
    if (!muted && volume > 1) volume--;
    if (muted && savedVolume > 1) savedVolume--;
    Serial.println("Button MINUS pressed");
    renderVolume();
    delay(200);
  }

  // Mute toggle
  if (digitalRead(BTN_MUTE) == LOW) {
    muted = !muted;
    if (muted) savedVolume = volume;
    else volume = savedVolume;
    Serial.println("Button MUTE pressed");
    renderVolume();
    delay(200);
  }
}
