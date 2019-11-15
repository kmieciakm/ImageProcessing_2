#include "../headers/functions.h"
#include "../headers/proc.h"
#include <math.h>
#include <algorithm>

void ApplyPowerProbabilityDensity(Channel &channel, int gMin, int gMax){
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

float GetChannelEntropy(Channel &channel){
    float entropyValue = 0;
    float temp = 0;
    std::vector<float> histogram = channel.GetHistogram();

    for(int i = 0; i < histogram.size(); i++){  
        if(histogram[i] > 0)
            temp = histogram[i] * log2f(static_cast<float>(histogram[i]));
        else
            temp = 0;
        entropyValue += temp;
    }
    return (-1 * entropyValue);
}

void ApplyKirschOperator(Channel &channel){
    Channel channelCopy = channel;
    for(int x = 1; x < channel.GetWidth()-1; x++){
        for(int y = 1; y < channel.GetHeight()-1; y++){   
            std::vector<float> pixelsValue; 
            for(int i = 0; i < 8; i++){
                float tempS = ComputeS(i,x,y,channelCopy);
                float tempT = ComputeT(i,x,y,channelCopy);
                pixelsValue.push_back( abs((5*tempS) - (3*tempT)) );
            }
            pixelsValue.push_back(1);
            float maxPixelValue = *max_element(begin(pixelsValue), end(pixelsValue));
            channel.SetValue(x,y,maxPixelValue);
        }
    }
}

int ComputeS(int i, int x, int y, Channel &channel){
    std::vector<int> neighborhoodA;
    neighborhoodA.push_back(channel.GetValue(x-1,y-1));
    neighborhoodA.push_back(channel.GetValue(x,y-1));
    neighborhoodA.push_back(channel.GetValue(x+1,y-1));
    neighborhoodA.push_back(channel.GetValue(x+1,y));
    neighborhoodA.push_back(channel.GetValue(x+1,y+1));
    neighborhoodA.push_back(channel.GetValue(x,y+1));
    neighborhoodA.push_back(channel.GetValue(x-1,y+1));
    neighborhoodA.push_back(channel.GetValue(x-1,y));
    
    return ( neighborhoodA[i%8] + neighborhoodA[(i+1)%8] + neighborhoodA[(i+2)%8] );
};

int ComputeT(int i, int x, int y, Channel &channel){
    std::vector<int> neighborhoodA;
    neighborhoodA.push_back(channel.GetValue(x-1,y-1));
    neighborhoodA.push_back(channel.GetValue(x,y-1));
    neighborhoodA.push_back(channel.GetValue(x+1,y-1));
    neighborhoodA.push_back(channel.GetValue(x+1,y));
    neighborhoodA.push_back(channel.GetValue(x+1,y+1));
    neighborhoodA.push_back(channel.GetValue(x,y+1));
    neighborhoodA.push_back(channel.GetValue(x-1,y+1));
    neighborhoodA.push_back(channel.GetValue(x-1,y));

    return ( neighborhoodA[(i+3)%8] + neighborhoodA[(i+4)%8] + neighborhoodA[(i+5)%8] + neighborhoodA[(i+6)%8] + neighborhoodA[(i+7)%8] );
};

void ApplyConvolution(Channel &channel, std::string version){
    Channel channelCopy = channel;
    for(int x = 1; x < channel.GetWidth()-1; x++){
        for(int y = 1; y < channel.GetHeight()-1; y++){
            int newPixelValue = ComputeExtractionDetail(version,x,y,channelCopy);   
            channel.SetValue(x,y,newPixelValue);
        }
    }
}

int ComputeExtractionDetail(std::string version, int x, int y, Channel &channel){
    std::vector<int> mask;
    int sum = 0;
    if(version == "N"){
        mask.insert(mask.end(),{ 1, 1, 1,
                                 1,-2, 1,
                                -1,-1,-1});
    } else if(version == "NE"){
        mask.insert(mask.end(),{ 1, 1, 1,
                                -1,-2, 1,
                                -1,-1, 1});
    } else if(version == "E"){
        mask.insert(mask.end(),{ -1, 1, 1,
                                 -1,-2, 1,
                                 -1, 1, 1});
    } else if(version == "SE"){
        mask.insert(mask.end(),{-1,-1, 1,
                                -1,-2, 1,
                                 1, 1, 1});
    } else{
        mask.insert(mask.end(),{ 0, 0, 0,
                                 0, 1, 0,
                                 0, 0, 0});
    }
    int currentPixel = 0;
    for(int i = -1; i <= 1; i++){
        for(int j = -1; j <= 1; j++, currentPixel++){
            sum += channel.GetValue(x+j, y+i) * mask[currentPixel];
        }
    }
    return sum;
}