/* ====================================================
#   Copyright (C)2020 2021 fhyPayaso All rights reserved.
#
#   @Author        : fhyPayaso
#   @Date          : 2020/11/9
#   @Email         : 401619823@qq.com
#   @Description   : 
# ====================================================*/

#include "DivideConquer.h"

int DivideConquer::triangleS(Point2i a1, Point2i a2, Point2i a3)
{
    // 计算三角形的面积的2倍，正数为上凸包三角形 负数为下凸包三角形
    int calculate = a1.x * a2.y + a3.x * a1.y + a2.x * a3.y - a3.x * a2.y - a2.x * a1.y - a1.x * a3.y;
    // x1*y2 + x3*y1 + x3*y2 - x3* y2 - x2*y1 - x1*y3
    return calculate;
}

void DivideConquer::divide(int first, int last, vector<Point2i> nodeList, vector<Point2i> &vist)
{
    int maxS = 0;
    int maxIndex = -1;

    if (first < last)
    {
        for (int i = first + 1; i < last; i++)
        {
            int S = triangleS(nodeList[first], nodeList[i], nodeList[last]);
            // 同一条线
//                if(S == 0)
//                    vist.push_back(nodeList[i]);
            if (S > maxS)
            {
                maxIndex = i;
                maxS = S;
            }
        }
    }
    else
    {
        for (int i = first - 1; i > last; i--)
        {
            int S = triangleS(nodeList[first], nodeList[i], nodeList[last]);

//                if(S == 0)
//                    vist.push_back(nodeList[i]);

            if (S > maxS)
            {
                maxIndex = i;
                maxS = S;
            }
        }
    }

    if (maxIndex != -1)
    {
        vist.push_back(nodeList[maxIndex]);
        divide(first, maxIndex, nodeList, vist);
        divide(maxIndex, last, nodeList, vist);
    }

}

vector<Point2i> DivideConquer::divideConquer(vector<Point2i> pointList)
{
    sort(pointList.begin(), pointList.end(), [](Point2i p1, Point2i p2)
    {
        if (p1.x != p2.x)
            return p1.x < p2.x;
        return p1.y < p2.y;
    });

    int len = pointList.size();
    vector<int> vist(len);

    vector<Point2i> res;
    // 起始终止点必然为凸包点
    res.push_back(pointList[0]);
    res.push_back(pointList.back());
    divide(0, len - 1, pointList,res); // 上凸包
    divide(len-1, 0, pointList,res); // 下凸包

    return res;
}

