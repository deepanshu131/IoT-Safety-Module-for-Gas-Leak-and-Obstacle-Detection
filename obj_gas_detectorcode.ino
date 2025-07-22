#include <LiquidCrystal.h>

const int trigPin = 13;
const int echoPin = 11;
const int buzzPin = 10;
const int rLed = 12;
const int gLed = 3;
const int gas_sensor = A0;

int sthreshold = 200;

LiquidCrystal lcd(9, 8, 7, 6, 5, 4);

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(rLed, OUTPUT);
  pinMode(gLed, OUTPUT);
  pinMode(buzzPin, OUTPUT);
  pinMode(gas_sensor, INPUT);

  lcd.begin(16, 2);
  lcd.print("Starting...");
  delay(1000);
  lcd.clear();
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  float distance = (duration * 0.0343) / 2;
  int analogsensor = analogRead(gas_sensor);

  bool objectDetected = (distance > 10 && distance < 150);
  bool smokeDetected = (analogsensor > sthreshold);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Dist: ");
  lcd.print(distance);
  lcd.print(" cm");
  lcd.setCursor(0, 1);
  if (objectDetected && smokeDetected) {
    lcd.print("Obj+Smoke Alert");
    digitalWrite(rLed, HIGH);
    digitalWrite(gLed, HIGH);
    digitalWrite(buzzPin, HIGH);
  }
  else if (objectDetected) {
    lcd.print("Object Detected ");
    digitalWrite(rLed, HIGH);
    delay(250);
    digitalWrite(rLed, LOW);
    delay(250);
    digitalWrite(gLed, LOW);
    digitalWrite(buzzPin, HIGH);
  }
  else if (smokeDetected) {
    lcd.print("Smoke Detected  ");
    digitalWrite(rLed, LOW);
    digitalWrite(gLed, HIGH);
    delay(250);
    digitalWrite(gLed, LOW);
    delay(250);
    digitalWrite(buzzPin, HIGH);
  }
  else {
    lcd.print("Nothing Detected");
    digitalWrite(rLed, LOW);
    digitalWrite(gLed, LOW);
    digitalWrite(buzzPin, LOW);
  }

  delay(2000);
}

