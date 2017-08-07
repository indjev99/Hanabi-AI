#include "../headers/run.h"
#include "../headers/play_game.h"
#include "../headers/player_human.h"
#include "../headers/player_random.h"
#include "../headers/player_strategy.h"

#include<iostream>
#include<stdlib.h>
#include<conio.h>
using namespace std;

PlayerHuman human;
PlayerRandom r1,r2,r3;
PlayerStrategy s1,s2,s3;
double score;
void run()
{
	int sum=0;
	for (int i=0;i<10000;++i)
	{
		system("cls");
		score=play_game(&s1,&s2,&s3,1);
		sum+=score;
		cout<<score<<endl;
		getch();
	}
	cout<<sum<<endl;
}
