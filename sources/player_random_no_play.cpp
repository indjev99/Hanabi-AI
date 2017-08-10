#include "../headers/player_random_no_play.h"

#include<iostream>
#include<stdlib.h>

void PlayerRandomNoPlay::init() {}

void PlayerRandomNoPlay::played_move(const MoveDone &moveDone) {};

Move PlayerRandomNoPlay::do_move(const Information &info)
{
	if (print)
	{
		print_move(info.moveBefore2,0);
		print_move(info.moveBefore,1);
		print_move(info.moveLast,2);
		if (info.moveLast.type!=-1) std::cout<<std::endl;
	}

    Move currMove;
    currMove.type=rand()%3+2;
    currMove.card=rand()%5+1;
    currMove.player=rand()%2+1;
    return currMove;
}
