//
// Group Assignment
// PROG71985 - F20
// Karl Stencell, Thomas Horvath, Gautam Singh - Dec 2020
//
// REVISION HISTORY
// 1.0		2020-Dec 11		initial
//
// VERSION 1.0 NOTES
// This file contains all the functionality needed by the main menu of the program. It will print the menu, prompt the user for input to
// declare their option choice, then call the appropriate functions to perform the task the user is trying to accomplish.

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "scheduleADT.h"
#include "menu.h"
#include "event.h"

void printMainMenuOptions(void) // main menu options
{
	fputs("~~~~~~~~~~~~~~~~~~~~ MENU ~~~~~~~~~~~~~~~~~~~\n", stdout);
	fputs("To choose a function, enter its letter label:\n\n", stdout);
	fputs("a) Add a new event.\n", stdout);
	fputs("b) Delete an existing event.\n", stdout); 
	fputs("c) Update an existing event.\n", stdout);
	fputs("d) Display next upcoming event in schedule.\n", stdout);
	fputs("e) Display a range of events.\n", stdout);
	fputs("f) Display all events.\n", stdout);
	fputs("g) Search for an event.\n", stdout);
	fputs("h) Quit\n", stdout);
	fputs("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n", stdout);
	fputs("Option: ", stdout);
}

void executeUserOptionChoice(P_SCHEDULE p_schedule)
{
	char user_input[MAX_USER_INPUT_LEN];

while (true)
	{
		fgets(user_input, MAX_USER_INPUT_LEN, stdin);
		user_input[strcspn(user_input, "\n")] = 0;

		if (!strcmp("a", user_input)) // Add an event
		{
			printf("\n");
			menuAddEventToSchedule(p_schedule);
			return;
		}
		else if (!strcmp("b", user_input)) // Delete an event
		{
			printf("\n");
			menuDeleteEvent(p_schedule);
			return;
		}
		else if (!strcmp("c", user_input)) // Update an event
		{
			printf("\n");
			menuUpdateEvent(p_schedule);
			return;
		}
		else if (!strcmp("d", user_input)) // Display upcoming event
		{
			displayNextUpcomingEventInSchedule(p_schedule);
			return;
		}
		else if (!strcmp("e", user_input)) // Display range
		{
			menuDisplayRangeOfEvents(p_schedule);
			return;
		}
		else if (!strcmp("f", user_input)) // Display all events
		{
			displayAllEventsInSchedule(p_schedule);
			return;
		}
		else if (!strcmp("g", user_input)) // Search for a single event.
		{
			menuSearchSchedule(p_schedule);
			return;
		}
		else if (!strcmp("h", user_input))  // Quit
		{
			if (!saveScheduleToDisk(p_schedule, "datafile.txt"))
				fprintf(stderr, "\nError saving to file.\n");
			exit(EXIT_SUCCESS);
		}
		else
		{
			fputs("\nError reading menu option, please try again!\n\n", stdout);
		}
	}
}

void menuAddEventToSchedule(P_SCHEDULE p_schedule) // grab user input for event details, creates an event struct with that info, then adds it to the schedule linked list.
{
	char title[MAX_TITLE_LEN];
	char description[MAX_DESCRIPTION_LEN];
	char location[MAX_LOCATION_LEN];
	char type_choice[MAX_USER_INPUT_LEN];

	// Get the event title
	bool validInput = false;
	do
	{
		fputs("Enter a title for your new event (0 to quit): ", stdout);
		fgets(title, MAX_TITLE_LEN, stdin);
		//clearInputStream();
		if (!strcmp(title, "0\n")) // Check quit condition
		{
			printf("\n");
			return;
		}
		else if (!strcmp(title, "\n"))
		{
			printf("\nNot a valid input.\n\n");
		}
		else
			validInput = true;

		title[strcspn(title, "\n")] = 0;
	} while (!validInput);

	// Get the event location
	validInput = false;
	do
	{
		fputs("Enter a location for your new event (0 to quit): ", stdout);
		fgets(location, MAX_LOCATION_LEN, stdin);
		if (!strcmp(location, "0\n")) // Check quit condition
		{
			printf("\n");
			return;
		}
		else if (!strcmp(location, "\n"))
		{
			printf("\nNot a valid input.\n\n");
		}
		else
			validInput = true;

		location[strcspn(location, "\n")] = 0;
	} while (!validInput);

	// Get the event description
	validInput = false;
	do
	{
		fputs("Enter a description for your new event (0 to quit): ", stdout);
		fgets(description, MAX_DESCRIPTION_LEN, stdin);
		//clearInputStream();
		if (!strcmp(description, "0\n")) // Check quit condition
		{
			printf("\n");
			return;
		}
		else if (!strcmp(description, "\n"))
		{
			printf("\nNot a valid input.\n\n");
		}
		else
			validInput = true;

		description[strcspn(description, "\n")] = 0;
	} while (!validInput);

	// Get the event type.
	TYPE type;
	bool validTypeChoice = false;
	while (!validTypeChoice) // Same design as the main menu.
	{
		fputs("Choose an event type by entering its letter label (0 to quit): \n", stdout);
		fputs("a. Reminder\n", stdout);
		fputs("b. Task\n", stdout);
		fputs("Option: ", stdout);

		fgets(type_choice, MAX_USER_INPUT_LEN, stdin);
		type_choice[strcspn(type_choice, "\n")] = 0;

		if (!strcmp("a", type_choice))
		{
			type = Reminder;
			validTypeChoice = true;
		}
		else if (!strcmp("b", type_choice)) 
		{
			type = Task;
			validTypeChoice = true;
		}
		else if (!strcmp("0", type_choice)) // Check quit condition
		{
			printf("\n");
			return;
		}
		else // Check invalid input
		{
			printf("Not a valid input. Try again.\n");
		}
	}

	// Get event start time
	bool validTime = false;
	struct tm* start_time = malloc(sizeof(struct tm));
	do // loop here to repromt the user if they entered invalid time parameters so they don't have to re-input above info.
	{
		fputs("\nChoose when this event starts by answering the following questions.\n", stdout);

		if (!createATime(start_time)) // Prompts user to input timing information. Also check here for quit condition.
		{
			printf("\n");
			return;
		}
		if (difftime(mktime(start_time), time(NULL)) <= 0) // Start time must happen in the future.
		{
			printf("\nError! The event must start in the future. Try again!\n\n");
			validTime = false;
		}
		else
			validTime = true;
		
	} while (!validTime);

	// Get event end time.
	struct tm* end_time = malloc(sizeof(struct tm));
	validTime = false;
	do // loop here to repromt the user if they entered invalid time parameters so they don't have to re-input above info.
	{
		fputs("\nChoose when this event ends by answering the following questions.\n", stdout);

		if (!createATime(end_time))// Prompts user to input timing information. Also check here for quit condition.
		{
			printf("\n");
			return;
		}
		if (difftime(mktime(end_time), mktime(start_time)) <= 0) // End time must come after the start time.
		{
			printf("\nError! The ending time must be after the starting time.\n\n");
			validTime = false;
		}
		else
			validTime = true;
	} while (!validTime);

	// Create the times struct and fill it
	TIMES times;
	times.start_time = start_time;
	times.end_time = end_time;

	//PRINT CONFIRMATION DETAILS
	EVENT newEvent = createEvent(title, description, location, type, times);

	// This prevents multiple events with the same title and start time from being added.
	// These events can either be viewed as redundant and thus unnecessary or
	// conflicting for a time slot that is already occupied in the schedule. Either way it is not allowed.
	// Essentially the title and start time of an event are what defines the uniqueness of an event.
	if (!isEventInSchedule(p_schedule, title, start_time))
	{
		addEventToSchedule(p_schedule, newEvent);
		fputs("\nThe following event has been added to your schedule.\n", stdout);
		printEventInSchedule(newEvent);
	}
	else // found an event with the same title and start time.
	{
		time_t startTime = mktime(start_time); // the following three lines show up quite a bit in this program
		char* c_time_string;					// and are required by the time.h standard functions to print times nicely
		c_time_string = ctime(&startTime);
		printf("\n\nError adding event to schedule.\n");
		printf("An event with the title %s and starts at %s is already in your schedule.\n\n", title, c_time_string);
	}
}

void menuDeleteEvent(P_SCHEDULE p_schedule)
{
	char event_title[MAX_USER_INPUT_LEN];
	struct tm* event_time = malloc(sizeof(struct tm));
	bool eventWasFound;

	if (isScheduleEmpty(p_schedule)) // not worth continuing if the schedule is empty
	{
		fputs("The schedule is currently empty.\n\n", stdout);
		return;
	}

	do //loop to reprompt the user if the event they are trying to delete wasn't found which most likely could be caused by a typo.
	{
		fputs("Enter the name of the event you would like to delete (0 to quit): ", stdout);

		eventWasFound = false;
		fgets(event_title, MAX_LOCATION_LEN, stdin);
		if (!strcmp(event_title, "0\n")) // Check for exit condition
		{
			printf("\n");
			return;
		}
		int stringLength = strlen(event_title + 1);
		event_title[stringLength] = '\0';

		fputs("Enter the start time of the event you would like to delete: ", stdout);
		if (!createATime(event_time)) // Grab the start time
		{
			printf("\n");
			return;
		}

		time_t timeNum = mktime(event_time);
		char* c_time_string;
		c_time_string = ctime(&timeNum);

		if (isEventInSchedule(p_schedule, event_title, event_time)) // Check if an event by the given information actually exists in the schedule.
		{
			eventWasFound = true;

			EVENT eventToDelete = getEvent(p_schedule, event_title, event_time);
			removeEventFromSchedule(p_schedule, eventToDelete);

			printf("\nCalendar entry for %s at %s has been deleted.\n\n", event_title, c_time_string); // print a confirmation
		}
		else
		{
			printf("\nCalendar entry for %s at %s not found.\n\n", event_title, c_time_string); 
		}
	} while (!eventWasFound);

	return;
}

void menuUpdateEvent(P_SCHEDULE p_schedule) // Prompts user to input information about an event they want to update and then sends them to the update event menu.
{
	char event_title[MAX_USER_INPUT_LEN];
	struct tm* event_time = malloc(sizeof(struct tm));
	bool eventWasFound;

	if (isScheduleEmpty(p_schedule)) // not worth continuing if the schedule is empty
	{
		fputs("The schedule is currently empty.\n\n", stdout);
		return;
	}

	do // The loop here is to reprompt the user again if the event the user has inputted is not found.
	{
		fputs("Enter the name of the event you would like to update (0 to quit): ", stdout);

		eventWasFound = false;

		// Get the event title.
		fgets(event_title, MAX_LOCATION_LEN, stdin);
		if (!strcmp(event_title, "0\n")) // Check for exit
		{
			printf("\n");
			return;
		}
		int stringLength = strlen(event_title + 1);
		event_title[stringLength] = '\0';

		// Get the event start time.
		fputs("\nEnter the start time of the event you would like to update by answering the following questions\n", stdout);
		if (!createATime(event_time)) // Check for exit.
		{
			printf("\n");
			return;
		}

		time_t timeNum = mktime(event_time);
		char* c_time_string;
		c_time_string = ctime(&timeNum);

		if (isEventInSchedule(p_schedule, event_title, event_time)) // Check for the existence of the event being searched for.
		{
			eventWasFound = true;

			EVENT eventToUpdate = getEvent(p_schedule, event_title, event_time);
			if (updateEventInSchedule(p_schedule, eventToUpdate)) // The return of this funciton is only used to confirm with the user if changes were made.
				printf("\nCalendar entry for %s at %s has been updated.\n\n", event_title, c_time_string); // print a confirmation
			else
				printf("\nNo changes were saved to your schedule.\n\n");
		}
		else
		{
			printf("\nCalendar entry for %s at %s not found.\n\n", event_title, c_time_string);
		}
	} while (!eventWasFound);

	return;
}

void menuDisplayRangeOfEvents(P_SCHEDULE p_schedule) // Prompts the user to input a start and end time to define a range and then prints all events with start times within that range.
{
	bool validTime = false;

	if (isScheduleEmpty(p_schedule)) // not worth continuing if the schedule is empty
	{
		fputs("\nThe schedule is currently empty.\n\n", stdout);
		return;
	}

	// Get the begining time for the range.
	struct tm* start_time = malloc(sizeof(struct tm));
	do // Loop to reprompt the user if an invalid time was entered.
	{
		fputs("\nChoose when the range starts by answering the following questions.\n", stdout);

		if (!createATime(start_time))
		{
			printf("\n");
			return;
		}
		if (difftime(mktime(start_time), time(NULL)) <= 0) // Start time of range must be before the current time.
		{
			printf("\nError! The start of the range must start in the future. Try again!\n");
			validTime = false;
		}
		else
			validTime = true;

	} while (!validTime);

	//Get the end time for the range.
	struct tm* end_time = malloc(sizeof(struct tm));
	validTime = false;
	do // loop again just in case the user inputs an invalid time.
	{
		fputs("\nChoose when the range ends by answering the following questions.\n", stdout);

		if (!createATime(end_time))
		{
			printf("\n");
			return;
		}
		if (difftime(mktime(end_time), mktime(start_time)) <= 0)
		{
			printf("\nError! The end of the range must be after the starting time.\n\n");
			validTime = false;
		}
		else
			validTime = true;
	} while (!validTime);

	TIMES range; // Build a times struct since there is still a start and end time even though they're for a range this time and not an event.
	range.start_time = start_time;
	range.end_time = end_time;

	printScheduleInRange(p_schedule, range);

	free(start_time); // Memory management.
	free(end_time);
}

bool menuSearchSchedule(P_SCHEDULE p_schedule) // Grabs the title and start time of an event and uses it to identify the event in the schedule and prints it.
{
	char event_title[MAX_USER_INPUT_LEN];
	struct tm* event_time = malloc(sizeof(struct tm));
	bool eventWasFound;

	if (isScheduleEmpty(p_schedule)) // not worth continuing if the schedule is empty
	{
		fputs("\nThe schedule is currently empty.\n\n", stdout);
		return;
	}

	do // do loop just in case of typos, it'll reprompt.
	{
		eventWasFound = false;

		// Grabs the event title.
		fputs("\nEnter the name of the event you would like to search for (0 to quit): ", stdout);
		fgets(event_title, MAX_LOCATION_LEN, stdin);
		if (!strcmp(event_title, "0\n")) // Check for exit condition.
		{
			printf("\n");
			return;
		}
		int stringLength = strlen(event_title + 1);
		event_title[stringLength] = '\0';

		// Grabs the event start time.
		fputs("Enter the start time of the event you are searching for by answering the following question:\n", stdout);
		if (!createATime(event_time))
		{
			printf("\n");
			return;
		}

		time_t timeNum = mktime(event_time);
		char* c_time_string;
		c_time_string = ctime(&timeNum);

		if (isEventInSchedule(p_schedule, event_title, event_time)) // Verifies event existence.
		{
			eventWasFound = true;

			EVENT eventToPrint = getEvent(p_schedule, event_title, event_time);
			fputs("\nSearch results:\n", stdout);
			printEventInSchedule(eventToPrint);
		}
		else
		{
			printf("\nCalendar entry for %s at %s not found.\n\n", event_title, c_time_string); // print confirmation if the event was not found.
		}
	} while (!eventWasFound);

	free(event_time); // Memory management.

	return;
}