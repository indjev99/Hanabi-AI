#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include "move.h"
#include "information.h"

struct Player
{
	void init();
	Move do_move(const Information &info);
	void played_move(const MoveDone &moveDone);
};

void print_move(const MoveDone &moveDone, int player);

#endif // PLAYER_H_INCLUDED
