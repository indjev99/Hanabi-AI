#include "../headers/constants.h"
#include "../headers/player.h"
#include "../headers/print_card.h"

#include<iostream>
#include<stdlib.h>
#include<conio.h>
using namespace std;

void Player::init() {}

void Player::played_card_successful(const Card &playedCard)
{
	cout<<"You successfully played a ";
	print_card(playedCard);
	cout<<"."<<endl;
	getch();
}
void Player::played_card_unsuccessful(const Card &playedCard)
{
	cout<<"You unsuccessfully played a ";
	print_card(playedCard);
	cout<<" and lost a life."<<endl;
	getch();
}
void Player::discarded_card(const Card &playedCard)
{
	cout<<"You discarded a ";
	print_card(playedCard);
	cout<<"."<<endl;
	getch();
}

Move Player::do_move(const Information &info)
{
	system("cls");
	getch();

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
	cout<<"(1) Next player's cards:";
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
	cout<<"(2) Following player's cards:";
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
