//
// Group Assignment
// PROG71985 - F20
// Karl Stencell, Thomas Horvath, Gautam Singh - Dec 2020
//
// REVISION HISTORY
// 1.0		2020-Dec 11		initial
//
// VERSION 1.0 NOTES
// This file contains the interface functionality with the schedule struct (which "contains" the linked list of events).

#include <string.h>
#include "scheduleADT.h"
#include "event.h"

SCHEDULE createSchedule() //pops the struct into existence.
{
	SCHEDULE schedule = { 0 };
	return schedule;
}

bool addEventToSchedule(P_SCHEDULE p_schedule, EVENT thisEvent) // takes a new event, wraps it into a node, and adds it to the linked list. In chronological order!
{
	P_EVENT_NODE newNode = createEventNode(thisEvent);

	if (p_schedule->events == NULL) // schedule is empty
	{
		setEventNodeNextEventNode(newNode, p_schedule->events);
		p_schedule->events = newNode;
	}
	else
	{
		P_EVENT_NODE current = p_schedule->events;
		P_EVENT_NODE prev = NULL;

		// The logic below is how the program determines were to place the node in the list based on its start time relative to the other nodes
		// This guarantees that the linked list is always in chronological order which removes the pain of algorithmically sorting them later to print
		while (current != NULL && (difftime(getEventStartTime(thisEvent), getEventStartTime(current->nodeData)) > 0))
		{
			prev = current;
			current = getEventNodeNextEventNode(current);
		}

		if (prev == NULL && current != NULL) // add new node to the front of the list
		{
			setEventNodeNextEventNode(newNode, current);
			p_schedule->events = newNode;
		}
		else if (prev != NULL && current != NULL) // add new node somewhere in the middle of the list
		{
			setEventNodeNextEventNode(prev, newNode);
			setEventNodeNextEventNode(newNode, current);
		}
		else if (prev != NULL && current == NULL) // add new node to the end of the list
		{
			setEventNodeNextEventNode(prev, newNode);
		}
	}
	return true;
}

bool removeEventFromSchedule(P_SCHEDULE p_schedule, EVENT eventToDelete) // finds an event and unlinks it from the list and then disposes of it
{
	P_EVENT_NODE current = p_schedule->events;

	if (current == NULL)
	{
		fputs("\nThe schedule is currently empty.\n\n", stdout);
		return false;
	}
	else if (compareEvents(current->nodeData, eventToDelete)) // remove the only event in the list.
	{
		if (getEventNodeNextEventNode(current) != NULL)
			p_schedule->events = getEventNodeNextEventNode(current);
		else
			p_schedule->events = NULL;
		disposeEventNode(current); // memory management
		return true;
	}
	else
	{
		P_EVENT_NODE prev = NULL;

		while (current != NULL && !compareEvents(current->nodeData, eventToDelete)) // iterates through the list until it finds the specific event that the user wants to delete
		{
			prev = current;
			current = getEventNodeNextEventNode(current);
		}

		if (current == NULL) // event wasn't found
			return false;

		setEventNodeNextEventNode(prev, getEventNodeNextEventNode(current)); //unlink the event we no longer want

		disposeEventNode(current); // memory management.
		return true;
	}
}

bool isScheduleEmpty(P_SCHEDULE p_schedule)
{
	if (p_schedule->events == NULL)
		return true;
	else
		return false;
}

bool isEventInSchedule(P_SCHEDULE p_schedule, char event_title[], struct tm* event_time) // confirms existence of an event in the list
{
	if (p_schedule->events == NULL) // empty list so definitely false
	{
		return false;
	}
	else
	{
		P_EVENT_NODE current = p_schedule->events;
		while (current != NULL)
		{
			// if the event title and start time are the same then the event has been found!
			if (!strcmp(getEventTitle(current->nodeData),event_title) && difftime(mktime(event_time), getEventStartTime(current->nodeData) == 0))
				return true;
			current = getEventNodeNextEventNode(current);
		}
	}
}

void printEventInSchedule(EVENT eventToPrint) // used for single event printing
{
	printEvent(eventToPrint);
}

EVENT getEvent(P_SCHEDULE p_schedule, char event_title[], struct tm* event_time) // finds a single event and return the actual struct
{
	P_EVENT_NODE current = p_schedule->events;
	while (current != NULL)
	{
		// if the event title and start time are the same then the event has been found!
		if (!strcmp(getEventTitle(current->nodeData), event_title) && difftime(mktime(event_time), getEventStartTime(current->nodeData) == 0))
			return current->nodeData;
		current = getEventNodeNextEventNode(current);
	}
}

// The assignment specifies printing a single event as a requirement. The program does that in several instances for confirmations
// however I added this to be explicit that you can print an event anytime you want from the main menu.
void displayNextUpcomingEventInSchedule(P_SCHEDULE p_schedule) 
{
	P_EVENT_NODE current = p_schedule->events;

	if (current == NULL)
		fputs("\nThe schedule is currently empty.\n\n", stdout);
	else
		printEvent(current->nodeData); // just prints the first event in the list which also by design is the earliest event.
}

void displayAllEventsInSchedule(P_SCHEDULE p_schedule) 
{
	P_EVENT_NODE current = p_schedule->events;

	if (current == NULL)
		fputs("\nThe schedule is currently empty.\n\n", stdout);
	else
	{
		while (current != NULL) // jumps through the list and just outputs every event until the end.
		{
			printEvent(current->nodeData);
			current = getEventNodeNextEventNode(current);
		}
	}
}

bool updateEventInSchedule(P_SCHEDULE p_schedule, EVENT event)
{
	if (p_schedule->events == NULL) // empty schedule
	{
		return false;
	}
	else
	{
		P_EVENT_NODE current = p_schedule->events;
		while (current != NULL)
		{
			if (compareEvents(current->nodeData, event)) // find the actual event in memory that the user wants to update
			{
				updateEvent(&current->nodeData); // send that event to the update menu
				return true;
			}
			current = getEventNodeNextEventNode(current);
		}
	}

	return false;
}

void printScheduleInRange(P_SCHEDULE p_schedule, TIMES range) // prints only events that have a start time within the user specfied range
{
	P_EVENT_NODE current = p_schedule->events;

	if (current == NULL)
		fputs("The schedule is currently empty.", stdout);
	else
	{
		while (current != NULL)
		{
			// checks whether the start time is within the given range or not
			if ((difftime(getEventStartTime(current->nodeData), getStartTime(range)) >= 0) && (difftime(getEventStartTime(current->nodeData), getEndTime(range)) <= 0))
			{
				printEvent(current->nodeData);
			}
			current = getEventNodeNextEventNode(current);
		}
	}
}

bool saveScheduleToDisk(P_SCHEDULE p_schedule, char filename[FILENAME_MAX])
{
	FILE* fp;
	if ((fp = fopen(filename, "w+")) == NULL)
		return false;

	if (p_schedule->events == NULL)
	{
		fprintf(stderr, "No events in schedule.\n");
		return true;
	}
	else
	{
		P_EVENT_NODE current = p_schedule->events;

		while (current != NULL) // goes to each node in the list and exports the data
		{
			streamPrintEventData(fp, current->nodeData); // have to juggle the points a bit so that the loop can iterate while the nodes are being freed.
			P_EVENT_NODE temp = getEventNodeNextEventNode(current);
			disposeEventNode(current); // memory management.
			current = temp;
		}
		return true;
	}
}

bool loadScheduleFromDisk(P_SCHEDULE p_schedule, char filename[FILENAME_MAX])
{
	FILE* fp;
	if ((fp = fopen(filename, "r")) == NULL) // didn't find file
		return false;
	else
	{
		char buffer[MAX_BUFFER];
		while (fgets(buffer, MAX_BUFFER, fp) != NULL) // you have to get a char/string from the file to then check it so this needs to keep track of what it uses to check
		{
			EVENT newEvent = streamReadEventData(fp, buffer); // create the events from data in text file
			addEventToSchedule(p_schedule, newEvent); // adds them to the schedule as if they were just inputted
		}
		return true;
	}
}