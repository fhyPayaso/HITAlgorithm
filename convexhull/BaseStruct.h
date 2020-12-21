/* ====================================================
#   Copyright (C)2020 2021 fhyPayaso All rights reserved.
#
#   @Author        : fhyPayaso
#   @Date          : 2020/11/9
#   @Email         : 401619823@qq.com
#   @Description   : 
# ====================================================*/

#ifndef HITALGORITHM_BASESTRUCT_H
#define HITALGORITHM_BASESTRUCT_H

#include <cmath>

struct Point2i
{
    int x;
    int y;

    Point2i(int ix = 0, int iy = 0)
    {
        x = ix;
        y = iy;
    }

    double dist(Point2i pnt)
    {
        int dx = pnt.x - x;
        int dy = pnt.y - y;
        return sqrt(1.0 * dx * dx + 1.0 * dy * dy);
    }

};

struct Vector2f
{
    Vector2f();

    Vector2f(Point2i start, Point2i end)
    {
        this->x = end.x - start.x;
        this->y = end.y - start.y;
    }

    double crossProduct(Vector2f vec)
    {
        return x * vec.y - y * vec.x;
    }

    double x;
    double y;

};

#endif //HITALGORITHM_BASESTRUCT_H
