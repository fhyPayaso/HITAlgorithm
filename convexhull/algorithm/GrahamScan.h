/* ====================================================
#   Copyright (C)2020 2021 fhyPayaso All rights reserved.
#
#   @Author        : fhyPayaso
#   @Date          : 2020/11/9
#   @Email         : 401619823@qq.com
#   @Description   : 
# ====================================================*/

#ifndef HITALGORITHM_GRAHAMSCAN_H
#define HITALGORITHM_GRAHAMSCAN_H

#include "../BaseStruct.h"
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;



class GrahamScan
{
public:

    static double cross(Vector2f v1, Vector2f v2);

    static vector<Point2i> grahamScan(vector<Point2i> pointList);


};


#endif //HITALGORITHM_GRAHAMSCAN_H
