//
// Group Assignment
// PROG71985 - F20
// Karl Stencell, Thomas Horvath, Gautam Singh - Dec 2020
//
// REVISION HISTORY
// 1.0		2020-Dec 11		initial
//
// VERSION 1.0 NOTES
// This file is the header file for eventnode.c

#pragma once

#include "event.h"

typedef struct eventnode //nodes for a linked list that contain events
{
	EVENT nodeData;
	struct eventnode* next;
}EVENT_NODE, *P_EVENT_NODE;

// PROTOTYPES
P_EVENT_NODE createEventNode(EVENT);
void setEventNodeNextEventNode(P_EVENT_NODE, P_EVENT_NODE);
P_EVENT_NODE getEventNodeNextEventNode(P_EVENT_NODE);
void disposeEventNode(P_EVENT_NODE);