#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include "move.h"
#include "information.h"

struct Player
{
	double score;
	bool print;
	virtual void init() =0;
	virtual Move do_move(const Information &info) =0;
	virtual void played_move(const MoveDone &moveDone) =0;
	virtual ~player() = default;
};

void print_move(const MoveDone &moveDone, int player);

#endif // PLAYER_H_INCLUDED
