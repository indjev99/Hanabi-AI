#ifndef PLAYER_RANDOM_H_INCLUDED
#define PLAYER_RANDOM_H_INCLUDED

#include "player.h"

struct PlayerRandom:Player
{
	void init();
	Move do_move(const Information &info);
	void played_move(const MoveDone &moveDone);
};

#endif // PLAYER_RANDOM_H_INCLUDED
