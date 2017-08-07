#ifndef PLAYER_STRATEGY_H_INCLUDED
#define PLAYER_STRATEGY_H_INCLUDED

#include "player.h"
#include "constants.h"

struct PlayerStrategy:Player
{
	int currDraw;
	int drawn[CARDS_IN_HAND];
	virtual void init();
	virtual Move do_move(const Information &info);
	virtual void played_move(const MoveDone &moveDone);
};

#endif // PLAYER_STRATEGY_H_INCLUDED
