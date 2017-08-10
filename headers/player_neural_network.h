#ifndef PLAYER_NEURAL_NETWORK_H_INCLUDED
#define PLAYER_NEURAL_NETWORK_H_INCLUDED

#include "player.h"

#include<vector>

const int INPUTS=1+3*4+5*5+3+8+1+5*5+3*6*6+2*5*5;
const int OUTPUTS=4+2+2*6*6+2*5;

struct PlayerNeuralNetwork:Player
{
	void init();
	Move do_move(const Information &info);
	void played_move(const MoveDone &moveDone);

	int memory_neurons;
    std::vector<int> topology;
    std::vector<std::vector<std::vector<double> > > weights;
    std::vector<std::vector<double> > neurons;

    void setTopology(const std::vector<int>& new_topology);
    void randomise();
    void mutate();
    void loadInputs(const Information &info);
    void forwardPropagate();
    Move& decodeOutputs(const Information &info);

    void loadMoveTypes(int &curr, const MoveDone &mvD);
    void loadPile(int &curr, int cards);
    void loadLives(int &curr, int lives);
    void loadHints(int &curr, int hints);
    void loadFullCards(int &curr, const Card cards[]);
    void loadNonFullCards(int &curr, const Card cards[]);
    void loadNonFullCards(int &curr, const Card cards[], const CardKnowledge crdKn[]);
};

#endif // PLAYER_NEURAL_NETWORK_H_INCLUDED
