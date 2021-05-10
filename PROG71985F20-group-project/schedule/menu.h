//
// Group Assignment
// PROG71985 - F20
// Karl Stencell, Thomas Horvath, Gautam Singh - Dec 2020
//
// REVISION HISTORY
// 1.0		2020-Dec 11		initial
//
// VERSION 1.0 NOTES
// This file is the header file for menu.c

#pragma once

#define MAX_USER_INPUT_LEN	20


// PROTOTYPES
void printMainMenuOptions(void);
void executeUserOptionChoice(P_SCHEDULE);

void menuAddEventToSchedule(P_SCHEDULE);
void menuDeleteEvent(P_SCHEDULE);
void menuUpdateEvent(P_SCHEDULE);
void menuDisplayRangeOfEvents(P_SCHEDULE);
bool menuSearchSchedule(P_SCHEDULE);
