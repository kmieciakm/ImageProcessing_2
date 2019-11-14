#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "./proc.h"

void PowerProbabilityDensity(Channel &,int,int);
float GetChannelEntropy(Channel &);
void KirschOperator(Channel &);
int ComputeS(int,int,int,Channel&);
int ComputeT(int,int,int,Channel&);

#endif