#include "../headers/proc.h"

Channel::Channel(int _width, int _height){
    this->fill.resize(_width);
    for(int i=0; i<_width; i++)
        this->fill[i].resize(_height);
}

Channel::Channel(){}

void Channel::SetValue(int _x, int _y, int _value){
    this->fill[_x][_y] = _value;
}

int Channel::GetValue(int _x, int _y){
    return this->fill[_x][_y];
}

Photo::Photo(){
    this->width=0;
    this->height=0;
    this->channel_amount=0;
    this->filename="image.bmp";
}

Photo::Photo(int _width,int _height, int _channelAmount, std::string _filename){
    this->width =_width;
    this->height =_height;
    this->channel_amount = _channelAmount;
    this->filename = _filename;
    this->channels.resize(_channelAmount);
    for(int i = 0; i < _channelAmount; i++)
        this->channels[i] = Channel(_width, _height);
}

int Photo::GetHeight(){
    return this->height;
}

int Photo::GetWidth(){
    return this->width;
}

int Photo::GetChannelAmount(){
    return this->channel_amount;
}

std::string Photo::GetFilename(){
    return this->filename;
}

void Photo::SetChannel(int _channelId, Channel _channel){
    this->channels[_channelId] = _channel;
}

Channel Photo::GetChannel(int _channelIndex){
    return this->channels[_channelIndex];
}