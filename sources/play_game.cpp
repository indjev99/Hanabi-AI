#include "../headers/play_game.h"
#include "../headers/information.h"
#include "../headers/constants.h"

#include<stdlib.h>
#include<algorithm>

#include "../headers/print_card.h"
#include<iostream>

Card deck[64];
int deckPoss;
Information info;
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

void initialise_tokens()
{
	info.lives=INITIAL_LIFE_TOKENS;
	info.hints=INITIAL_HINT_TOKENS;
}

Player *players[3];
void initialise_players(bool print)
{
	for (int i=0;i<3;++i)
	{
		players[i]->init();
		players[i]->print=0;
	}
	players[0]->print=print;
}

void initialise_clbt()
{
	for (int i=0;i<5;++i)
	{
		info.clbt[i][1-1]=3;
		for (int j=2;j<=5;++j)
		{
			info.clbt[i][j-1]=2;
		}
		info.clbt[i][5-1]=1;
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
			playerData[i].cardKnowledge[j]={0,0};
		}
	}
}

void initialise_piles()
{
	for (int i=0;i<5;++i)
	{
		info.piles[i]=0;
	}
}

double game_score;
void initialise_score()
{
	game_score=0;
}

void initialise_moves()
{
	info.moveBefore2.type=-1;
	info.moveBefore2.player=0;
	info.moveBefore2.card={0,0};
	info.moveBefore2.cardNumber=0;
	info.moveBefore2.success=0;
	info.moveBefore=info.moveBefore2;
	info.moveLast=info.moveBefore;
}
void make_info(int currPlayer)
{
	info.cardsLeft=deckPoss;
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
	currMove.type=(currMove.type-1)%4+1;
	currMove.player=(currMove.player-1)%2+1;
	currMove.card=(currMove.card-1)%CARDS_IN_HAND+1;

	info.moveBefore2=info.moveBefore;
	info.moveBefore=info.moveLast;
	auto &moveLast=info.moveLast;
	apply_move:
	moveLast.type=currMove.type;
	moveLast.cardNumber=currMove.card-1;

	if (currMove.type==1 || currMove.type==2)
	{
		moveLast.player=0;
		auto &playedCard=playerData[currPlayer].cards[currMove.card-1];
		moveLast.card=playedCard;
		if (currMove.type==1)
		{
			if (info.piles[playedCard.col-1]==playedCard.num-1)
			{
				game_score+=1;
				++info.piles[playedCard.col-1];
				if (info.piles[playedCard.col-1]==5) ++info.hints;
				moveLast.success=1;
			}
			else
			{
				--info.lives;
				moveLast.success=0;
			}
		}
		else ++info.hints;

		--info.clbt[playedCard.col-1][playedCard.num-1];

		if (info.hints>INITIAL_HINT_TOKENS) info.hints=INITIAL_HINT_TOKENS;

		playedCard={0,0};
		if (deckPoss>0) playedCard=deck[--deckPoss];
		playerData[currPlayer].cardKnowledge[currMove.card-1]={0,0};

	}
	else
	{
		moveLast.player=currMove.player;
		auto &target=playerData[(currPlayer+currMove.player)%3];
		auto &chosenCard=target.cards[currMove.card-1];
		if (info.hints==0 || chosenCard.col==0)
		{
			currMove.type=2;
			goto apply_move;
		}
		--info.hints;
		if (currMove.type==3)
		{
			moveLast.card=card_with_knowledge(chosenCard,{0,1});
			for (int i=0;i<CARDS_IN_HAND;++i)
			{
				if (target.cards[i].num==chosenCard.num)
				{
					target.cardKnowledge[i].know_num=true;
				}
			}
		}
		else
		{
			moveLast.card=card_with_knowledge(chosenCard,{1,0});
			for (int i=0;i<CARDS_IN_HAND;++i)
			{
				if (target.cards[i].col==chosenCard.col)
				{
					target.cardKnowledge[i].know_col=true;
				}
			}
		}
	}
	players[currPlayer]->played_move(moveLast);
}

double play_game(Player *p1, Player *p2, Player *p3, bool print)
{
	players[0]=p1;
	players[1]=p2;
	players[2]=p3;
	initialise_deck();
	initialise_tokens();
	initialise_players(print);
	deal_cards();
	initialise_clbt();
	initialise_piles();
	initialise_score();
	initialise_moves();

	/*for (int i=50-1;i>=0;--i)
	{
		print_card(deck[i]);
		cout<<" ";
	}
	cout<<endl;
	cout<<endl;**/

	int currPlayer=0;
    while(deckPoss>0 && game_score<25 && info.lives>0)
	{
		turn(currPlayer);
		++currPlayer;
		currPlayer%=3;
	}
	for (int i=0;i<3 && game_score<25 && info.lives>0;++i)
	{
		turn(currPlayer);
		++currPlayer;
		currPlayer%=3;
	}

	if (info.lives==0) game_score=game_score/5-5;

	if (print)
	{
		if (currPlayer==0) print_move(info.moveBefore2,currPlayer);
		if (currPlayer==0 || currPlayer==2) print_move(info.moveBefore,(currPlayer+1)%3);
		print_move(info.moveLast,(currPlayer+2)%3);
		if (info.moveLast.type!=-1) std::cout<<std::endl;
	}

	return game_score;
}
