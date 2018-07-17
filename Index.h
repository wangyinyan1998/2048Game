//
// Created by lenovo on 2018/7/1.
//

#ifndef OOPPJ_2048_INDEX_H
#define OOPPJ_2048_INDEX_H

const int maxX=4;
const int maxY=4;
class Index{
    int indexY;
    int indexX;
public:
    Index(int X,int Y){
        indexY = Y;
        indexX=X;
    }
    Index(){
        indexY = 0;
        indexX = 0;
    }
    Index* getUpIndex();
    Index* getDownIndex();
    Index* getLeftIndex();
    Index* getRightIndex();
    int getIndexX(){
        return indexX;
    }
    int getIndexY(){
        return indexY;
    }
    bool equal(Index index);
};



#endif //OOPPJ_2048_INDEX_H
