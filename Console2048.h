//
// Created by lenovo on 2018/7/1.
//
#include "Game2048Operation.h"
#include <string>
#include <Windows.h>
#ifndef OOPPJ_2048_CONSOLE2048_H
#define OOPPJ_2048_CONSOLE2048_H


class Console2048 {
private:
    Game2048Operation* game2048Operation = 0;
    std::string getBestTime();
public:
    void start();
    void draw(std::string s,int rearrange,int randomDelete);
    void AI(std::string s,int rearrange,int randomDelete);
    Console2048();
    char getDirection(std::string bestTime,int rearrange,int randomDelete);
};


#endif //OOPPJ_2048_CONSOLE2048_H
