#include "../headers/randomisation.h"

#include<stdlib.h>

const int MAX_MUTATION=25;

void mutateVariable(double& variable, double low, double high)
{
    variable+=rand()%(MAX_MUTATION*2+1)/100.0-MAX_MUTATION/1000.0;
    if (variable<low) variable=low;
    if (variable>high) variable=high;
}
void randomiseVariable(double& variable, double low, double high)
{
    variable=rand()%(int(high-low)*1000+1)/1000.0+low;
}
