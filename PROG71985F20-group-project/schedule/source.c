//
// Group Assignment
// PROG71985 - F20
// Karl Stencell, Thomas Horvath, Gautam Singh - Dec 2020
//
// REVISION HISTORY
// 1.0		2020-Dec 11		initial
//
// VERSION 1.0 NOTES
// This file contains the start of the program where it checks for stored data and then jumps right into the main menu.

#include <stdio.h>
#include <time.h>
#include <string.h>
#include "scheduleADT.h"
#include "testSchedule.h"
#include "menu.h"

int main(void)
{

	SCHEDULE schedule = createSchedule();
	P_SCHEDULE p_schedule = &schedule;

	if (!loadScheduleFromDisk(p_schedule, "datafile.txt")) // if there's data stored then read it. otherwise the testing event generator can be used or start with a blank schedule
	{
		fprintf(stderr, "\nNo previous schedule data found.\n\n");
		generateTestSchedule(p_schedule); // TESTING FUNCTION! GENERATES 10 EVENTS ALL SEPARATED 2 DAYS APART IF THERE IS NO SAVED DATA.
	}

	while (true) // the main engine of the program that runs the main menu around in a circle until terminated by the user
	{
		printMainMenuOptions();
		executeUserOptionChoice(p_schedule);
	}

	return 0;
}