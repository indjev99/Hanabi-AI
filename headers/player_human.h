#ifndef PLAYER_HUMAN_H_INCLUDED
#define PLAYER_HUMAN_H_INCLUDED

#include "player.h"

struct PlayerHuman:Player
{
	virtual void init();
	virtual Move do_move(const Information &info);
	virtual void played_move(const MoveDone &moveDone);
};

#endif // PLAYER_HUMAN_H_INCLUDED
