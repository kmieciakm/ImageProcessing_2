#include <iostream>
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
            if( !isIntNumber((std::string)arguments[3]) || std::stoi(std::string(arguments[3])) >= photo.GetChannelAmount() ){
                std::cout << "Wrong argument value type";
                exit(0);
            }else{
                DisplayHistogram(photo.GetChannel( std::stoi(std::string(arguments[3])) ).GetHistogram());
            }
        }
    }else if(command == "--hpower"){
        if(argumentsAmount != 5){
            std::cout << "Unexpected or missing argument";
            exit(0);
        }else{
            if( !isIntNumber((std::string)arguments[3]) || !isIntNumber((std::string)arguments[4]) 
                    || std::stoi(std::string(arguments[3])) < 0 || std::stoi(std::string(arguments[3])) > 255
                    || std::stoi(std::string(arguments[4])) < 0 || std::stoi(std::string(arguments[4])) > 255){
                std::cout << "Wrong argument value type";
                exit(0);
            }else{
                for(int channelIndex = 0; channelIndex < photo.GetChannelAmount(); channelIndex++)
                    PowerProbabilityDensity(photo.GetChannel(channelIndex), std::stoi(std::string(arguments[3])), std::stoi(std::string(arguments[4])) );
            }
        }
    }else{
        std::cout << "Illigal command: " << command;
        exit(0);
    }
}