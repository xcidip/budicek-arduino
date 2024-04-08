#include <Adafruit_LiquidCrystal.h> 
int seconds = 0;

Adafruit_LiquidCrystal lcd(0);
/*
 Melodie
*/
#define NOTE_C4  262
#define NOTE_G3  196
#define NOTE_A3  220
#define NOTE_B3  247
#define NOTE_C4  262
// notes in the melody:
int melody[] = {
  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
};

// note durations: 4 = quarter note t, 8 = eighth note, etc.:
int noteDurations[] = {
  4, 8, 8, 4, 4, 4, 4, 4
};

void playAlarm() {
  for (int thisNote = 0; thisNote < 8; thisNote++) {

    // to calculate the note duration, take one second
    // divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(8, melody[thisNote], noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well4
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(8);
  }
}

void printTime(int hrs, int mins) {
  if (hrs < 10) {
    lcd.print('0');
  }
  lcd.print(hrs);
  lcd.print(':');
  if (mins < 10) {
    lcd.print('0');
  }
  lcd.print(mins);
}
 


void handleButtonPress(int buttonIndex) {
  switch (buttonIndex) {
    case 0: // Set hours
      alarmSet = true;
      lcd.clear();
      lcd.print("Set Hour:");
      break;
    case 1: // Set minutes
      if (alarmSet) {
        alarmSet = false;
        lcd.clear();
        lcd.print("Alarm:");
      }
      break;
    case 2: // Enable/disable alarm
      alarmEnabled = !alarmEnabled;
      lcd.clear();
      lcd.print("Alarm:");
      break;
    case 3: // Increment time (for setting hours or minutes)
      if (alarmSet) {
        if (lcd.cursorX() == 0) {
          alarmHour++;
          if (alarmHour >= 24) {
            alarmHour = 0;
          }
        } else {
          alarmMinute++;
          if (alarmMinute >= 60) {
            alarmMinute = 0;
          }
        }
        lcd.clear();
        lcd.print("Set Hour:");
        printTime(alarmHour, alarmMinute);
      }
      break;
  }
}


const int bPin1 = 2;
const int bPin2 = 3;
const int bPin3 = 4;
const int bPin4 = 5;

int bState1 = 0;
int bState2 = 0;
int bState3 = 0;
int bState4 = 0;

void setup() {
  lcd_1.begin(16, 2);
  lcd_1.print("");
  pinMode(bPin1, INPUT);
  pinMode(bPin2, INPUT);
  pinMode(bPin3, INPUT);
  pinMode(bPin4, INPUT);
  Serial.begin(9600);
}
/*
void loop()
{
  //playAlarm();
  lcd_1.setCursor(0, 1);
  lcd_1.setBacklight(1);
  bState2 = digitalRead(bPin2);
  lcd_1.print(bState2);
}
*/

const int buttonsPin[4] = {2, 3, 4, 5}; // Pins connected to the 4 buttons
const byte rows = 2, cols = 16;
LiquidCrystal lcd(12, 11, 5, 4, 3, 2); // Pins for LCD connections (RS, E, D4, D5, D6, D7)

int alarmHour = 0, alarmMinute = 0;
bool alarmEnabled = false;
bool alarmSet = false;
unsigned long previousMillis = 0;
const int debounceDelay = 50; // Debounce delay to avoid button bouncing in milliseconds

void setup() {
  lcd.begin(16, 2);
  lcd.clear();
  lcd.print("Budicek:");

  for (int i = 0; i < 4; i++) {
    pinMode(buttonsPin[i], INPUT_PULLUP);
  }
}

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= debounceDelay) {
    for (int i = 0; i < 4; i++) {
      if (!digitalRead(buttonsPin[i])) {
        handleButtonPress(i);
        previousMillis = currentMillis;
      }
    }
  }

  if (alarmEnabled && alarmSet && (hour() == alarmHour) && (minute() == alarmMinute)) {
    alarmRing();
  }

  // Display current time or alarm settings
  if (!alarmSet) {
    lcd.setCursor(0, 1);
    printTime(hour(), minute());
  } else {
    lcd.setCursor(0, 1);
    lcd.print("Alarm: ");
    printTime(alarmHour, alarmMinute);
    if (alarmEnabled) {
      lcd.print(" (Enabled)");
    } else {
      lcd.print(" (Disabled)");
    }
  }
}



