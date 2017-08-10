#ifndef PLAYER_STRATEGY_H_INCLUDED
#define PLAYER_STRATEGY_H_INCLUDED

#include "player.h"
#include "constants.h"

struct PlayerStrategy:Player
{
	void init();
	Move do_move(const Information &info);
	void played_move(const MoveDone &moveDone);
};

#endif // PLAYER_STRATEGY_H_INCLUDED
