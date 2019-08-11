#ifndef CARD_KNOWLEDGE_H_INCLUDED
#define CARD_KNOWLEDGE_H_INCLUDED

#include "card.h"

struct CardKnowledge
{
	bool know_col;
	bool know_num;
};

const Card card_with_knowledge(const Card& card, const CardKnowledge& cardKnowledge);

#endif // CARD_KNOWLEDGE_H_INCLUDED
