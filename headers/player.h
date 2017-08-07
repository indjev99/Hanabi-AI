#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include "move.h"
#include "information.h"

struct Player
{
	void init();
	Move do_move(const Information &info);
	void played_card_successful(const Card &playedCard);
	void played_card_unsuccessful(const Card &playedCard);
	void discarded_card(const Card &playedCard);
};

#endif // PLAYER_H_INCLUDED
