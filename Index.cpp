//
// Created by lenovo on 2018/7/1.
//

#include "Index.h"
Index* Index::getDownIndex() {
    if(indexY-1>=1)
        return new Index(indexX,indexY-1);
    return 0;
}
Index* Index::getLeftIndex() {
    if(indexX-1>=1)
        return new Index(indexX-1,indexY);
    return 0;
}
Index* Index::getRightIndex() {
    if(indexX+1<=maxX)
        return new Index(indexX+1,indexY);
    return 0;
}
Index* Index::getUpIndex() {
    if(indexY+1<=maxY)
        return new Index(indexX,indexY+1);
    return 0;
}
bool Index::equal(Index index) {
    if(index.getIndexX()==indexX && index.getIndexY()==indexY)
        return true;
    return false;
}