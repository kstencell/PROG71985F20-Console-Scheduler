//
// Group Assignment
// PROG71985 - F20
// Karl Stencell, Thomas Horvath, Gautam Singh - Dec 2020
//
// REVISION HISTORY
// 1.0		2020-Dec 11		initial
//
// VERSION 1.0 NOTES
// This file contains the test funciton that generates 10 unique events timed 2 days apart from one another. Used to test the functionality
// of the program without having to go through and add several events first when the program loads. Helpful prior to adding the save/load funcitonality.


#include "testSchedule.h"
#include "scheduleADT.h"
#include "menu.h"
#include <string.h>
#include <stdlib.h>

void generateTestSchedule(P_SCHEDULE p_schedule)
{
	char title[MAX_TITLE_LEN];
	char description[MAX_DESCRIPTION_LEN];
	char location[MAX_LOCATION_LEN];
	TYPE type;

	// loop through the event creation 10 times
	for (int i = 0; i < AMOUNT_OF_EVENTS; i++)
	{
		snprintf(title, MAX_TITLE_LEN, "event%d", i); // cool function I found that assigns a modified string to a variable.
		snprintf(description, MAX_DESCRIPTION_LEN, "description%d", i); // useful for creating unique names to keep track of events.
		snprintf(location, MAX_LOCATION_LEN, "location%d", i);

		if (i % 2 == 0) // just to randomize the event type for testing purposes.
			type = Reminder;
		else
			type = Task;

		// generate a start time
		struct tm* start_time = malloc(sizeof(struct tm)); // do not need to free these mallocs here because they will be freed when the program writes to disk upon exit.
		time_t buffer = TIME_T_MIDNIGHT_JAN_1 + i*TIME_T_24_HOURS;
		*start_time = *localtime(&buffer);

		// generate an end time
		struct tm* end_time = malloc(sizeof(struct tm));
		buffer = TIME_T_MIDNIGHT_JAN_1 + (i+1) * TIME_T_24_HOURS;
		*end_time = *localtime(&buffer);

		TIMES times;
		times.start_time = start_time;
		times.end_time = end_time;

		// creates an event with all the necessary parameters as if a user inputted them.
		EVENT newEvent = createEvent(title, description, location, type, times);
		addEventToSchedule(p_schedule, newEvent);
	}
}
