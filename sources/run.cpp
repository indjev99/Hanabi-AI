#include "../headers/run.h"
#include "../headers/play_game.h"
#include "../headers/player.h"

#include<iostream>
#include<stdlib.h>
using namespace std;

Player human1,human2,human3;
double score;
void run()
{
	score=play_game(human1,human2,human3);
	system("cls");
	cout<<score<<endl;
}
