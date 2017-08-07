#ifndef INFORMATION_H_INCLUDED
#define INFORMATION_H_INCLUDED

#include "player_data.h"
#include "move_done.h"

struct Information
{
	MoveDone moveBefore2;
	MoveDone moveBefore;
	MoveDone moveLast;
	int piles[5];
	int lives;
	int hints;
	int cardsLeft;
	int clbt[5][5]; //cardsLeftByType
    PlayerData next;
    PlayerData prev;
	Card cards[CARDS_IN_HAND];
};

#endif // INFORMATION_H_INCLUDED
