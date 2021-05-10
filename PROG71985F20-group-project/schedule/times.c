//
// Group Assignment
// PROG71985 - F20
// Karl Stencell, Thomas Horvath, Gautam Singh - Dec 2020
//
// REVISION HISTORY
// 1.0		2020-Dec 11		initial
//
// VERSION 1.0 NOTES
// This file contains the interface functionality with the times struct (which contains a start and an end time).

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "times.h"

TIMES createTimes(struct tm* start_time, struct tm* end_time) // actually create a struct in memory
{
	TIMES times;
	times.start_time = start_time;
	times.end_time = end_time;

	return times;
}

// This function is called for every instance where the user is asked to enter a time.
// It is responsible for gathering time data and also verifying that the numbers inputted constitute a legitimate time in the calendar.
// Usually in my program '0' is to quit but its switched to 'q' here because 0 is a valid input this time.
bool createATime(struct tm* time)
{
	long number = 0;
	long* p_number = &number;
	int year, daysInMonth;
	bool parameterIsValid = false;

	while (!parameterIsValid) // this loop is used again and again to reprompt a user if they entered invalid input. Most a typo safeguard.
	{
		fputs("Enter the year (q to quit): ", stdout);
		if (!getTimeParameter(p_number))
			return false;
		else
			if (*p_number >= CURRENT_YEAR) // only allow events to be created in the future
			{
				year = *p_number;
				time->tm_year = *p_number - STRUCT_YEAR_OFFSET; //tm structs hold years as "number of years since 1900"
				parameterIsValid = true;
			}
			else
				fputs("\nNot a valid input. Try again.\n\n", stdout);
	}
	
	parameterIsValid = false;
	while (!parameterIsValid)
	{
		fputs("Enter the month number (q to quit): ", stdout);
		if (!getTimeParameter(p_number))
			return false;
		else
			if (*p_number <= MONTHS_IN_YEAR && *p_number > 0) //validate choice of month
			{
				int month = *p_number;
				daysInMonth = numberOfDays(month - 1, year); // this funciton checks the amount of days for the month in the year chosen.
				time->tm_mon = *p_number - 1; //array offset
				parameterIsValid = true;
			}
			else
				fputs("\nNot a valid input. Try again.\n\n", stdout);
				
	}
	
	parameterIsValid = false;
	while (!parameterIsValid)
	{
		fputs("Enter the day number (q to quit): ", stdout);
		if (!getTimeParameter(p_number))
			return false;
		else
			if (*p_number <= daysInMonth && *p_number >= 1) // validate input
			{
				time->tm_mday = *p_number;
				parameterIsValid = true;
			}
			else
				fputs("\nNot a valid input. Try again.\n\n", stdout);
	}
	
	parameterIsValid = false;
	while (!parameterIsValid)
	{
		fputs("Enter the hour in 24hr format (q to quit): ", stdout);
		if (!getTimeParameter(p_number))
			return false;
		else
			if (*p_number < HOURS_IN_DAY && *p_number >= 0) // validate input
			{
				time->tm_hour = *p_number;
				parameterIsValid = true;
			}
			else
				fputs("\nNot a valid input. Try again.\n\n", stdout);
	}
	
	parameterIsValid = false;
	while (!parameterIsValid)
	{
		fputs("Enter the minutes (q to quit): ", stdout);
		if (!getTimeParameter(p_number))
			return false;
		else
			if (*p_number < MINS_IN_HOUR && *p_number >= 0) // validate input
			{
				time->tm_min = *p_number;
				parameterIsValid = true;
			}
			else
				fputs("\nNot a valid input. Try again.\n\n", stdout);
	}

	time->tm_sec = 0; // this schedule doesn't get more precise than minutes.

	return true;
}

bool getTimeParameter(int* p_number) // grabbing user input for a time happens several times so I gave it its own function
{
	char buffer[LINE_MAX];
	bool isInputNumerical;
	do
	{
		isInputNumerical = true;
		fgets(buffer, LINE_MAX, stdin);
		if (!strcmp(buffer, "q\n")) // check exit condition
			return false;
		buffer[strlen(buffer) - 1] = 0;

		for (int i = 0; i < strlen(buffer); i++) // Checks that the user inputted a number i.e no letters or symbols are in the string.
		{
			if (((int)buffer[i] < ASCII_VALUE_0) || (int)buffer[i] > ASCII_VALUE_9) // validate each character by checking its ASCII value
			{
				isInputNumerical = false;
				fputs("Input must be a numerical value. Try again.\n", stdout);
				break;
			}
		}
	} while (!isInputNumerical);

	*p_number = atoi(buffer);

	return true;
}

// from https://www.geeksforgeeks.org/c-program-to-display-month-by-month-calendar-for-a-given-year/
// Simply returns the days in a given month.
int numberOfDays(int monthNumber, int year)
{
	// January 
	if (monthNumber == 0)
		return (31);

	// February 
	if (monthNumber == 1) {
		// If the year is leap then Feb 
		// has 29 days 
		if (year % 400 == 0
			|| (year % 4 == 0
				&& year % 100 != 0))
			return (29);
		else
			return (28);
	}

	// March 
	if (monthNumber == 2)
		return (31);

	// April 
	if (monthNumber == 3)
		return (30);

	// May 
	if (monthNumber == 4)
		return (31);

	// June 
	if (monthNumber == 5)
		return (30);

	// July 
	if (monthNumber == 6)
		return (31);

	// August 
	if (monthNumber == 7)
		return (31);

	// September 
	if (monthNumber == 8)
		return (30);

	// October 
	if (monthNumber == 9)
		return (31);

	// November 
	if (monthNumber == 10)
		return (30);

	// December 
	if (monthNumber == 11)
		return (31);
}

time_t getStartTime(TIMES tm)
{
	return mktime(tm.start_time);
}

time_t getEndTime(TIMES tm)
{
	return mktime(tm.end_time);
}

bool compareTimes(TIMES a, TIMES b)
{
	if ((difftime(mktime(a.start_time), mktime(b.start_time)) != 0) || (difftime(mktime(a.end_time), mktime(b.end_time)) != 0))
		return false;
	else
		return true;
}

void updateStartTime(P_TIMES times, struct tm* new_time)
{
	times->start_time = new_time;
	return;
}

void updateEndTime(P_TIMES times, struct tm* new_time)
{
	times->end_time = new_time;
	return;
}

void streamPrintTimes(FILE* fp, TIMES times) //prints to file
{
	fprintf(fp, "%d\n", mktime(times.start_time));
	fprintf(fp, "%d\n", mktime(times.end_time));
}

TIMES streamReadTimes(FILE* fp) // reads from file
{
	struct tm* start_time = malloc(sizeof(struct tm));
	struct tm* end_time = malloc(sizeof(struct tm));
	
	time_t buffer;
	fscanf(fp, "%lld\n", &buffer);
	time_t time1 = buffer;
	*start_time = *localtime(&time1);

	fscanf(fp, "%lld\n", &buffer);
	time_t time2 = buffer;
	*end_time = *localtime(&time2);

	TIMES times = createTimes(start_time, end_time);

	return times;
}

void disposeStartTime(TIMES times) // memory management
{
	free(times.start_time);
	return;
}

void disposeEndTime(TIMES times) // memory management
{
	free(times.end_time);
	return;
}
