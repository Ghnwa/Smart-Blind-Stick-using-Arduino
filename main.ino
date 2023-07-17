#include <toneAC.h>

const int ultrasonicPin = 2; 
const int leftLightPin = A0; 
const int rightLightPin = A1; 
const int pushButtonPin = 7; 
const int soundPin = 8;

void setup() {
  pinMode(ultrasonicPin, INPUT);
  pinMode(leftLightPin, INPUT);
  pinMode(rightLightPin, INPUT);
  pinMode(pushButtonPin, INPUT_PULLUP);
  pinMode(soundPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
    int ultrasonicDistance = getUltrasonicDistance();
    int leftLightValue = getLightValue(leftLightPin);
    int rightLightValue = getLightValue(rightLightPin);
    bool buttonState = isPushButtonPressed();
   
    if (buttonState == HIGH && !isPressed) {
        // turn on the system 
        playSound();
        isPressed = true;
        if (ultrasonicDistance < 30 || leftLightValue < 500 || rightLightValue < 500 ) {
          playSoundFront();
        }
    }
    else if (buttonState == HIGH && isPressed) {
        // turn off the system 
        isPressed = false;
    }
    delay(100);
}

int getUltrasonicDistance() { 
    digitalWrite(ultrasonicPin, LOW);
    delayMicroseconds(2);
    digitalWrite(ultrasonicPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(ultrasonicPin, LOW);
    long duration = pulseIn(ultrasonicPin, HIGH);
    int distance = duration * 0.034 / 2;
    return distance;
}

int getLightValue(int pin) {
    int lightValue = analogRead(pin);
      return lightValue;
}

bool isButtonPressed(int pin) {
    int buttonState = digitalRead(pin);
    if (buttonState == HIGH) {
      return true;
    } else {
      return false; 
    }
}

void playSound(int pin, int duration) {
    toneAC(pin, 2000, duration);
}
