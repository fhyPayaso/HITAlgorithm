/* ====================================================
#   Copyright (C)2020 2021 fhyPayaso All rights reserved.
#
#   @Author        : fhyPayaso
#   @Date          : 2020/11/9
#   @Email         : 401619823@qq.com
#   @Description   : 
# ====================================================*/

#include "GrahamScan.h"

Point2i basePnt;

double GrahamScan::cross(Vector2f v1, Vector2f v2)
{
    return v1.x * v2.y - v1.y * v2.x;
}

vector<Point2i> GrahamScan::grahamScan(vector<Point2i> pointList)
{

    //  ======================== 找到左下角的点，作为初始点 ======================= //
    int index = 0;
    basePnt = pointList[index];
    for (int i = 1; i < pointList.size(); ++i)
    {
        Point2i p = pointList[i];
        if (p.y > basePnt.y || (p.y == basePnt.y && p.x < basePnt.x))
        {
            basePnt = p;
            index = i;
        }
    }
    swap(pointList[index], pointList[0]);

    // =============================== 根据极角排序 ============================== //
    sort(pointList.begin() + 1, pointList.end(), [](Point2i p1, Point2i p2)
    {
        Vector2f vec1(basePnt, p1);
        Vector2f vec2(basePnt, p2);
        double cross = vec1.crossProduct(vec2);

//        double tol = 1e-5;

        if (cross > 0)
        {
            // 叉积大于0 p1在p2顺时针方向
            return true;
        }
        else if (cross == 0)
        {
            // 叉积=0， 则两点在同一条线上，取距离较短的
            if (basePnt.dist(p1) < basePnt.dist(p2))
                return true;
        }

        return false;
    });

    // =============================== 寻找凸包点 ============================== //
    vector<Point2i> res;
    res.push_back(pointList[0]); // 原始结点
    res.push_back(pointList[1]);
//    res.push_back(pointList[2]);

    for (int i = 2; i < pointList.size(); i++)
    {
        int len = res.size();
        while (cross(Vector2f(res[len - 2], res[len - 1]),
                     Vector2f(res[len - 2], pointList[i])) <= 0)
        {
            res.pop_back();
            len = res.size();
            if(len < 2)
                break;
        }

        res.push_back(pointList[i]);
    }


    return res;
}
