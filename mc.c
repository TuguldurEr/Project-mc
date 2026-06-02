#include <LiquidCrystal.h>

const int buzzerPin = 8;
const int buttonPin1 = 7;
const int buttonPin2 = 2;
const int rs = 12, en = 11, d4 = A0, d5 = A1, d6 = A2, d7 = A3;

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int melody[] = {
  660, 660, 0, 660, 0, 510, 660, 0,
  770, 0, 380, 0,
  510, 0, 380, 0,
  320, 0, 440, 0, 480, 0, 450, 430, 380,
  660, 0, 770, 0, 860, 0, 700, 760,
  660, 0, 510, 430, 380, 0,
  510, 0, 380, 0,
  320, 0, 440, 0, 480, 0, 450, 430, 380,
  660, 0, 770, 0, 860, 0, 700, 760,
  660, 0, 510, 430, 380, 0
};

int noteDurations[] = {
  8, 8, 8, 8, 8, 8, 8, 8,
  8, 8, 8, 8,
  8, 8, 8, 8,
  8, 8, 8, 8, 8, 8, 8, 8, 8,
  8, 8, 8, 8, 8, 8, 8, 8,
  8, 8, 8, 8, 8, 8,
  8, 8, 8, 8,
  8, 8, 8, 8, 8, 8, 8, 8, 8,
  8, 8, 8, 8, 8, 8, 8, 8,
  8, 8, 8, 8, 8, 8
};

int totalNotes = 62;

void setup() {
  delay(500);
  pinMode(buttonPin1, INPUT_PULLUP);
  pinMode(buttonPin2, INPUT_PULLUP);
  pinMode(buzzerPin, OUTPUT);
  lcd.begin(16, 2);
  showIdle();
}

void loop() {
  if (digitalRead(buttonPin1) == LOW) {
    delay(50);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Mario Theme");
    lcd.setCursor(0, 1);
    lcd.print("Nintendo");

    bool reset = false;

    for (int i = 0; i < totalNotes; i++) {
      int noteDuration = 1000 / noteDurations[i];
      int pauseDuration = noteDuration * 13 / 10;

      if (melody[i] != 0) {
        tone(buzzerPin, melody[i], noteDuration);
      }

      for (int t = 0; t < pauseDuration; t++) {
        if (digitalRead(buttonPin2) == LOW) {
          reset = true;
          break;
        }
        delay(1);
      }

      noTone(buzzerPin);

      if (reset) {
        break;
      }
    }

    noTone(buzzerPin);

    if (reset) {
      for (int loop = 0; loop < 3; loop++) {
        for (int dots = 1; dots <= 3; dots++) {
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Resetting");
          for (int d = 0; d < dots; d++) {
            lcd.print(".");
          }
          delay(400);
        }
      }
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Reset!");
      delay(1000);
    }

    showIdle();
    delay(500);
  }
}

void showIdle() {
  lcd.setCursor(0, 0);
  lcd.print("Press button to");
  lcd.setCursor(0, 1);
  lcd.print("start game!");
}
