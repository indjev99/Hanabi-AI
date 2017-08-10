#include "../headers/player_neural_network.h"
#include "../headers/randomisation.h"
#include "../headers/move_done.h"
#include "../headers/constants.h"

#include<iostream>
#include<math.h>

#include<stdlib.h>
#include<conio.h>
using namespace std;

void PlayerNeuralNetwork::init()
{
	for (int i=0;i<topology.size();++i)
    {
        for (int j=0;j<topology[i];++j)
		{
			neurons[i][j]=0;
		}
    }
}

void PlayerNeuralNetwork::played_move(const MoveDone &moveDone) {}

Move PlayerNeuralNetwork::do_move(const Information &info)
{
	if (print)
	{
		print_move(info.moveBefore2,0);
		print_move(info.moveBefore,1);
		print_move(info.moveLast,2);
		if (info.moveLast.type!=-1) std::cout<<std::endl;
	}

	Move currMove;
    loadInputs(info);
    forwardPropagate();
    currMove=decodeOutputs(info);
    return currMove;
}

void PlayerNeuralNetwork::setTopology(const std::vector<int>& new_topology)
{
	topology=new_topology;
    if (topology.empty())
    {
        memory_neurons=0;
        topology.push_back(INPUTS);
    }
    else
    {
        memory_neurons=topology[0];
        topology[0]=INPUTS+memory_neurons;
    }
    topology.push_back(OUTPUTS+memory_neurons);
    neurons.resize(topology.size());
    weights.resize(topology.size());
    for (int i=0;i<topology.size();++i)
    {
        neurons[i].resize(topology[i]);
        weights[i].resize(topology[i]);
        if (i)
        {
            for (int j=0;j<topology[i];++j)
            {
                weights[i][j].resize(topology[i-1]);
            }
        }
    }
}
void PlayerNeuralNetwork::randomise()
{
	for (int i=1;i<topology.size();++i)
    {
        for (int j=0;j<topology[i];++j)
        {
            for (int k=0;k<topology[i-1];++k)
            {
                randomiseVariable(weights[i][j][k],-2,2);
            }
        }
    }
}
void PlayerNeuralNetwork::mutate()
{
	for (int i=1;i<topology.size();++i)
    {
        for (int j=0;j<topology[i];++j)
        {
            for (int k=0;k<topology[i-1];++k)
            {
                mutateVariable(weights[i][j][k],-2,2);
            }
        }
    }
}

Move& PlayerNeuralNetwork::decodeOutputs(const Information &info)
{
    int ll=topology.size()-1;
    Move currMove;
    double ma=neurons[ll][0];
    currMove.type=1;
    if (neurons[ll][1]>ma)
	{
		currMove.type=2;
		ma=neurons[ll][1];
	}
	if (neurons[ll][2]>ma && info.hints>0)
	{
		currMove.type=3;
		ma=neurons[ll][2];
	}
	if (neurons[ll][3]>ma && info.hints>0)
	{
		currMove.type=4;
		ma=neurons[ll][2];
	}
	if (currMove.type==1)
	{
		ma=-1;
		for (int i=0;i<CARDS_IN_HAND;++i)
		{
			const Card &card=info.cards[i];
			if (neurons[ll][6+(card.col-1)*6+(card.num-1)]>ma)
			{
				currMove.card=i+1;
				ma=neurons[ll][4+(card.col-1)*6+(card.num-1)];
			}
		}
	}
	else if (currMove.type==2)
	{
		ma=-1;
		for (int i=0;i<CARDS_IN_HAND;++i)
		{
			const Card &card=info.cards[i];
			if (neurons[ll][42+(card.col-1)*6+(card.num-1)]>ma)
			{
				currMove.card=i+1;
				ma=neurons[ll][42+(card.col-1)*6+(card.num-1)];
			}
		}
	}
	else
	{
		const PlayerData *pl;
		if (neurons[ll][5]>neurons[ll][4])
		{
			currMove.player=2;
			pl=&info.prev;
		}
		else
		{
			currMove.player=1;
			pl=&info.next;
		}
		if (currMove.type=3)
		{
			ma=-1;
			for (int i=0;i<CARDS_IN_HAND;++i)
			{
				const Card &card=pl->cards[i];
				if (neurons[ll][78+(card.num-1)]>ma)
				{
					currMove.card=i+1;
					ma=neurons[ll][78+(card.num-1)];
				}
			}
		}
		else
		{
			ma=-1;
			for (int i=0;i<CARDS_IN_HAND;++i)
			{
				const Card &card=pl->cards[i];
				if (neurons[ll][83+(card.col-1)]>ma)
				{
					currMove.card=i+1;
					ma=neurons[ll][83+(card.col-1)];
				}
			}
		}
	}
	return currMove;
}

void PlayerNeuralNetwork::forwardPropagate()
{
	for (int i=1;i<topology.size();++i)
    {
        for (int j=0;j<topology[i];++j)
        {
            neurons[i][j]=0;
            for (int k=0;k<topology[i-1];++k)
            {
                neurons[i][j]+=neurons[i-1][k]*weights[i][j][k];
            }
            if (neurons[i][j]<0) neurons[i][j]=0;
        }
    }
}

void PlayerNeuralNetwork::loadMoveTypes(int &curr, const MoveDone &mvD)
{
	int mvT[4];
	for (int i=0;i<4;++i)
	{
		mvT[i]=0;
	}
	if (mvD.type==1 && mvD.success==1) mvT[0]=1;
	else if (mvD.type==1 && mvD.success==0) mvT[1]=1;
	else if (mvD.type==2) mvT[2]=1;
	else mvT[3]=1;
	for (int i=0;i<4;++i)
	{
		neurons[0][curr++]=mvT[i];
	}
}
void PlayerNeuralNetwork::loadPile(int &curr, int cards)
{
	int p[5];
	for (int i=0;i<5;++i)
	{
		p[i]=0;
	}
	p[cards]=1;
	for (int i=0;i<5;++i)
	{
		neurons[0][curr++]=p[i];
	}
}
void PlayerNeuralNetwork::loadLives(int &curr, int lives)
{
	int p[INITIAL_LIFE_TOKENS];
	for (int i=0;i<INITIAL_LIFE_TOKENS;++i)
	{
		p[i]=0;
	}
	p[lives]=1;
	for (int i=0;i<INITIAL_LIFE_TOKENS;++i)
	{
		neurons[0][curr++]=p[i];
	}
}
void PlayerNeuralNetwork::loadHints(int &curr, int hints)
{
	int p[INITIAL_HINT_TOKENS];
	for (int i=0;i<INITIAL_HINT_TOKENS;++i)
	{
		p[i]=0;
	}
	p[hints]=1;
	for (int i=0;i<INITIAL_HINT_TOKENS;++i)
	{
		neurons[0][curr++]=p[i];
	}
}
void PlayerNeuralNetwork::loadFullCards(int &curr, const Card cards[])
{
	int p[5][5];
	for (int i=0;i<5;++i)
	{
		for (int j=0;j<5;++j)
		{
			p[i][j]=0;
		}
	}
	for (int i=0;i<CARDS_IN_HAND;++i)
	{
		if (cards[i].col>0 && cards[i].num>0)
			++p[cards[i].col-1][cards[i].num-1];
	}
	for (int i=0;i<5;++i)
	{
		for (int j=0;j<5;++j)
		{
			neurons[0][curr++]=p[i][j];
		}
	}
}
void PlayerNeuralNetwork::loadNonFullCards(int &curr, const Card cards[])
{
	int p[6][6];
	for (int i=0;i<6;++i)
	{
		for (int j=0;j<6;++j)
		{
			p[i][j]=0;
		}
	}
	for (int i=0;i<CARDS_IN_HAND;++i)
	{
		++p[cards[i].col][cards[i].num];
	}
	for (int i=0;i<6;++i)
	{
		for (int j=0;j<6;++j)
		{
			neurons[0][curr++]=p[i][j];
		}
	}
}
void PlayerNeuralNetwork::loadNonFullCards(int &curr, const Card cards[], const CardKnowledge crdKn[])
{
	int p[6][6];
	for (int i=0;i<6;++i)
	{
		for (int j=0;j<6;++j)
		{
			p[i][j]=0;
		}
	}
	Card card;
	for (int i=0;i<CARDS_IN_HAND;++i)
	{
		card=card_with_knowledge(cards[i],crdKn[i]);
		++p[card.col][card.num];
	}
	for (int i=0;i<6;++i)
	{
		for (int j=0;j<6;++j)
		{
			neurons[0][curr++]=p[i][j];
		}
	}
}
void PlayerNeuralNetwork::loadInputs(const Information &info)
{
	int curr=0;
	neurons[0][curr++]=1; //constant

	loadMoveTypes(curr,info.moveBefore2);
	loadMoveTypes(curr,info.moveBefore);
	loadMoveTypes(curr,info.moveLast);

	for (int i=0;i<5;++i)
	{
		loadPile(curr,info.piles[i]);
	}

	loadLives(curr,info.lives);
	loadHints(curr,info.hints);

    neurons[0][curr++]=info.cardsLeft*1.0/(50-3*CARDS_IN_HAND);

	for (int i=0;i<5;++i)
	{
		for (int j=0;j<5;++j)
		{
			neurons[0][curr++]=info.clbt[i][j];
		}
	}

	loadFullCards(curr,info.next.cards);
	loadNonFullCards(curr,info.next.cards,info.next.cardKnowledge);

	loadFullCards(curr,info.prev.cards);
	loadNonFullCards(curr,info.prev.cards,info.prev.cardKnowledge);

	loadNonFullCards(curr,info.cards);

	for (int i=0;i<memory_neurons;++i)
    {
        neurons[0][curr++]=neurons[topology.size()-1][OUTPUTS+i];
    }
}
