#include <Arduino.h>
#include <RTClib.h>
#include <SPI.h>
#include <NewPing.h>
#include <TimerOne.h>
#include <Wire.h>
#include <MultiFuncShield.h>
#include <Functions.h>

// Constants
const int TRIGGER_PIN = 5;
const int ECHO_PIN = 6;
const int MAX_DISTANCE = 200;
const int MAX_SECONDS_SITTING = 30 * 60;
const int MIN_DISTANCE = 50;
const int TOLERANCE_SECONDS = 10;

// Variables
bool chronometerStarted = false;
DateTime chronometerStartTime;
bool waitResetStarted = false;
DateTime waitResetStartTime;
int currentDistance = MAX_DISTANCE;

RTC_DS3231 rtc;
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

void printData(const String &label, int value) {
  Serial.print(label);
  Serial.print(value);
  Serial.print("\t");
}

void setup() {
  Timer1.initialize();
  MFS.initialize(&Timer1);
  Serial.begin(9600);

  if (!rtc.begin()) {
    MFS.write("RTC");
    Serial.println("Couldn't find RTC!");
    Serial.flush();
    while (1)
      delay(10);
  }
}

void loop() {
  int distanceMeasured = sonar.ping_cm();
  if (distanceMeasured > 0 && distanceMeasured != currentDistance) {
    currentDistance = distanceMeasured;
  }
  printData("Distance[cm]", currentDistance);

  if (!chronometerStarted && (currentDistance > 0 || currentDistance < MIN_DISTANCE)) {
    startChronometer();
  }

  if (currentDistance >= MIN_DISTANCE) {
    if (!waitResetStarted) {
      startWaitReset();
    }
    int remainingSeconds = TOLERANCE_SECONDS - (rtc.now().unixtime() - waitResetStartTime.unixtime());
    printData("Remain[s]", remainingSeconds);

    if (chronometerStarted && waitResetStarted && waitResetElapsed(TOLERANCE_SECONDS)) {
      stopChronometer();
      MFS.write("");
    }
  } else if (waitResetStarted) {
    stopChronometer();
  }

  if (chronometerStarted) {
    int secondsSitting = rtc.now().unixtime() - chronometerStartTime.unixtime();
    printData("Siting[s]", secondsSitting);
    MFS.write(secondsSitting);

    if (sittingTooLong(MAX_SECONDS_SITTING)) {
      Serial.print("Stand up!");
      MFS.beep(5, 5, 4, 3, 50);
    }
  } else {
    MFS.write("");
  }

  Serial.println();
  delay(100);
}