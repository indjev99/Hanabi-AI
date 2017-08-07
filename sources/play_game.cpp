#include "../headers/play_game.h"
#include "../headers/information.h"
#include "../headers/constants.h"

#include<stdlib.h>
#include<algorithm>

#include "../headers/print_card.h"
#include<iostream>
#include<conio.h>
using namespace std;

Card deck[64];
int deckPoss;
void initialise_deck()
{
	deckPoss=0;
	for (int i=1;i<=5;++i)
	{
		deck[deckPoss++]={i,1};
		deck[deckPoss++]={i,1};
		deck[deckPoss++]={i,1};
		for (int j=2;j<5;++j)
		{
			deck[deckPoss++]={i,j};
			deck[deckPoss++]={i,j};
		}
		deck[deckPoss++]={i,5};
	}
	int swapPoss;
	for (int i=deckPoss;i>0;--i)
	{
		swapPoss=rand()%i;
		std::swap(deck[i-1],deck[swapPoss]);
	}
}

int lives;
int hints;
void initialise_tokens()
{
	lives=INITIAL_LIFE_TOKENS;
	hints=INITIAL_HINT_TOKENS;
}

Player *players[3];
void initialise_players()
{
	for (int i=0;i<3;++i)
	{
		players[i]->init();
	}
}

int clbt[5][5];
void initialise_clbt()
{
	for (int i=0;i<5;++i)
	{
		clbt[i][1-1]=3;
		for (int j=2;j<=5;++j)
		{
			clbt[i][j-1]=2;
		}
		clbt[i][5-1]=1;
	}
}

PlayerData playerData[3];
void deal_cards()
{
	for (int i=0;i<3;++i)
	{
		for (int j=0;j<CARDS_IN_HAND;++j)
		{
			playerData[i].cards[j]=deck[--deckPoss];
			playerData[i].cardKnowledge[j]={false,false};
		}
	}
}

int piles[5];
void initialise_piles()
{
	for (int i=0;i<5;++i)
	{
		piles[i]=0;
	}
}

double game_score;
void initialise_score()
{
	game_score=0;
}

Information info;
void make_info(int currPlayer)
{
	for (int i=0;i<5;++i)
	{
		info.piles[i]=piles[i];
	}
	info.lives=lives;
	info.hints=hints;
	info.cardsLeft=deckPoss;
	for (int i=0;i<5;++i)
	{
		for (int j=0;j<5;++j)
		{
			info.cardsLeftByType[i][j]=clbt[i][j];
		}
	}
	info.next=playerData[(currPlayer+1)%3];
	info.prev=playerData[(currPlayer+2)%3];
	for (int i=0;i<CARDS_IN_HAND;++i)
	{
		info.cards[i]=card_with_knowledge(playerData[currPlayer].cards[i],playerData[currPlayer].cardKnowledge[i]);
	}
}
Move currMove;
void turn(int currPlayer)
{
	make_info(currPlayer);
	currMove=players[currPlayer]->do_move(info);

	apply_move:
	if (currMove.type==1 || currMove.type==2)
	{
		auto &playedCard=playerData[currPlayer].cards[currMove.card-1];

		if (currMove.type==1)
		{
			if (piles[playedCard.col-1]==playedCard.num-1)
			{
				game_score+=1;
				++piles[playedCard.col-1];
				if (piles[playedCard.col-1]==5) ++hints;
				players[currPlayer]->played_card_successful(playedCard);
			}
			else
			{
				--lives;
				players[currPlayer]->played_card_unsuccessful(playedCard);
			}
		}
		else
		{
			++hints;
			players[currPlayer]->discarded_card(playedCard);
		}

		--clbt[playedCard.col-1][playedCard.num-1];

		if (hints>INITIAL_HINT_TOKENS) hints=INITIAL_HINT_TOKENS;

		playedCard={0,0};
		if (deckPoss>0) playedCard=deck[--deckPoss];
		playerData[currPlayer].cardKnowledge[currMove.card-1]={0,0};

	}
	else
	{
		auto &target=playerData[(currPlayer+currMove.player)%3];
		auto &chosenCard=target.cards[currMove.card-1];
		if (hints==0 || chosenCard.col==0)
		{
			currMove.type=2;
			goto apply_move;
		}
		--hints;
		if (currMove.type==3)
		{
			for (int i=0;i<CARDS_IN_HAND;++i)
			{
				if (target.cards[i].col==chosenCard.col)
				{
					target.cardKnowledge[i].know_col=true;
				}
			}
		}
		else
		{
			for (int i=0;i<CARDS_IN_HAND;++i)
			{
				if (target.cards[i].num==chosenCard.num)
				{
					target.cardKnowledge[i].know_num=true;
				}
			}
		}
	}
}

double play_game(Player &p1, Player &p2, Player &p3)
{
	players[0]=&p1;
	players[1]=&p2;
	players[2]=&p3;
	initialise_deck();
	initialise_tokens();
	initialise_players();
	deal_cards();
	initialise_clbt();
	initialise_piles();
	initialise_score();

	for (int i=50-1;i>=0;--i)
	{
		print_card(deck[i]);
		cout<<" ";
	}
	cout<<endl;
	cout<<endl;

	int currPlayer=0;
    while(deckPoss>0 && game_score<25 && lives>0)
	{
		turn(currPlayer);
		++currPlayer;
		currPlayer%=3;
	}
	for (int i=0;i<3 && game_score<25 && lives>0;++i)
	{
		turn(currPlayer);
		++currPlayer;
		currPlayer%=3;
	}

	if (lives==0) game_score=game_score/5-5;

	return game_score;
}
