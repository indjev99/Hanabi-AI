#ifndef PLAYER_DATA_H_INCLUDED
#define PLAYER_DATA_H_INCLUDED

#include "card.h"
#include "card_knowledge.h"
#include "constants.h"

struct PlayerData
{
	Card cards[CARDS_IN_HAND];
	CardKnowledge cardKnowledge[CARDS_IN_HAND];
};

#endif // PLAYER_DATA_H_INCLUDED
