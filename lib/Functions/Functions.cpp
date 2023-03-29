#include "Functions.h"

void startChronometer() {
  chronometerStarted = true;
  waitResetStarted = false;
  chronometerStartTime = rtc.now();
}

void stopChronometer() {
  chronometerStarted = false;
  waitResetStarted = false;
}

void startWaitReset() {
  waitResetStarted = true;
  waitResetStartTime = rtc.now();
}

bool waitResetElapsed(int toleranceSeconds) {
  DateTime now = rtc.now();
  int secondsElapsed = now.unixtime() - waitResetStartTime.unixtime();
  return secondsElapsed >= toleranceSeconds;
}

bool sittingTooLong(int maxSecondsSitting) {
  DateTime now = rtc.now();
  int secondsSitting = now.unixtime() - chronometerStartTime.unixtime();
  return secondsSitting >= maxSecondsSitting;
}
