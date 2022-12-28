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
DateTime saveDateTime;
int currDistance = 200;
bool lock = false;
/* Config vars */
const int maxSecs = 30 * 60;
const int distance = 100;
MySerial serial(true);

void setup() {
  Timer1.initialize();
  MFS.initialize(&Timer1);
  serial.begin(9600);
  if (!rtc.begin()) {
    serial.println("Couldn't find RTC!");
    serial.flush();
    while (1)
      delay(10);
  }
}

void loop() {
  const int currDist = sonar.ping_cm();
  if (currDist != 0 && currDist != currDistance)
    currDistance = currDist;

  if (!lock && (currDistance > 0 || currDistance < distance)) {
    lock = true;
    saveDateTime = rtc.now();
  }
  if (lock && currDistance >= distance) {
    lock = false;
  }

  serial.print1("distanceCM", currDistance);
  serial.print("lock", lock);

  if (lock) {
    DateTime now = rtc.now();
    const int secs = now.unixtime() - saveDateTime.unixtime();
    serial.print("secs", secs);
    // const int mm = secs / 60;
    // const int ss = secs % 60;
    MFS.write(secs);
    if (secs >= maxSecs) {
      serial.print("beep");
      MFS.beep(5, 5, 4, 3, 50);
    }
  } else
    MFS.write("");
  serial.println();
  delay(100);
}