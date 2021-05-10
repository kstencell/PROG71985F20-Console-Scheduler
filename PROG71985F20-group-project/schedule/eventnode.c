//
// Group Assignment
// PROG71985 - F20
// Karl Stencell, Thomas Horvath, Gautam Singh - Dec 2020
//
// REVISION HISTORY
// 1.0		2020-Dec 11		initial
//
// VERSION 1.0 NOTES
// This file contains functionality pertaining to nodes for the schedule linked list.

#include <stdlib.h>
#include <stdio.h>
#include "eventnode.h"

P_EVENT_NODE createEventNode(EVENT event) // initialize a node and fill it with an event struct
{
	P_EVENT_NODE newNode = (P_EVENT_NODE)malloc(sizeof(EVENT_NODE));
	if (!newNode)
	{
		fprintf(stderr, "Error allocating memory.\n");
		exit(1);
	}
	newNode->nodeData = copyEvent(event);
	newNode->next = NULL;

	return newNode;
}

P_EVENT_NODE getEventNodeNextEventNode(P_EVENT_NODE eventNode)
{
	return eventNode->next;
}

void setEventNodeNextEventNode(P_EVENT_NODE sourceEventNode, P_EVENT_NODE newNextEventNode)
{
	sourceEventNode->next = newNextEventNode;
}

void disposeEventNode(P_EVENT_NODE eventNode) // memory management.
{
	disposeEvent(eventNode->nodeData);
	free(eventNode);
}