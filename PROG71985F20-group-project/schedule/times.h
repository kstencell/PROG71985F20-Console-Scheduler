//
// Group Assignment
// PROG71985 - F20
// Karl Stencell, Thomas Horvath, Gautam Singh - Dec 2020
//
// REVISION HISTORY
// 1.0		2020-Dec 11		initial
//
// VERSION 1.0 NOTES
// This file is the header file for times.c

#pragma once
#include <time.h>
#include <stdbool.h>

#define LINE_MAX			20
#define CURRENT_YEAR		2020
#define STRUCT_YEAR_OFFSET	1900
#define MONTHS_IN_YEAR		12
#define HOURS_IN_DAY		24
#define MINS_IN_HOUR		60
#define MAX_TIME_BUFFER		100
#define ASCII_VALUE_9		57
#define ASCII_VALUE_0		48


typedef struct times
{
	struct tm* start_time;
	struct tm* end_time;
}TIMES, *P_TIMES;

TIMES createTimes(struct tm*, struct tm*);
bool createATime(struct tm*);
bool getTimeParameter(int*);
int numberOfDays(int, int);
time_t getStartTime(TIMES);
time_t getEndTime(TIMES);
bool compareTimes(TIMES, TIMES);
void updateStartTime(P_TIMES, struct tm*);
void updateEndTime(P_TIMES, struct tm*);


void streamPrintTimes(FILE*, TIMES);
TIMES streamReadTimes(FILE*);

void disposeStartTime(TIMES);
void disposeEndTime(TIMES);