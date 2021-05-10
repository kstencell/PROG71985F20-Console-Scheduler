//
// Group Assignment
// PROG71985 - F20
// Karl Stencell, Thomas Horvath, Gautam Singh - Dec 2020
//
// REVISION HISTORY
// 1.0		2020-Dec 11		initial
//
// VERSION 1.0 NOTES
// This file is the header file for scheduleADT.h

#pragma once

#include <stdio.h>
#include <stdbool.h>
#include "eventnode.h"
#include "event.h"



typedef struct scheduleADT //It's a linked list
{
	P_EVENT_NODE events;
}SCHEDULE, *P_SCHEDULE;

//PROTOTYPES
SCHEDULE createSchedule();
bool addEventToSchedule(P_SCHEDULE, EVENT);
bool removeEventFromSchedule(P_SCHEDULE, EVENT);
bool isScheduleEmpty(P_SCHEDULE);
bool isEventInSchedule(P_SCHEDULE, char[], struct tm*);
void printEventInSchedule(EVENT);
EVENT getEvent(P_SCHEDULE, char[], struct tm*);
void displayNextUpcomingEventInSchedule(P_SCHEDULE);
void displayAllEventsInSchedule(P_SCHEDULE);
bool updateEventInSchedule(P_SCHEDULE, EVENT);
void printScheduleInRange(P_SCHEDULE, TIMES);

bool saveScheduleToDisk(P_SCHEDULE p_schedule, char filename[]);
bool loadScheduleFromDisk(P_SCHEDULE p_schedule, char filename[]);