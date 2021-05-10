//
// Group Assignment
// PROG71985 - F20
// Karl Stencell, Thomas Horvath, Gautam Singh - Dec 2020
//
// REVISION HISTORY
// 1.0		2020-Dec 11		initial
//
// VERSION 1.0 NOTES
// This file is the header file for event.c

#pragma once
#include <stdbool.h>
#include "times.h"

#define MAX_TITLE_LEN			20
#define MAX_DESCRIPTION_LEN		100
#define MAX_LOCATION_LEN		50
#define MAX_TIME_LEN			26
#define MAX_BUFFER				250

typedef enum type {Reminder, Task}TYPE;

typedef struct event
{
	char* title;
	char* description;
	char* location;
	TYPE type;
	TIMES times;
}EVENT, *P_EVENT;

//PROTOTYPES
EVENT createEvent(char[], char[], char[], TYPE, TIMES);
EVENT copyEvent(EVENT);
bool compareEvents(EVENT, EVENT);
char* getEventTitle(EVENT);
time_t getEventStartTime(EVENT);
void printEvent(EVENT);

void updateEvent(P_EVENT);
void updateEventTitle(P_EVENT);
void updateEventLocation(P_EVENT);
void updateEventDescription(P_EVENT);
void updateEventStartTime(P_EVENT);
void updateEventEndTime(P_EVENT);
void updateEventType(P_EVENT);

void disposeEvent(EVENT);

void streamPrintEventData(FILE*, EVENT);
EVENT streamReadEventData(FILE*);