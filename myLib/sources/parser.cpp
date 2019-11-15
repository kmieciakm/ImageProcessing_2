#include <iostream>
#include <chrono>
#include <stdlib.h>
#include "../headers/proc.h"
#include "../headers/converter.h"
#include "../headers/functions.h"
#include "../../CImg/CImg.h"


bool isIntNumber(std::string str){
    for (int i=0 ; i < str.length(); i++){
        if(str[0] == '-')
            continue;
        if ( !isdigit(str[i]) ) 
            return false;
    }
    return true;
}

void DisplayHelpInformations(){
    std::cout  << std::endl << "Usage" << std::endl;
    std::cout << "task2 -pathToImage --command [-argument=value [...]]" << std::endl << std::endl;
    std::cout << "Options" << std::endl << std::endl;
    
    exit(0);
}

std::string ExtractFilenameFromPath(std::string path){
    std::string filename = "";
    short indexOfSlash = 0;
    for(int characterIndex = path.length()-1; characterIndex >= 0; characterIndex--){
        if(path[characterIndex] == '/'){
            indexOfSlash = characterIndex;
            break;
        }
    }
    for(int currentIndex = indexOfSlash+1; currentIndex<path.length(); currentIndex++){
        filename += path[currentIndex];
    }
    return filename;
}

void ParseCommandAndRun(std::string command, int argumentsAmount, char *arguments[], Photo & photo){
    if(command == "--histogram"){
        if(argumentsAmount != 4){
            std::cout << "Unexpected or missing argument";
            exit(0);
        }else{
            if( !isIntNumber(static_cast<std::string>(arguments[3])) 
                    || std::stoi(static_cast<std::string>(arguments[3])) >= photo.GetChannelAmount() ){
                std::cout << "Wrong argument value type";
                exit(0);
            }else{
                DisplayHistogram(photo.GetChannel( std::stoi(static_cast<std::string>(arguments[3])) ).GetHistogram());
                exit(0);
            }
        }
    }else if(command == "--hpower"){
        if(argumentsAmount != 5){
            std::cout << "Unexpected or missing argument";
            exit(0);
        }else{
            if( !isIntNumber(static_cast<std::string>(arguments[3])) || !isIntNumber(static_cast<std::string>(arguments[4])) 
                    || std::stoi(static_cast<std::string>(arguments[3])) < 0 || std::stoi(static_cast<std::string>(arguments[3])) > 255
                    || std::stoi(static_cast<std::string>(arguments[4])) < 0 || std::stoi(static_cast<std::string>(arguments[4])) > 255){
                std::cout << "Wrong argument value type";
                exit(0);
            }else{
                for(int channelIndex = 0; channelIndex < photo.GetChannelAmount(); channelIndex++)
                    ApplyPowerProbabilityDensity(photo.GetChannel(channelIndex), std::stoi(static_cast<std::string>(arguments[3])), std::stoi(static_cast<std::string>(arguments[4])) );
            }
        }
    }else if(command == "--centropy"){
        if(argumentsAmount != 3){
            std::cout << "Unexpected or missing argument";
            exit(0);
        }else{
            for(int channelIndex = 0; channelIndex < photo.GetChannelAmount(); channelIndex++)
                std::cout << GetChannelEntropy(photo.GetChannel(channelIndex)) << std::endl;
            exit(0);
        }
    }else if(command == "--okirsf"){
        if(argumentsAmount != 3){
            std::cout << "Unexpected or missing argument";
            exit(0);
        }else{
            for(int channelIndex = 0; channelIndex < photo.GetChannelAmount(); channelIndex++)
                ApplyKirschOperator(photo.GetChannel(channelIndex));
        }
    }else if(command == "--sexdeti"){
        if(argumentsAmount != 4){
            std::cout << "Unexpected or missing argument";
            exit(0);
        }else{
            if( static_cast<std::string>(arguments[3]) != "N" 
                    && static_cast<std::string>(arguments[3]) != "NE"
                    && static_cast<std::string>(arguments[3]) != "E"
                    && static_cast<std::string>(arguments[3]) != "SE"){
                std::cout << "Wrong argument value type, available values: N, NE, E, SE";
                exit(0);
            }else{
                for(int channelIndex = 0; channelIndex < photo.GetChannelAmount(); channelIndex++)
                    ApplyConvolution(photo.GetChannel(channelIndex), static_cast<std::string>(arguments[3]));
            }
        }
    }else if(command == "--sexdetio"){
        if(argumentsAmount != 4){
            std::cout << "Unexpected or missing argument";
            exit(0);
        }else{
            if( static_cast<std::string>(arguments[3]) != "N" ){
                std::cout << "Wrong argument value type, available values: N";
                exit(0);
            }else{
                for(int channelIndex = 0; channelIndex < photo.GetChannelAmount(); channelIndex++)
                    ApplyOptimalizedConvolution(photo.GetChannel(channelIndex), static_cast<std::string>(arguments[3]));
            }
        }
    }else if(command == "--ntest"){
        if(argumentsAmount != 3){
            std::cout << "Unexpected or missing argument";
            exit(0);
        }else{
            Channel ch1 = photo.GetChannel(0);
            Channel ch2 = photo.GetChannel(0);

            auto start1 = std::chrono::system_clock::now();
                ApplyConvolution(ch1,"N");
            auto end1 = std::chrono::system_clock::now();
            std::chrono::duration<double> elapsed_seconds1 = end1-start1;
            std::cout << "Non optimalized execution time: " << elapsed_seconds1.count() << "s" << std::endl;

            auto start2 = std::chrono::system_clock::now();
                ApplyOptimalizedConvolution(ch2,"N");
            auto end2 = std::chrono::system_clock::now();
            std::chrono::duration<double> elapsed_seconds2 = end2-start2;
            std::cout << "Optimalized execution time:     " << elapsed_seconds2.count() << "s" << std::endl;
            exit(0);
        }
    }else{
        std::cout << "Illigal command: " << command;
        exit(0);
    }
}