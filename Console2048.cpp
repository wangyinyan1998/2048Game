//
// Created by lenovo on 2018/6/30.
//
#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include <unistd.h>
#include <conio.h>
#include "Console2048.h"

using namespace std;

Console2048::Console2048() {}
/**
 * 获取用户输入的指令，如果30秒内没有输入，新增一个块，最后三秒会有时间提示
 * @param s
 * @param rearrange
 * @param randomDelete
 * @return
 */
char Console2048::getDirection(std::string s,int rearrange,int randomDelete) {
char a;
time_t timeBegin = time(0);
int n=0;
    while(true)  {           //the main loop  ||  主循环
        if(kbhit()){       //detect the keyboard  ||  kbhit检测键盘输，如果发现了输入
            a = _getch() ;
            return a;
        } else if(time(0)-timeBegin==24 && n==0) {
            cout << "Your time have "<<3 <<" s"<< endl;
            n=1;
        }
        else if(time(0)-timeBegin==26 && n==1) {
            cout <<  "Your time have "<<2<<" s"<< endl;
            n=2;
        }
        else if(time(0)-timeBegin==28 && n==2) {
            cout << "Your time have "<<1 <<" s"<< endl;
            n=3;
        }
        else if(time(0)-timeBegin>=30){
            timeBegin = time(0);
            game2048Operation->setRandomKey();
            draw(s, rearrange, randomDelete);
            n=0;
        }
    }
}/**
 * 获取排行榜中最佳时间
 * @return
 */
std::string Console2048::getBestTime() {
    ifstream in("records.txt");
    double bestTime = 99999999999999;
    double s;
    while (in >> s) {
        if (s < bestTime)
            bestTime = s;
    }
    if (bestTime == 99999999999999)
        bestTime = 0;
    int hour = ((int) bestTime) / 3600;
    int minute = ((int) bestTime) / 60 % 60;
    int second = ((int) bestTime) % 60;
    string ss;
    ss = "best Time:" + to_string(hour) + ":" + to_string(minute) + ":" + to_string(second);
    return ss;
}
/**
 * 开始游戏
 */
void Console2048::start() {
    cout<<"Welcome to WYY-2048-Game,you can enter:"
          " 'w' to move up,  's' to move down,\n"
          "'d' to move right, 'a' to move left,\n"
          "'q' to quit, 'z' to rearranging your chesses\n"
          "'x' to random delete one chess\n"
          "remember: chances to rearrange or random delete have 5 times,please treasure them!\n"
          "now! Please to start your game tour!\n";

    string s = getBestTime();
    delete (game2048Operation);
    game2048Operation = new Game2048Operation();
    game2048Operation->setRandomKey();
    game2048Operation->setRandomKey();
    int rearrange = 5;
    int randomDelete = 5;
    char direction;
    while (true) {
        draw(s, rearrange, randomDelete);
        direction = getDirection(s, rearrange,randomDelete);
        switch (direction) {
            case 'w':
                game2048Operation->up();
                break;
            case 's':
                game2048Operation->down();
                break;
            case 'd':
                game2048Operation->right();
                break;
            case 'a':
                game2048Operation->left();
                break;
            case 'q':
                exit(0);
            case 'z':
                if (rearrange == 0) {
                    cout << "Your opportunities to rearrange have run out! " << endl;
                    break;
                }
                game2048Operation->rearrange();
                rearrange--;
                break;
            case 'x':
                if (randomDelete == 0) {
                    cout << "Your opportunities to random delete have run out!" << endl;
                    break;
                }
                game2048Operation->randomDelete();
                randomDelete--;
                break;
            case 'c':
                AI(s, rearrange, randomDelete);
                break;
        }
        if (game2048Operation->ifWin()) {
            draw(s, rearrange, randomDelete);
            cout << "-----Yes! You have win!" << endl;
            break;
        } else if (game2048Operation->ifGameOver()) {
            draw(s, rearrange, randomDelete);
            cout << "-----Oh NO! You are lost!" << endl;
            break;
        }
    }
    cout << "The game is over! you can enter 'restart' to restart or 'q' to quit the game!" << endl;
    char direction2[20];
    while (true) {
        cin >> direction2;
        if (strcmp(direction2, "restart") == 0)
            break;
        else if (strcmp(direction2, "q") == 0)
            exit(0);
        else {
            cout << "What you enter is invalid! please enter words again!" << endl;
        }
    }
    start();
}
/**
 * 画棋盘
 * @param s
 * @param rearrange
 * @param randomDelete
 */
void Console2048::draw(string s, int rearrange, int randomDelete) {
    cout << s << endl;
    cout << "Your opportunities to rearrange is  " << rearrange << endl;
    cout << "Your opportunities to random delte is  " << randomDelete << endl;
    for (int x = maxX - 1; x >= 0; x--) {
        for (int y = 0; y < maxY; y++) {
            cout << game2048Operation->keys[y][x]->getNumber() << "\t";
        }
        cout << endl;
        cout << endl;
    }
}
/**
 * 全部的AI操作
 * @param s
 * @param rearrange
 * @param randomDelete
 */
void Console2048::AI(std::string s, int rearrange, int randomDelete) {
    while (true) {
       // game2048Operation->randomOperation();
        game2048Operation->AIOperation();
        if (game2048Operation->ifWin() || game2048Operation->ifGameOver()) {
            break;
        }
        draw(s, rearrange, randomDelete);
    }
}