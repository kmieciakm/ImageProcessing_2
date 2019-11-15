#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "./proc.h"

float GetChannelEntropy(Channel &);
void ApplyPowerProbabilityDensity(Channel &,int,int);
void ApplyKirschOperator(Channel &);
void ApplyConvolution(Channel&,std::string);
void ApplyOptimalizedConvolution(Channel&,std::string);
void ApplyOptimalizedN(Channel&);

#endif