#ifndef PROC_H
#define PROC_H

#include <iostream>
#include <vector>

class Channel{
private:
    std::vector<std::vector<int>> fill;

public:
    void SetValue(int _x, int _y, int _value); 
    int GetValue(int _x, int _y);
    Channel(int _width, int _height);
    Channel();
};

class Photo{
private:
    int width;
    int height;
    int channel_amount;
    std::string filename;
    std::vector<Channel> channels;
    std::vector<int> histogram;

public:
    int GetWidth();
    int GetHeight();
    int GetChannelAmount();
    std::string GetFilename();
    void SetChannel(int,Channel);
    Channel GetChannel(int);
    Photo(int,int,int,std::string);
    Photo();
};

#endif