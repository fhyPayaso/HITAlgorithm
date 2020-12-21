/* ====================================================
#   Copyright (C)2020 2021 fhyPayaso All rights reserved.
#
#   @Author        : fhyPayaso
#   @Date          : 2020/11/9
#   @Email         : 401619823@qq.com
#   @Description   : 
# ====================================================*/

#ifndef HITALGORITHM_DIVIDECONQUER_H
#define HITALGORITHM_DIVIDECONQUER_H

#include "../BaseStruct.h"
#include <vector>
#include <algorithm>

using namespace std;

class DivideConquer
{

public:


    static int triangleS(Point2i a1, Point2i a2, Point2i a3);


    static void divide(int first, int last, vector<Point2i> nodeList, vector<Point2i> &vist);


    static vector<Point2i> divideConquer(vector<Point2i> pointList);

};


#endif //HITALGORITHM_DIVIDECONQUER_H
