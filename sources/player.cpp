#include "../headers/constants.h"
#include "../headers/player.h"
#include "../headers/print_card.h"

#include<iostream>
#include<stdlib.h>
#include<conio.h>
using namespace std;

void Player::init() {}

void print_move(const MoveDone &moveDone, int player)
{
	if (moveDone.type==-1) return;
	int player2;
	string playerName;
	string player2Name;
	player2=(player+moveDone.player)%3;
	if (player==0) playerName="You";
	else
	{
		playerName="Player ";
		playerName+=('0'+player);
	}
	if (player2==0) player2Name="You";
	else
	{
		player2Name="Player ";
		player2Name+=('0'+player2);
	}

	if (moveDone.type==1 || moveDone.type==2)
	{
		if (moveDone.type==1 && moveDone.success==1)
		{
			cout<<playerName<<" successfully played a ";
			print_card(moveDone.card);
			cout<<".\n";
		}
		else if (moveDone.type==1 && moveDone.success==0)
		{
			cout<<playerName<<" unsuccessfully played a ";
			print_card(moveDone.card);
			cout<<" and lost a life.\n";
		}
		else
		{
			cout<<playerName<<" discarded a ";
			print_card(moveDone.card);
			cout<<".\n";
		}
	}
	else
	{
		cout<<playerName<<" hinted "<<player2Name;
		if (moveDone.type==3)
		{
			cout<<" the colour ";
		}
		else
		{
			cout<<" the number ";
		}
		print_card(moveDone.card);
		cout<<".\n";
	}
}
void Player::played_move(const MoveDone &moveDone)
{
	print_move(moveDone,0);
	getch();
}
Move Player::do_move(const Information &info)
{
	system("cls");
	getch();

	print_move(info.moveBefore2,0);
	print_move(info.moveBefore,1);
	print_move(info.moveLast,2);
	if (info.moveLast.type!=-1) cout<<'\n';


	cout<<"Piles:";
	for (int i=0;i<5;++i)
	{
		cout<<' ';
		print_card({i+1,info.piles[i]});
	}
	cout<<"\n\n";

	cout<<"Your cards:";
	for (int i=0;i<CARDS_IN_HAND;++i)
	{
		cout<<' ';
		print_card(info.cards[i]);
	}
	cout<<'\n';

	auto &next=info.next;
	cout<<"Player 1's cards:";
	for (int i=0;i<CARDS_IN_HAND;++i)
	{
		cout<<' ';
		print_card(next.cards[i]);
	}
	cout<<"  But he knows:";
	for (int i=0;i<CARDS_IN_HAND;++i)
	{
		cout<<' ';
		print_card(card_with_knowledge(next.cards[i],next.cardKnowledge[i]));
	}
	cout<<'\n';

	auto &prev=info.prev;
	cout<<"Player 2's cards:";
	for (int i=0;i<CARDS_IN_HAND;++i)
	{
		cout<<' ';
		print_card(prev.cards[i]);
	}
	cout<<"  But he knows:";
	for (int i=0;i<CARDS_IN_HAND;++i)
	{
		cout<<' ';
		print_card(card_with_knowledge(prev.cards[i],prev.cardKnowledge[i]));
	}
	cout<<"\n\n";

	char colour;
	auto *clbt=info.cardsLeftByType;
	cout<<"Cards left: "<<info.cardsLeft<<'\n';
	cout<<"By type:\n\n";
	cout<<"  ";
	for (int i=0;i<5;++i)
	{
		cout<<' '<<i+1;
	}
	cout<<'\n';
	for (int i=0;i<5;++i)
	{
		switch(i+1)
		{
			case 1: colour='W';
					break;
			case 2: colour='B';
					break;
			case 3: colour='G';
					break;
			case 4: colour='Y';
					break;
			case 5: colour='R';
					break;
		}
		cout<<colour<<':';
		for (int j=0;j<5;++j)
		{
			cout<<' ';
			print_card({i+1,clbt[i][j]});
		}
		cout<<'\n';
	}
	cout<<'\n';

	cout<<"Information tokens: "<<info.hints<<'/'<<INITIAL_HINT_TOKENS<<'\n';
	cout<<"Life tokens: "<<info.lives<<'/'<<INITIAL_LIFE_TOKENS<<'\n';
	cout<<'\n';

	Move currMove;
	cout<<"1 - Play\n2 - Discard\n3 - Hint colour\n4 - Hint number\nYour move: ";
	cin>>currMove.type;
	if (currMove.type==3 || currMove.type==4)
	{
		cout<<"Hint to player: ";
		cin>>currMove.player;
	}
	cout<<"Card number: ";
	cin>>currMove.card;

	return currMove;
}
