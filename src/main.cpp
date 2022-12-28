#include <Arduino.h>
#include <RTClib.h>
#include <SPI.h>
#include <NewPing.h>
#include <TimerOne.h>
#include <Wire.h>
#include <MultiFuncShield.h>
#include <MySerial.h>
// Real Time Clock Module
RTC_DS3231 rtc;
// Ultrasonic Distance Sensor
const int TRIGGER_PIN = 5;
const int ECHO_PIN = 6;
const int MaxDistance = 200;
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MaxDistance);
/* Aux vars */
bool chronometer = false;
DateTime chronometerDateTime;
bool waitReset = false;
DateTime waitResetDateTime;
int currentDistance = 200;
/* Config vars */
const int maxSecs = 30 * 60;
const int minDistance = 50;
const int toleranceSecs = 10;
MySerial serial(true);

void setup() {
  Timer1.initialize();
  MFS.initialize(&Timer1);
  serial.begin(9600);
  if (!rtc.begin()) {
    MFS.write("RTC");
    serial.println("Couldn't find RTC!");
    serial.flush();
    while (1)
      delay(10);
  }
}

void loop() {
  const int distanceMeasured = sonar.ping_cm();
  if (distanceMeasured != 0 && distanceMeasured != currentDistance)
    currentDistance = distanceMeasured;
  serial.print1("Distance[cm]", currentDistance);

  if (!chronometer && (currentDistance > 0 || currentDistance < minDistance)) {
    chronometer = true;
    waitReset = false;
    chronometerDateTime = rtc.now();
  }
  if (currentDistance >= minDistance) {
    if (!waitReset) {
      waitReset = true;
      waitResetDateTime = rtc.now();
    }

    DateTime now = rtc.now();
    const int secs = now.unixtime() - waitResetDateTime.unixtime();
    serial.print("Remain[s]", toleranceSecs - secs);

    if (chronometer && waitReset && secs >= toleranceSecs) {
      chronometer = false;
      waitReset = false;
    }
  } else if (waitReset) {
    waitReset = false;
  }

  if (chronometer) {
    DateTime now = rtc.now();
    const int secs = now.unixtime() - chronometerDateTime.unixtime();
    serial.print("Siting[s]", secs);
    MFS.write(secs);
    // const int mm = secs / 60;
    // const int ss = secs % 60;
    if (secs >= maxSecs) {
      serial.print("Stand up!");
      MFS.beep(5, 5, 4, 3, 50);
    }
  } else
    MFS.write("");

  serial.println();
  delay(100);
}