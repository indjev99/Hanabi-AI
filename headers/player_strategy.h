#ifndef PLAYER_STRATEGY_H_INCLUDED
#define PLAYER_STRATEGY_H_INCLUDED

#include "player.h"

struct PlayerStrategy:Player
{
	virtual void init();
	virtual Move do_move(const Information &info);
	virtual void played_move(const MoveDone &moveDone);
};

#endif // PLAYER_STRATEGY_H_INCLUDED
