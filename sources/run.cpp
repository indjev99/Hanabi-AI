#include "../headers/run.h"
#include "../headers/play_game.h"
#include "../headers/player_human.h"
#include "../headers/player_random.h"
#include "../headers/player_strategy.h"
#include "../headers/player_neural_network.h"

#include<iostream>
#include<algorithm>
#include<stdlib.h>
#include<conio.h>
#include<time.h>
using namespace std;

const int NUM_IN_GEN=50;
const int EXPERIMENTS=5;

PlayerHuman human;
PlayerRandom r1,r2,r3;
PlayerStrategy s1,s2,s3;
PlayerNeuralNetwork nn[NUM_IN_GEN];
double score;

bool cmpByScore(const Player &p1, const Player &p2)
{
	return p1.score>p2.score;
}

void run()
{
	double st,ct;
	double sum=0;

	/*for (int i=0;i<NUM_IN_GEN;++i)
	{
		nn[i].setTopology({0,25,25});
		nn[i].randomise();
	}
	int c=0;
	while (1)
	{
		/*if (c==0)
		{
			getch();
			score=play_game(&nn[0],&nn[0],&nn[0],1);
			cout<<score<<endl;
			getch();
			system("cls");
		}* /
		st=clock();
		sum=0;
		for (int i=0;i<NUM_IN_GEN;++i)
		{
			nn[i].score=0;
			for (int j=0;j<EXPERIMENTS;++j)
			{
				nn[i].score+=play_game(&nn[i],&s1,&s2,0);
			}
			sum+=nn[i].score;
		}
		sort(nn,nn+NUM_IN_GEN,cmpByScore);
		for (int i=0;i<NUM_IN_GEN/2;++i)
		{
			nn[NUM_IN_GEN/2+i]=nn[i];
			nn[NUM_IN_GEN/2+i].mutate();
		}
		ct=clock();
		cout<<"top avg score: "<<nn[0].score/EXPERIMENTS<<'\n';
		cout<<"avg score: "<<sum/NUM_IN_GEN/EXPERIMENTS<<'\n';
		cout<<"time "<<(ct-st)/CLOCKS_PER_SEC<<"\n\n";
	}*/


	st=clock();
	score=0;
	for (int i=0;i<10000;++i)
	{
		//system("cls");
		score=play_game(&r1,&s2,&s3,0);
		sum+=score;
		//cout<<score<<endl;
		//getch();
	}
	ct=clock();
	cout<<sum/10000<<endl;
	cout<<(ct-st)/CLOCKS_PER_SEC<<endl;
}
