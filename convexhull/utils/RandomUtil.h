/* ====================================================
#   Copyright (C)2020 2021 fhyPayaso All rights reserved.
#
#   @Author        : fhyPayaso
#   @Date          : 2020/11/8
#   @Email         : 401619823@qq.com
#   @Description   : 
# ====================================================*/

#ifndef HITALGORITHM_RANDOMUTIL_H
#define HITALGORITHM_RANDOMUTIL_H

#include <vector>
#include <cstdlib>
#include <time.h>
#include <iostream>
#include "../BaseStruct.h"

using namespace std;

class RandomUtil
{

public:


    static vector<Point2i> buildRandomPoint(int size = 100);


};

vector<Point2i> RandomUtil::buildRandomPoint(int size)
{

    srand(time(0));

    const int MAT_SIZE = 100;

    vector<Point2i> resVec;

    for (int i = 0; i < size; ++i)
    {
        Point2i pnt;
        pnt.x = rand() % MAT_SIZE;
        pnt.y = rand() % MAT_SIZE;
        resVec.push_back(pnt);

//            cout << "point " << i << "  ===>  x: " << pnt.x << "  y:" << pnt.y << endl;
    }

    return resVec;
}


#endif //HITALGORITHM_RANDOMUTIL_H
