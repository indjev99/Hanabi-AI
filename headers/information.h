#ifndef INFORMATION_H_INCLUDED
#define INFORMATION_H_INCLUDED

#include "player_data.h"

struct Information
{
	int piles[5];
	int lives;
	int hints;
	int cardsLeft;
	int cardsLeftByType[5][5];
    PlayerData next;
    PlayerData prev;
	Card cards[CARDS_IN_HAND];
};

#endif // INFORMATION_H_INCLUDED
