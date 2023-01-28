
#include "../c_datetime.h"

#include <stdio.h>
#include <string.h>

// define day index constants
enum dayIndex {
  SUNDAY_INDEX = 0,
  MONDAY_INDEX,
  TUESDAY_INDEX,
  WEDNESDAY_INDEX,
  THURSDAY_INDEX,
  FRIDAY_INDEX,
  SATURDAY_INDEX
};

// define expections data structure
typedef struct {
    long timestamp;
    int dayIdx;
} ExpectDateTime;

// declare test methods
int testDateTime (SHDateTime * dt, ExpectDateTime * ex);


int main (int argc, char * argv[]) {
  printf("Start tests...\n");

  int status = 0;
  SHDateTime dt;
  ExpectDateTime ex;

  dt = (SHDateTime){.year = 1970, .month = 1, .day = 1, .hour = 0, .min = 0, .sec = 0, .timezoneOffset = 0};
  ex = (ExpectDateTime){.timestamp = 0, .dayIdx = THURSDAY_INDEX};
  status = testDateTime(&dt, &ex) || status;

  dt = (SHDateTime){.year = 1970, .month = 1, .day = 15, .hour = 0, .min = 0, .sec = 0, .timezoneOffset = 0};
  ex = (ExpectDateTime){.timestamp = 14 * UNIX_DAY, .dayIdx = THURSDAY_INDEX};
  status = testDateTime(&dt, &ex) || status;

  dt = (SHDateTime){.year = 1969, .month = 12, .day = 31, .hour = 0, .min = 0, .sec = 0, .timezoneOffset = 0};
  ex = (ExpectDateTime){.timestamp = -1 * UNIX_DAY, .dayIdx = WEDNESDAY_INDEX};
  status = testDateTime(&dt, &ex) || status;

  dt = (SHDateTime){.year = 1969, .month = 12, .day = 18, .hour = 0, .min = 0, .sec = 0, .timezoneOffset = 0};
  ex = (ExpectDateTime){.timestamp = -14 * UNIX_DAY, .dayIdx = THURSDAY_INDEX};
  status = testDateTime(&dt, &ex) || status;

  if (status) printf("Tests completed with failures.\n");
  else printf("Tests completed with all passing.\n");
  return status;
}


// test methods with given SHDateTime values against expectations in ExpectedDateTime
int testDateTime (SHDateTime * dt, ExpectDateTime * ex) {
  printf("Testing date time: %d, month: %d, day: %d, hour: %d, min: %d, sec: %d, tz: %d\n", dt->year, dt->month, dt->day, dt->hour, dt->min, dt->sec, dt->timezoneOffset);
  
  long timestamp;
  int status;
  status = dateObjToTimestamp(dt, &timestamp);
  if (status != 0) {
    printf("FAILED dateObjToTimestamp with status %d\n", status);
    return 1;
  }
  if (timestamp != ex->timestamp) {
    printf("FAILED dateObjToTimestamp, expected %d but returned %d\n", ex->timestamp, timestamp);
    return 1;
  }
  printf("PASSED dateObjToTimestamp\n");

  int dayIdx;
  status = calcWeekdayIdx(timestamp, dt->timezoneOffset, &dayIdx);
  if (status != 0) {
    printf("FAILED calcWeekdayIdx with status %d\n", status);
    return 1;
  }
  if (dayIdx != ex->dayIdx) {
    printf("FAILED calcWeekdayIdx, expected %d but returned %d\n", ex->dayIdx, dayIdx);
    return 1;
  }
  printf("PASSED calcWeekdayIdx\n");
  printf("Passed date time.\n\n");
  return 0;
}