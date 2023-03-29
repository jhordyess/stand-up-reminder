#include <RTClib.h>

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

extern bool chronometerStarted;

extern DateTime chronometerStartTime;

extern bool waitResetStarted;

extern DateTime waitResetStartTime;

extern RTC_DS3231 rtc;

/**
 * @brief Starts the chronometer when the person sits on the chair.
 */
void startChronometer();

/**
 * @brief Stops the chronometer when the person stands up from the chair or has been sitting for too long.
 */
void stopChronometer();

/**
 * @brief Starts the wait period after the person stands up from the chair.
 */
void startWaitReset();

/**
 * @brief Checks if the wait period has elapsed.
 * @return true if the wait period has elapsed, false otherwise.
 */
bool waitResetElapsed(int toleranceSeconds);

/**
 * @brief Checks if the person has been sitting for too long.
 * @return true if the person has been sitting for too long, false otherwise.
 */
bool sittingTooLong(int maxSecondsSitting);

#endif