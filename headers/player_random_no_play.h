#ifndef PLAYER_RANDOM_NO_PLAY_H_INCLUDED
#define PLAYER_RANDOM_NO_PLAY_H_INCLUDED

#include "player.h"

struct PlayerRandomNoPlay:Player
{
	void init();
	Move do_move(const Information &info);
	void played_move(const MoveDone &moveDone);
};

#endif // PLAYER_RANDOM_NO_PLAY_H_INCLUDED
