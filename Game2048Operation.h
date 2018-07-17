//
// Created by lenovo on 2018/7/1.
//
#include "Index.h"
#include <stdlib.h>
#include <vector>
#include <time.h>
#ifndef OOPPJ_2048_GAME2048OPERATION_H
#define OOPPJ_2048_GAME2048OPERATION_H




extern const int maxX;
extern const int maxY;

class Key {
    int number;
    Index* index;
    bool canMerge= false;
public:
    Key(int num,Index* index1){
        number = num;
        index = index1;
    }
    Index getIndex(){
        return *index;
    }
    int getNumber(){
        return number;
    }
    void setNumber(int num){
        number = num;
    }
    void setCanMerge(bool canM){
        canMerge = canM;
    }
    bool getCanMerge(){
        return canMerge;
    }
};


class Game2048Operation {
private:
    time_t startTime;
    time_t endTime;
    Key* getKey(Index index);
    Key* getUpKey(Index index);
    Key* getDownKey(Index index);
    Key* getLeftKey(Index index);
    Key* getRightKey(Index index);
    void keyUp(Index index,int &keyMoveCount);
    void keyDown(Index index,int &keyMoveCount);
    void keyLeft(Index index,int &keyMoveCount);
    void keyRight(Index index,int &keyMoveCount);
    bool canUp(Index index);
    bool canDown(Index index);
    bool canRight(Index index);
    bool canLeft(Index index);
    Key* getRandomKey();
    int* randomInt(int num);
    void randomOperation();
    void getMoveWeight(int& upWeight,int& downWeight,int & leftWeight,int & rightWeight);
public:
    Game2048Operation();
    Key* keys[maxX][maxY];
    bool ifGameOver();
    bool ifWin();
    void up();
    void down();
    void left();
    void right();
    void setRandomKey();
    void rearrange();
    void randomDelete();
    void AIOperation();


};



#endif //OOPPJ_2048_GAME2048OPERATION_H
