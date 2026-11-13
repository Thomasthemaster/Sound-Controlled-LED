
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

const int DOpin = 2;
const int AOpin = A7;
const int led = 12;

int smallDelay = 400;
int ledState = 0;
int soundMin;
int soundMax;
int soundRange;
int soundThreshold = 130;
int digitalVal;

void checkLED() {
  if (soundRange >= soundThreshold && ledState == 0) {
    digitalWrite(led, HIGH);
    ledState = 1;
    delay(smallDelay);
  }
  else if (soundRange >= soundThreshold && ledState == 1) {
    digitalWrite(led, LOW);
    ledState = 0;
    delay(smallDelay);
  }
  else {}
}

void setup() {
  lcd.init();
  lcd.backlight();

  pinMode(DOpin, INPUT);
  pinMode(AOpin, INPUT);
  pinMode(led, OUTPUT);

  digitalWrite(led, LOW);

  lcd.setCursor(0, 0);
  lcd.print("Sound Sensor");
  lcd.setCursor(0, 1);
  lcd.print("Initializing...");
  delay(1000);
  lcd.clear();
}

void loop() {

  // Start measuring
  soundMin = 1023;
  soundMax = 0;
  soundRange = 0;

  // Take 200 readings over approximately 100ms
  for (int i = 0; i < 200; i++) {

    int reading = analogRead(AOpin);

    if (reading < soundMin) {
      soundMin = reading;
    }

    if (reading > soundMax) {
      soundMax = reading;
    }

    checkLED();
    delayMicroseconds(500);
  }

  // Calculate peak-to-peak variation
  soundRange = soundMax - soundMin;

  // Read digital output
  digitalVal = digitalRead(DOpin);

  // Display results
  lcd.setCursor(0, 0);
  lcd.print("Range: ");
  lcd.print(soundRange);
  lcd.print("     ");

  lcd.setCursor(0, 1);
  lcd.print("LED: ");

  if (ledState == 1) {
    lcd.print("ON ");
  }
  else {
    lcd.print("OFF ");
  }
  checkLED();
}
