/* ====================================================
#   Copyright (C)2020 2021 fhyPayaso All rights reserved.
#
#   @Author        : fhyPayaso
#   @Date          : 2020/11/9
#   @Email         : 401619823@qq.com
#   @Description   : 
# ====================================================*/

#ifndef HITALGORITHM_BRUTEFORCE_H
#define HITALGORITHM_BRUTEFORCE_H

#include "../BaseStruct.h"
#include <vector>

using namespace std;

class BruteForce
{
public:

    // 判断点A是否在点BCD组成的三角形内部
    static bool isInTriangle(Point2i pntA, Point2i pntB, Point2i pntC, Point2i pntD);

    // 暴力枚举
    static vector<Point2i> bruteForce(vector<Point2i> pointList);

    static bool judge(Point2i P, Point2i A, Point2i B)
    {
        bool xb = min(A.x, B.x) <= P.x && P.x <= max(A.x, B.x);
        bool yb = min(A.y, B.y) <= P.y && P.y <= max(A.y, B.y);

        return xb && yb;
    }
};


#endif //HITALGORITHM_BRUTEFORCE_H
