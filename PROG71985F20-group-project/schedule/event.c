//
// Group Assignment
// PROG71985 - F20
// Karl Stencell, Thomas Horvath, Gautam Singh - Dec 2020
//
// REVISION HISTORY
// 1.0		2020-Dec 11		initial
//
// VERSION 1.0 NOTES
// This file contains the funcitonality residing over event structs from creation to manipulation to deletion.

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "event.h"


EVENT createEvent(char title[], char description[], char location[], TYPE type, TIMES times)
{
	EVENT event;

	// Give it a title
	int stringLength = strlen(title)+1;
	event.title = (char*)malloc(stringLength);
	if (!event.title)
	{
		fprintf(stderr, "Error allocating memory.\n");
		exit(1);
	}
	strncpy(event.title, title, stringLength);
	event.title[stringLength-1] = '\0';

	// Give the event a description
	stringLength = strlen(description)+1;
	event.description = (char*)malloc(stringLength);
	if (!event.description)
	{
		fprintf(stderr, "Error allocating memory.\n");
		exit(1);
	}
	strncpy(event.description, description, stringLength);
	event.description[stringLength-1] = '\0';

	// give the event a location
	stringLength = strlen(location)+1;
	event.location = (char*)malloc(stringLength);
	if (!event.location)
	{
		fprintf(stderr, "Error allocating memory.\n");
		exit(1);
	}
	strncpy(event.location, location, stringLength);
	event.location[stringLength-1] = '\0';

	// give the event a type
	event.type = type;

	//give the event times
	event.times = times;

	return event;
}

EVENT copyEvent(EVENT event) //simple cloning function
{
	EVENT copy;
	copy.title = event.title;
	copy.description = event.description;
	copy.location = event.location;
	copy.type = event.type;
	copy.times = event.times;

	return copy;
}

bool compareEvents(EVENT a, EVENT b) // compares events by comparing every parameter against each other
{
	if (a.type != b.type)
		return false;

	if (!compareTimes(a.times, b.times))
		return false;

	char a_buffer[MAX_BUFFER];
	char b_buffer[MAX_BUFFER];

	strcpy(a_buffer, a.title);
	strcpy(b_buffer, b.title);
	if (strcmp(a_buffer, b_buffer)) //couldn't just do strcmp(a.title, b.title)... 
		return false;

	strcpy(a_buffer, a.location);
	strcpy(b_buffer, b.location);
	if (strcmp(a_buffer, b_buffer))
		return false;

	strcpy(a_buffer, a.description);
	strcpy(b_buffer, b.description);
	if (strcmp(a_buffer, b_buffer))
		return false;

	return true;
}

char* getEventTitle(EVENT a)
{
	return a.title;
}

time_t getEventStartTime(EVENT a)
{
	return getStartTime(a.times);
}

void printEvent(EVENT event) // Every time an event appears on screen its because this function prints it
{
	printf("\n");
	char buffer[MAX_TIME_LEN];
	printf("Title: %s\n", event.title);
	printf("Location: %s\n", event.location);
	printf("Description: %s\n", event.description);
	int type = event.type;
	if (type == 1)
		printf("Type: Task\n");
	else
		printf("Type: Reminder\n");
	time_t startTime = getStartTime(event.times);
	char* c_time_string;
	c_time_string = ctime(&startTime);
	printf("Start time: %s", c_time_string);
	time_t endTime = getEndTime(event.times);
	c_time_string = ctime(&endTime);
	printf("End time: %s", c_time_string);
	printf("\n");
}

void updateEvent(P_EVENT event) // This update menu works in a similar fashion as the main menu where it asks for input, directs control to external functions, and loops until the user exits.
{
	bool changesWereMade = false;

	char option_choice[MAX_BUFFER];
	while (true)
	{
		fputs("\n\nCurrent event information:\n", stdout);
		printEvent(*event); // just to confirm to the user this is the event information

		fputs("Choose which type of event information you would like to change: \n", stdout);
		fputs("a. Title\n", stdout);
		fputs("b. Location\n", stdout);
		fputs("c. Description\n", stdout);
		fputs("d. Type\n", stdout);
		fputs("e. Start Time\n", stdout);
		fputs("f. End time\n", stdout);
		fputs("g. Quit\n", stdout);
		fputs("Option: ", stdout);

		fgets(option_choice, MAX_BUFFER, stdin);
		option_choice[strcspn(option_choice, "\n")] = 0;

		if (!strcmp("a", option_choice)) // check for option choice by user
		{
			updateEventTitle(event);
		}
		else if (!strcmp("b", option_choice))
		{
			updateEventLocation(event);
		}
		else if (!strcmp("c", option_choice))
		{
			updateEventDescription(event);
		}
		else if (!strcmp("d", option_choice))
		{
			updateEventType(event);
		}
		else if (!strcmp("e", option_choice))
		{
			updateEventStartTime(event);
		}
		else if (!strcmp("f", option_choice))
		{
			updateEventEndTime(event);
		}
		else if (!strcmp("g", option_choice))
		{
			return;
		}
		else
		{
			printf("Not a valid input. Try again.\n");
		}
	}
}

void updateEventTitle(P_EVENT event)
{
	fputs("Enter a new event title (0 to quit): ", stdout);
	char buffer[MAX_TITLE_LEN];
	fgets(buffer, MAX_TITLE_LEN, stdin);
	if (strcmp(buffer, "0\n"))
	{
		free(event->title); // memory mangement. I free than reallocate because the new title is not guaranteed to be the same size as the old title.
		int stringLength = strlen(buffer);
		event->title = (char*)malloc(stringLength);
		if (!event->title)
		{
			fprintf(stderr, "Error allocating memory.\n");
			exit(1);
		}
		buffer[stringLength-1] = '\0';
		strncpy(event->title, buffer, stringLength);

		printf("\nThe title of the event has been changed to %s\n", event->title); // confirm the change with a print.
	}
	else
		fputs("\nNo changes to the title have been made.\n", stdout); // confirm also if nothing happened

	return;
}

void updateEventLocation(P_EVENT event)
{
	fputs("Enter a new event location (0 to quit): ", stdout);
	char buffer[MAX_LOCATION_LEN];
	fgets(buffer, MAX_LOCATION_LEN, stdin);
	if (strcmp(buffer, "0\n"))
	{
		free(event->location); // memory mangement
		int stringLength = strlen(buffer);
		event->location = (char*)malloc(stringLength);
		if (!event->location)
		{
			fprintf(stderr, "Error allocating memory.\n");
			exit(1);
		}
		buffer[stringLength - 1] = '\0';
		strncpy(event->location, buffer, stringLength);

		printf("\nThe location of the event has been changed to %s\n", event->location); // print confirmation for the user
	}
	else
		fputs("\nNo changes to the location have been made.\n", stdout);

	return;
}

void updateEventDescription(P_EVENT event)
{
	fputs("Enter a new event description (0 to quit): ", stdout);
	char buffer[MAX_DESCRIPTION_LEN];
	fgets(buffer, MAX_DESCRIPTION_LEN, stdin);
	if (strcmp(buffer, "0\n"))
	{
		free(event->description); // memory management
		int stringLength = strlen(buffer);
		event->description = (char*)malloc(stringLength);
		if (!event->description)
		{
			fprintf(stderr, "Error allocating memory.\n");
			exit(1);
		}
		buffer[stringLength - 1] = '\0';
		strncpy(event->description, buffer, stringLength);

		printf("\nThe description of the event has been changed to %s\n", event->description); // print confirmation for the user
	}
	else
		fputs("\nNo changes to the description have been made.\n", stdout);

	return;
}

void updateEventType(P_EVENT event)
{
	bool validTypeChoice = false;
	char buffer[MAX_BUFFER];
	while (!validTypeChoice) // logically this is a micro version of the main menu
	{
		fputs("Choose an event type by entering its letter label (0 to quit): \n", stdout);
		fputs("a. Reminder\n", stdout);
		fputs("b. Task\n", stdout);
		fputs("Option: ", stdout);

		fgets(buffer, MAX_BUFFER, stdin);
		buffer[strcspn(buffer, "\n")] = 0;

		if (!strcmp("a", buffer))
		{
			event->type = Reminder;
			fputs("\nThe event type has been changed to: Reminder\n", stdout); // print confirmation
			validTypeChoice = true;
		}
		else if (!strcmp("b", buffer))
		{
			event->type = Task;
			fputs("\nThe event type has been changed to: Task\n", stdout); // print confirmation
			validTypeChoice = true;
		}
		else if (!strcmp("0", buffer))
		{
			printf("\nNo new type information has been saved.\n"); // confirm nothing was changed
			return;
		}
		else
		{
			printf("\nNot a valid input. Try again.\n\n");
		}
	}
}

void updateEventStartTime(P_EVENT event)
{
	struct tm* new_time = malloc(sizeof(struct tm));
	bool validTime = false;
	do
	{
		fputs("\nChoose the new start time for this event by answering the following questions.\n", stdout);

		if (!createATime(new_time))
		{
			printf("\n");
			return;
		}
		// Check that the event time is still in the future and still before the end time.
		if (difftime(mktime(new_time), time(NULL)) <= 0 || difftime(getEndTime(event->times), mktime(new_time)) <= 0)
		{
			printf("\nError! The event must start in the future and before the end time. Try again!\n");
			validTime = false;
		}
		else
			validTime = true;

	} while (!validTime);

	disposeStartTime(event->times); // memory management. The struct will be the same size as the old one but it was easier to dispose the old and create a new
	updateStartTime(&event->times, new_time);

	printf("\n");
	return;
}

void updateEventEndTime(P_EVENT event)
{
	struct tm* new_time = malloc(sizeof(struct tm));
	bool validTime = false;
	do
	{
		fputs("\nChoose the new end time for this event by answering the following questions.\n", stdout);

		if (!createATime(new_time))
		{
			printf("\n");
			return;
		}
		// check that the new end time comes after the start time.
		if (difftime(mktime(new_time), getStartTime(event->times)) <= 0)
		{
			printf("\nError! The ending time must be after the starting time.\n");
			validTime = false;
		}
		else
			validTime = true;

	} while (!validTime);

	disposeEndTime(event->times); // memory management
	updateEndTime(&event->times, new_time);

	printf("\n");
	return;
}

void disposeEvent(EVENT event) // memory management
{
	free(event.title);
	free(event.description);
	free(event.location);
}

void streamPrintEventData(FILE* fp, EVENT event) // prints a whole event to a text file.
{
	fprintf(fp, "%s\n", event.title);
	fprintf(fp, "%s\n", event.description);
	fprintf(fp, "%s\n", event.location);
	fprintf(fp, "%d\n", event.type);
	streamPrintTimes(fp, event.times);
}

EVENT streamReadEventData(FILE* fp, char event_title[MAX_BUFFER]) // reads a whole event from a text file
{
	char event_description[MAX_DESCRIPTION_LEN];
	char event_location[MAX_LOCATION_LEN];
	int event_type_num;
	TYPE event_type;

	// already have the event title from memory but it needs to get the newline chopped off
	for (size_t i = 0; i < strlen(event_title); i++)
		if (event_title[i] == '\n')
			event_title[i] = '\0';

	// get the event description from file
	fgets(event_description, MAX_DESCRIPTION_LEN, fp);
	for (size_t i = 0; i < strlen(event_description); i++)
		if (event_description[i] == '\n')
			event_description[i] = '\0';

	// get the event location from the file.
	fgets(event_location, MAX_LOCATION_LEN, fp);
	for (size_t i = 0; i < strlen(event_location); i++)
		if (event_location[i] == '\n')
			event_location[i] = '\0';

	// get the event type from file
	fscanf(fp, "%d\n", &event_type_num);
	if (event_type_num == 0)
		event_type = Reminder;
	else
		event_type = Task;

	// get the event times from the file
	TIMES times = streamReadTimes(fp);

	// all info has been gathered so the event struct can be made
	EVENT event = createEvent(event_title, event_description, event_location, event_type, times);

	return event;
}