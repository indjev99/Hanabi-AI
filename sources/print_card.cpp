#include "../headers/print_card.h"
#include "../headers/console_handle.h"

#include<iostream>
#include<windows.h>

void print_card(const Card &card)
{
	int colourCode=FOREGROUND_INTENSITY;
	switch (card.col)
	{
		case 1: colourCode=FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
				break;
		case 2: colourCode=FOREGROUND_INTENSITY | FOREGROUND_BLUE;
				break;
		case 3: colourCode=FOREGROUND_INTENSITY | FOREGROUND_GREEN;
				break;
		case 4: colourCode=FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN;
				break;
		case 5: colourCode=FOREGROUND_INTENSITY | FOREGROUND_RED;
				break;
	}
	SetConsoleTextAttribute(hConsole, colourCode);
	if (card.num) std::cout<<card.num;
	else std::cout<<'X';
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}
