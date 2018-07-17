//
// Created by lenovo on 2018/6/30.
//
#include <iostream>
#include <fstream>
#include "Game2048Operation.h"
using namespace std;
Game2048Operation::Game2048Operation() {
    for(int i=0;i<maxX;i++){
        for(int j=0;j<maxY;j++){
            keys[j][i] = new Key(0,new Index(j+1,i+1));
        }
    }
   /* keys[0][0]->setNumber(0);
    keys[1][0]->setNumber(2);
    keys[2][0]->setNumber(2);
    keys[3][0]->setNumber(4);*/
    startTime = time(0);
}
void Game2048Operation::setRandomKey() {
    Key* randomKey = getRandomKey();
    if(randomKey==0)
        return;
    int num = rand() % 2;
    if(num%2==0)
        num = 2;
    else
        num = 4;
    randomKey->setNumber(num);
}
Key* Game2048Operation::getKey(Index index) {
    int x = index.getIndexX()-1;
    int y = index.getIndexY()-1;
    if(x>=0 && y>=0 && x<maxX && y<maxY )
        return keys[x][y];
    return 0;
}
Key* Game2048Operation::getDownKey(Index index) {
    Index* index1 = index.getDownIndex();
    if(index1!=0)
        return getKey(*index1);
    return 0;
}
Key* Game2048Operation::getUpKey(Index index) {
    Index* index1 = index.getUpIndex();
    if(index1!=0)
        return getKey(*index1);
    return 0;
}
Key* Game2048Operation::getLeftKey(Index index) {
    Index* index1 = index.getLeftIndex();
    if(index1!=0)
        return getKey(*index1);
    return 0;
}
Key* Game2048Operation::getRightKey(Index index) {
    Index* index1 = index.getRightIndex();
    if(index1!=0)
        return getKey(*index1);
    return 0;
}
/**
 * 从index位置开始，向上进行判断，一旦找到一个数值为0的方块，或者两个相邻的且数字相等的方块，就返回true
 * @param index
 * @return
 */

bool Game2048Operation::canUp(Index index) {
    int y = index.getIndexY();
    int x = index.getIndexX();
    Key* key = getUpKey(Index(x,y));
    if(key!=0 && (key->getNumber()==0 || key->getNumber()== getKey(index)->getNumber()))
        return true;
    for(y=y+1;y<=maxY;y++){
        Key* key = getUpKey(Index(index.getIndexX(),y));
        if(key!=0 && key->getNumber()==0)
            return true;
    }
    return false;
}
void Game2048Operation::keyUp(Index index,int &keyMoveCount){
    Key* key = getKey(index);
    Key* targetKey = getUpKey(key->getIndex());
    if(targetKey==0)
        return;
    bool keyCanUp;
    if(key->getNumber()!=0 && targetKey->getNumber() == key->getNumber() && targetKey->getCanMerge()) {
        targetKey->setNumber(key->getNumber() + key->getNumber());
        key->setNumber(0);
        targetKey->setCanMerge(false);
        keyMoveCount++;
        return;
    }
    if(targetKey->getNumber()==0 && key->getNumber()!=0){
        targetKey->setNumber(key->getNumber());
        key->setNumber(0);
        keyCanUp = canUp(targetKey->getIndex());
        keyMoveCount++;
        if(keyCanUp)
            keyUp(targetKey->getIndex(),keyMoveCount);
    }
};
/**
 * 从index位置开始，向下进行判断，一旦找到一个数值为0的方块，或者两个相邻的且数字相等的方块，就返回true
 * @param index
 * @return
 */
bool Game2048Operation::canDown(Index index) {
    int y = index.getIndexY();
    int x = index.getIndexX();
    Key* key = getDownKey(Index(x,y));
    if(key!=0 && (key->getNumber()==0 || key->getNumber()== getKey(index)->getNumber()))
        return true;
    for(y=y-1;y>0;y--){
        Key* key = getDownKey(Index(x,y));
        if(key!=0 && key->getNumber()==0)
            return true;
    }
    return false;
}
/**
 * 单个块向下移动，则判断index上的数字（设为key），1. 如果该数字为0，则直接返回；
 * 2. 如果不为0，再对它的下一个位置上的数字（设为targetKey）进行判断，
 * ①如果targetKey与key的数字相同，则进行合并，并对targetKey的canMerge设为
 * false（因为每次移动对于每一个格子的撞击只有一次），keyMoveCount++（这个参数用来表示一次移动棋盘上的块移动的个数，如果为0，则不会新增块）；
 * ②如果targetKey数字为0，则进行keyCanDown()的判断，如果返回true，则递归调用keyDown()
 *
 * 其余移动类似，不再详述
 * @param index
 * @param keyMoveCount
 */
void Game2048Operation::keyDown(Index index,int &keyMoveCount){
    Key* key = getKey(index);
    Key* targetKey = getDownKey(key->getIndex());
    if(targetKey==0)
        return;
    bool keyCanDown;
    if(targetKey->getNumber()==0 && key->getNumber()!=0){
        targetKey->setNumber(key->getNumber());
        key->setNumber(0);
        keyCanDown = canDown(targetKey->getIndex());
        keyMoveCount++;
        if(keyCanDown)
            keyDown(targetKey->getIndex(),keyMoveCount);
    }
    if(key->getNumber()!=0 && targetKey->getNumber() == key->getNumber() && targetKey->getCanMerge()) {
        targetKey->setNumber(key->getNumber() + key->getNumber());
        key->setNumber(0);
        targetKey->setCanMerge(false);
        keyMoveCount++;
        return;
    }

};
/**
 * 从index位置开始，向左进行判断，一旦找到一个数值为0的方块，或者两个相邻的且数字相等的方块，就返回true
 * @param index
 * @return
 */
bool Game2048Operation::canLeft(Index index) {
    int y=index.getIndexY();
    int x=index.getIndexX();
    Key* key = getLeftKey(Index(x,y));
    if(key!=0 && (key->getNumber()==0 || key->getNumber()==getKey(index)->getNumber()))
        return true;
    for(x=x-1;x>0;x--){
        key = getLeftKey(Index(x,y));
        if(key!=0 && key->getNumber()==0)
            return true;
    }
    return false;
}
void Game2048Operation::keyLeft(Index index,int &keyMoveCount){
    Key* key = getKey(index);
    Key* targetKey = getLeftKey(key->getIndex());
    if(targetKey==0)
        return;
    bool keyCanLeft;
    if(key->getNumber()!=0 && targetKey->getNumber() == key->getNumber() && targetKey->getCanMerge()) {
        targetKey->setNumber(key->getNumber() + key->getNumber());
        key->setNumber(0);
        targetKey->setCanMerge(false);
        keyMoveCount++;
        return;
    }
    if(targetKey->getNumber()==0 && key->getNumber()!=0){
        targetKey->setNumber(key->getNumber());
        key->setNumber(0);
        keyCanLeft = canLeft(targetKey->getIndex());
        keyMoveCount++;
        if(keyCanLeft)
            keyLeft(targetKey->getIndex(),keyMoveCount);
    }
};
/**
 * 从index位置开始，向右进行判断，一旦找到一个数值为0的方块，或者两个相邻的且数字相等的方块，就返回true
 * @param index
 * @return
 */
bool Game2048Operation::canRight(Index index) {
    int y=index.getIndexY();
    int x=index.getIndexX();
    Key* key = getRightKey(Index(x,y));
    if(key!=0 && (key->getNumber()==0 || key->getNumber()==getKey(index)->getNumber()))
        return true;
    for(x=x+1;x<=maxX;x++){
        key = getRightKey(Index(x,y));
        if(key!=0 && key->getNumber()==0)
            return true;
    }
    return false;

}
void Game2048Operation::keyRight(Index index,int &keyMoveCount){
    Key* key = getKey(index);
    Key* targetKey = getRightKey(key->getIndex());
    if(targetKey==0)
        return;
    bool keyCanRight;// = canRight(targetKey->getIndex());
    if(key->getNumber()!=0 && targetKey->getNumber() == key->getNumber() && targetKey->getCanMerge()) {
        targetKey->setNumber(key->getNumber() + key->getNumber());
        key->setNumber(0);
       targetKey->setCanMerge(false);
       keyMoveCount++;
        return;
    }
    if(targetKey->getNumber()==0 && key->getNumber()!=0){
        targetKey->setNumber(key->getNumber());
        key->setNumber(0);
        keyCanRight = canRight(targetKey->getIndex());
        keyMoveCount++;
        if(keyCanRight)
            keyRight(targetKey->getIndex(),keyMoveCount);
    }
};
/**
 * 判断是不是赢了
 * @return
 */
bool Game2048Operation::ifWin() {
    Key* key;
    for(int y=1;y<maxY;y++){
        for(int x=1;x<maxX;x++){
            key = getKey(Index(x,y));
            if(key->getNumber()==2048) {
                ofstream out;
                out.open("records.txt",ios::out|ios::app);
                endTime = time(0);
                out<<endTime-startTime<<endl;
                out.close();
                return true;
            }
        }
    }
    return false;
}/**
 * 判断是不是输了
 * @return
 */
bool Game2048Operation::ifGameOver() {
    Key *key;
    bool leftOver;
    bool rightOver;
    bool upOver;
    bool downOver;
    for(int y=1;y<=maxY;y++){
        for(int x=1;x<=maxX;x++){
            key = getKey(Index(x,y));
            if(key->getNumber()==0)
                return false;
            leftOver = x-1<=0 || (getKey(Index(x-1,y))==0 || ((getKey(Index(x-1,y))->getNumber()!=key->getNumber())));
            rightOver =x+1>maxX ||  (getKey(Index(x+1,y))==0 || (getKey(Index(x+1,y))->getNumber()!=key->getNumber()));
            upOver = y-1<=0 || (getKey(Index(x,y-1))==0  || (getKey(Index(x,y-1))->getNumber()!=key->getNumber()));
            downOver =y+1>maxY ||(getKey(Index(x,y+1))==0  || (getKey(Index(x,y+1))->getNumber()!=key->getNumber()));
            if(!leftOver || !rightOver || !upOver || !downOver)
                return false;
        }
    }
    return true;
}
/**
 * 以下四个方法是对整个棋盘上的块进行上下左右移动
 */
void Game2048Operation::up() {
    int keyMoveCount = 0;
    for(int x=maxX;x>0;x--){
        for(int y=maxY;y>0;y--){
            keyUp(Index(x,y),keyMoveCount);
        }
        for(int y=maxY;y>0;y--){
            getKey(Index(x,y))->setCanMerge(true);
        }
    }
    if(keyMoveCount>0)
        setRandomKey();
}
void Game2048Operation::down() {
    int keyMoveCount = 0;
    for(int x=maxX;x>0;x--){
        for(int y=1;y<=maxY;y++){
            keyDown(Index(x,y),keyMoveCount);
        }
        for(int y=1;y<=maxY;y++){
            getKey(Index(x,y))->setCanMerge(true);
        }
    }
    if(keyMoveCount>0)
        setRandomKey();
}
void Game2048Operation::right() {
    int keyMoveCount = 0;
    for(int y=1;y<=maxY;y++){
        for(int x=maxX;x>0;x--){
            keyRight(Index(x,y),keyMoveCount);
        }
        for(int x=maxX;x>0;x--){
            getKey(Index(x,y))->setCanMerge(true);
        }
    }
    if(keyMoveCount>0)
        setRandomKey();
}
void Game2048Operation::left() {
    int keyMoveCount = 0;
    for(int y=1;y<=maxY;y++){
        for(int x=1;x<=maxX;x++){
            keyLeft(Index(x,y),keyMoveCount);
        }
        for(int x=1;x<=maxX;x++){
            getKey(Index(x,y))->setCanMerge(true);
        }
    }
    if(keyMoveCount>0)
        setRandomKey();
}
/**
 * 对棋盘上的数字进行重排操作
 */
void Game2048Operation::rearrange() {
    int x;
    int y;
    int number;
    for(int i=0;i<8;i++){
        x=rand() % 4+1;
        y=rand() % 4+1;
        number = getKey(Index(x,y))->getNumber();
        getKey(Index(x,y))->setNumber(getKey(Index(y,x))->getNumber());
        getKey(Index(y,x))->setNumber(number);
    }
}
/**
 * 获取随机的一个块的地址
 * @return
 */
Key* Game2048Operation::getRandomKey() {
    int* random = randomInt(maxX);
    for(int x=0;x<maxX;x++){
        for(int y=0;y<maxY;y++){
            if(getKey(Index(random[x],random[y]))->getNumber()==0) {
                int indexX = random[x];
                int indexY = random[y];
                delete(random);
                return getKey(Index(indexX,indexY));
            }
        }
    }

    return 0;
}
/**
 * 获取随机的从1-n的打乱的数组
 * @param n
 * @return
 */
int* Game2048Operation::randomInt(int n) { //n为随机数大小
    vector<int>a; //储存所有可能的随机数
    int* randnum = new int[n]; //结果序列
    for (int i = 1; i < n+1; i++)a.push_back(i); //生成所有可能随机数
    for (int i = 0; i < n; i++) {
        int choice = rand() % a.size(); //随机产生下标
        randnum[i] = a[choice];
        swap(a[choice], a[a.size()-1]); //交换已经生成的随机数和数组最后一个数
        a.pop_back(); //删除已经生成的随机数
    }
    return randnum;
}
/**
 * 随机删除一个最小的块
 */
void Game2048Operation::randomDelete() {
    int* random = randomInt(maxX);
    int small = 2050;
    int indexX=0;
    int indexY=0;
    int num;
    for(int x=0;x<maxX;x++){
        for(int y=0;y<maxY;y++){
            num = getKey(Index(random[x],random[y]))->getNumber();
            if(num !=0 && num<small) {
                small = num;
                indexX = random[x];
                indexY =  random[y];
            }
        }
    }
    getKey(Index(indexX,indexY))->setNumber(0);
    delete(random);
}
/**
 * 对游戏上的块进行评估，向上的权重为upWeight，向下的权重为downWeight，向左的权重为leftWeight、向右的权重为rightWeight，主要通过判断每个方块上的数字与上下左右的关系，具体规则为（以upWeight为例）：
1.	如果方块number上面的第一个targetNumber不为0，则：
①如果number不为0，且targetNumber=number，且targetNumber的上下左右有任意一个块的大小等于number*2，则upWeight+=3；
②如果number！=0，且targetNumber=0，且targetNumber的上下左右有任意一个块的大小等于number，则upWeight+=3；
③如果number！=0，且targetNumber=number，且targetNumber的上下左右没有一个块的大小等于2*number，则upWeight+=2
剩下的downWeight、等赋值与上述类似
 * @param upWeight
 * @param downWeight
 * @param leftWeight
 * @param rightWeight
 */
void Game2048Operation::getMoveWeight(int &upWeight, int &downWeight, int &leftWeight, int &rightWeight) {
    int number;
    int targetNumber;
    int nextTargetUp;
    int nextTargetDown;
    int nextTargetLeft;
    int nextTargetRight;
    bool argueNextTarget1;
    bool argueNextTarget2;
    for(int x=1;x<=maxX;x++){
        for(int y=1;y<=maxY;y++){
            number = getKey(Index(x,y))->getNumber();
            nextTargetUp = getUpKey(Index(x,y+1))== 0? 0: getUpKey(Index(x,y+1))->getNumber();
            nextTargetRight = getRightKey(Index(x+1,y))== 0? 0: getRightKey(Index(x+1,y))->getNumber();
            nextTargetDown = getDownKey(Index(x,y-1))== 0? 0: getDownKey(Index(x,y-1))->getNumber();
            nextTargetLeft = getLeftKey(Index(x-1,y))== 0? 0: getLeftKey(Index(x-1,y))->getNumber();
            argueNextTarget1 = (nextTargetUp==number*2) ||(nextTargetDown==number*2) || (nextTargetLeft==number*2) || (nextTargetRight==number*2);
            argueNextTarget2 = nextTargetUp==number ||nextTargetDown==number || nextTargetLeft==number || nextTargetRight==number;
            if(getUpKey(Index(x,y))!=0){
                targetNumber = getUpKey(Index(x,y))->getNumber();
                if(number!=0 && targetNumber==number && argueNextTarget1)
                    upWeight = upWeight+3;
                if(number!=0 && targetNumber==0 && argueNextTarget2)
                    upWeight+=3;
                if(number!=0 && targetNumber==number &&!argueNextTarget1)
                    upWeight+=2;
            }
            if(getDownKey(Index(x,y))!=0){
                targetNumber = getDownKey(Index(x,y))->getNumber();
                if(number!=0 && targetNumber==number && argueNextTarget1)
                    downWeight = downWeight+3;
                if(number!=0 && targetNumber==0 && argueNextTarget2)
                    downWeight+=3;
                if(number!=0 && targetNumber==number && !argueNextTarget1)
                    downWeight+=2;
            }

            if(getLeftKey(Index(x,y))!=0){
                targetNumber = getLeftKey(Index(x,y))->getNumber();
                if(number!=0 && targetNumber==number && argueNextTarget1)
                    leftWeight = leftWeight+3;
                if(number!=0 && targetNumber==0 && argueNextTarget2)
                    leftWeight+=3;
                if(number!=0 && targetNumber==number &&!argueNextTarget1)
                    leftWeight+=2;
            }

            if(getRightKey(Index(x,y))!=0){
                targetNumber = getRightKey(Index(x,y))->getNumber();
                if(number!=0 && targetNumber==number && argueNextTarget1)
                    rightWeight = rightWeight+3;
                if(number!=0 && targetNumber==0 && argueNextTarget2)
                    rightWeight+=3;
                if(number!=0 && targetNumber==number && !argueNextTarget1)
                    rightWeight+=2;
            }
        }
    }
}
/**
 * 一次AI操作
 */
void Game2048Operation::AIOperation() {
    int upNum = 0;
    int downNum = 0;
    int rightNum = 0;
    int leftNum = 0;
   getMoveWeight(upNum,downNum,leftNum,rightNum);
    if(upNum!=0 &&  upNum>=leftNum && upNum>=rightNum && upNum>=downNum) {
       up();
    }
    else if(downNum!=0 &&  downNum>=leftNum && downNum>=rightNum && downNum>=upNum) {
       down();
    }
    else if(leftNum!=0 &&  leftNum>=upNum && leftNum>=rightNum && leftNum>=downNum) {
        left();
    }
    else if(rightNum!=0 &&  rightNum>=leftNum &&  rightNum>=downNum &&  rightNum>=upNum) {
        right();
    }
    else {
        randomOperation();
    }
}
/**
 * 一次随机移动操作
 */
void Game2048Operation::randomOperation(){
    int* random = randomInt(4);
    static int count = 0;
    count++;
    switch (random[count % 4]){
        case 1:
            up();
            break;
        case 2:
            down();
            break;
        case 3:
            left();
            break;
        case 4:
            right();
            break;
        default:
            up();
    }
    delete(random);
}

