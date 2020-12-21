/* ====================================================
#   Copyright (C)2020 2021 fhyPayaso All rights reserved.
#
#   @Author        : fhyPayaso
#   @Date          : 2020/11/9
#   @Email         : 401619823@qq.com
#   @Description   : 
# ====================================================*/

#include "BruteForce.h"

bool BruteForce::isInTriangle(Point2i pntA, Point2i pntB, Point2i pntC, Point2i pntD)
{
    // 三角形三条边
    Vector2f BC(pntB, pntC);
    Vector2f CD(pntC, pntD);
    Vector2f DB(pntD, pntB);

    Vector2f BA(pntB, pntA);
    Vector2f CA(pntC, pntA);
    Vector2f DA(pntD, pntA);

    double ba = BC.crossProduct(BA);
    double ca = CD.crossProduct(CA);
    double da = DB.crossProduct(DA);

    if (ba > 0 && ca > 0 && da > 0)
        return true;

    if (ba == 0 && judge(pntA, pntB, pntC))
        return true;
    else if (ca == 0 && judge(pntA, pntC, pntD))
        return true;
    else if (da == 0 && judge(pntA, pntD, pntB))
        return true;

    return false;
}

vector<Point2i> BruteForce::bruteForce(vector<Point2i> pointList)
{
    vector<Point2i> res;
    int num = pointList.size();
    for (int index = 0; index < num; ++index)
    {
        Point2i pnt = pointList[index];
        bool flag = true;
        for (int i = 0; i < num; ++i)
        {
            for (int j = i + 1; j < num; ++j)
            {
                for (int k = j + 1; k < num; ++k)
                {
                    if (index == i || index == j || index == k)
                        continue;

                    // pnt 是否在ijk里
                    if (isInTriangle(pnt, pointList[i], pointList[j], pointList[k]))
                    {
                        flag = false;
                        break;
                    }
                }
            }
        }
        if (flag)
            res.push_back(pnt);
    }
    return res;
}
