#include "../headers/constants.h"
#include "../headers/player.h"
#include "../headers/print_card.h"

#include<iostream>

void print_move(const MoveDone &moveDone, int player)
{
	if (moveDone.type==-1) return;
	int player2;
	std::string playerName;
	std::string player2Name;
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
			std::cout<<playerName<<" successfully played a ";
			print_card(moveDone.card);
			std::cout<<".\n";
		}
		else if (moveDone.type==1 && moveDone.success==0)
		{
			std::cout<<playerName<<" unsuccessfully played a ";
			print_card(moveDone.card);
			std::cout<<" and lost a life.\n";
		}
		else
		{
			std::cout<<playerName<<" discarded a ";
			print_card(moveDone.card);
			std::cout<<".\n";
		}
	}
	else
	{
		std::cout<<playerName<<" hinted "<<player2Name;
		if (moveDone.type==3)
		{
			std::cout<<" the number ";
		}
		else
		{
			std::cout<<" the colour ";
		}
		print_card(moveDone.card);
		std::cout<<".\n";
	}
}
