#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "./proc.h"

void ApplyPowerProbabilityDensity(Channel &,int,int);
float GetChannelEntropy(Channel &);
void ApplyKirschOperator(Channel &);
int ComputeS(int,int,int,Channel&);
int ComputeT(int,int,int,Channel&);
void ApplyConvolution(Channel&,std::string);
int ComputeExtractionDetail(std::string,int,int,Channel&);

#endif