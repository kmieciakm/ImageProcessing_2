#include "../headers/functions.h"
#include "../headers/proc.h"
#include <math.h>

void PowerProbabilityDensity(Channel &channel, int gMin, int gMax){
    std::vector<float> histogram = channel.GetHistogram();
    float gMinPow = powf(static_cast<float>(gMin),(1./3.));
    float gMaxPow = powf(static_cast<float>(gMax),(1./3.));
    
    for(int x = 0; x < channel.GetWidth(); x++){
        for(int y = 0; y < channel.GetHeight(); y++){    
            float sum = 0;
            int f = channel.GetValue(x,y);
            for(int m=0; m<f; m++)
                sum += histogram[m];
            int gF = powf(static_cast<float>( gMinPow + ( gMaxPow - gMinPow) * sum ), 3.);
            channel.SetValue(x,y,gF);
        }
    }
}