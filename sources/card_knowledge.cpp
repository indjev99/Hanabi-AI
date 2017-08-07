#include "../headers/card_knowledge.h"

const Card& card_with_knowledge(const Card& card, const CardKnowledge& cardKnowledge)
{
	Card new_card=card;
	if (cardKnowledge.know_col) new_card.col=card.col;
	else new_card.col=0;
	if (cardKnowledge.know_num) new_card.num=card.num;
	else new_card.num=0;
	return new_card;
}
