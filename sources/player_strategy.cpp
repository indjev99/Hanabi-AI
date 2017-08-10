#include "../headers/player_strategy.h"

#include<iostream>
#include<math.h>

#include<stdlib.h>
#include<conio.h>
using namespace std;


void PlayerStrategy::init() {}

void PlayerStrategy::played_move(const MoveDone &moveDone) {}

Move PlayerStrategy::do_move(const Information &info)
{
	if (print)
	{
		print_move(info.moveBefore2,0);
		print_move(info.moveBefore,1);
		print_move(info.moveLast,2);
		if (info.moveLast.type!=-1) std::cout<<std::endl;
	}

	int clbt[5][5];
	bool playable[5][5];
	bool useless[5][5];
	bool critical[5][5];
	bool missing[5][5];

	for (int i=0;i<5;++i)
	{
		for (int j=0;j<5;++j)
		{
			clbt[i][j]=info.clbt[i][j];
		}
	}

	for (int i=0;i<5;++i)
	{
		for (int j=1;j<=5;++j)
		{
			missing[i][j-1]=0;
			playable[i][j-1]=0;
			useless[i][j-1]=1;
			critical[i][j-1]=0;
			if (j>1 && missing[i][j-2]==1)
			{
				missing[i][j-1]=1;
			}
			else
			{
				if (j>info.piles[i])
				{
					useless[i][j-1]=0;
					if (j==info.piles[i]+1)
					{
						playable[i][j-1]=1;
					}
					if (clbt[i][j-1]==0)
					{
						useless[i][j-1]=1;
						playable[i][j-1]=0;
						missing[i][j-1]=1;
					}
					else if (clbt[i][j-1]==1)
					{
						critical[i][j-1]=1;
					}
				}
			}
		}
	}

	int col;
	int num;
	for (int i=0;i<CARDS_IN_HAND;++i)
	{
		col=info.next.cards[i].col;
		num=info.next.cards[i].num;
		if (col!=0 && num!=0) --clbt[col-1][num-1];

		col=info.prev.cards[i].col;
		num=info.prev.cards[i].num;
		if (col!=0 && num!=0) --clbt[col-1][num-1];
	}

	int numPlayable[CARDS_IN_HAND];
	int numUseless[CARDS_IN_HAND];
	int numCritical[CARDS_IN_HAND];
	int numCases[CARDS_IN_HAND];

	double partPlayable[CARDS_IN_HAND];
	double partUseless[CARDS_IN_HAND];
	double partCritical[CARDS_IN_HAND];

	for (int p=0;p<CARDS_IN_HAND;++p)
	{
		numPlayable[p]=0;
		numUseless[p]=0;
		numCritical[p]=0;
		numCases[p]=0;
		for (int i=0;i<5;++i)
		{
			for (int j=0;j<5;++j)
			{
				if (clbt[i][j]>0 && (info.cards[p].col==0 || info.cards[p].col==i+1)
								 && (info.cards[p].num==0 || info.cards[p].num==j+1))
				{
					++numCases[p];
					if (playable[i][j]) ++numPlayable[p];
					if (useless[i][j]) ++numUseless[p];
					if (critical[i][j]) ++numCritical[p];
				}
			}
		}
		partPlayable[p]=numPlayable[p]*1.0/numCases[p];
		partUseless[p]=numUseless[p]*1.0/numCases[p];
		partCritical[p]=numCritical[p]*1.0/numCases[p];
	}

    Move currMove;

    currMove.type=-1;

    for (int i=0;i<CARDS_IN_HAND && currMove.type==-1;++i)
	{
		if (numPlayable[i]==numCases[i])
		{
			currMove.type=1;
			currMove.card=i+1;
		}
	}

	int repeat;
	bool found;
	if (currMove.type==-1 && info.hints>0)
	{
		currMove.player=1;
		currMove.card=0;
		repeat=2;
		while (repeat==2)
		{
			if (rand()%20<=13) currMove.type=3;
			else currMove.type=4;
			if (currMove.card==CARDS_IN_HAND)
			{
				currMove.card=CARDS_IN_HAND+1;
				break;
			}
			found=0;
			for (int i=currMove.card;i<CARDS_IN_HAND && found==0;++i)
			{
				const Card &card=info.next.cards[i];
				if (playable[card.col-1][card.num-1])
				{
					currMove.card=i+1;
					found=1;
				}
			}
			if (!found)
			{
				currMove.card=CARDS_IN_HAND+1;
				break;
			}
			repeat=0;
			if (currMove.type==3 && info.next.cardKnowledge[currMove.card-1].know_num==1)
			{
				currMove.type=4;
				++repeat;
			}
			if (currMove.type==4 && info.next.cardKnowledge[currMove.card-1].know_col==1)
			{
				currMove.type=3;
				++repeat;
			}
		}
		if (currMove.card==CARDS_IN_HAND+1)
		{
			currMove.player=2;
			currMove.card=0;
			repeat=2;
		}
		while (repeat==2)
		{
			if (rand()%20<=13) currMove.type=3;
			else currMove.type=4;
			if (currMove.card==CARDS_IN_HAND)
			{
				currMove.card=CARDS_IN_HAND+1;
				break;
			}
			found=0;
			for (int i=currMove.card;i<CARDS_IN_HAND && found==0;++i)
			{
				const Card &card=info.prev.cards[i];
				if (playable[card.col-1][card.num-1])
				{
					currMove.card=i+1;
					found=1;
				}
			}
			if (!found)
			{
				currMove.card=CARDS_IN_HAND+1;
				break;
			}
			repeat=0;
			if (currMove.type==3 && info.prev.cardKnowledge[currMove.card-1].know_num==1)
			{
				currMove.type=4;
				++repeat;
			}
			if (currMove.type==4 && info.prev.cardKnowledge[currMove.card-1].know_col==1)
			{
				currMove.type=3;
				++repeat;
			}
		}
		if (currMove.card==CARDS_IN_HAND+1)
		{
			currMove.type=-1;
		}
	}

	for (int i=0;i<CARDS_IN_HAND && currMove.type==-1 && info.hints<INITIAL_HINT_TOKENS;++i)
	{
		if (numUseless[i]==numCases[i])
		{
			currMove.type=2;
			currMove.card=i+1;
		}
	}

	double minPartCritical=2;
	double maxPartUseless=-1;
	double minPartPlayable=2;

	if (currMove.type==-1)
	{
		currMove.type=2;
		currMove.card=0;
		for (int i=0;i<CARDS_IN_HAND;++i)
		{
			if (partCritical[i]<minPartCritical)
			{
				minPartCritical=partCritical[i];
			}
		}

		for (int i=0;i<CARDS_IN_HAND;++i)
		{
			if (partCritical[i]<=minPartCritical+EPS  && partPlayable[i]<minPartPlayable)
			{
				minPartPlayable=partPlayable[i];
			}
		}

		for (int i=0;i<CARDS_IN_HAND;++i)
		{
			if (partCritical[i]<=minPartCritical+EPS && partPlayable[i]<=minPartPlayable+EPS && partUseless[i]>maxPartUseless)
			{
				maxPartUseless=partUseless[i];
				currMove.card=i+1;
			}
		}
	}

    return currMove;
}
