#ifndef MOVE_DONE_H_INCLUDED
#define MOVE_DONE_H_INCLUDED

#include "card.h"

struct MoveDone
{
	int type;
	int player;
	Card card;
	int cardNumber;
	bool success;
};

#endif // MOVE_DONE_H_INCLUDED
