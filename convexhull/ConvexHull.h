/* ====================================================
#   Copyright (C)2020 2021 fhyPayaso All rights reserved.
#
#   @Author        : fhyPayaso
#   @Date          : 2020/11/8
#   @Email         : 401619823@qq.com
#   @Description   : 
# ====================================================*/

#ifndef HITALGORITHM_CONVEXHULL_H
#define HITALGORITHM_CONVEXHULL_H

#include "algorithm/BruteForce.h"
#include "algorithm/GrahamScan.h"
#include "algorithm/DivideConquer.h"
#include "utils/PlotUtil.h"

#include <iostream>

class ConvexHull
{

public:

    enum CHType
    {
        BruteForce,
        GrahamScan,
        DivideConquer
    };


    static void findConvexHull( CHType type, vector<Point2i> dataPntList);


    static void init();


};


#endif //HITALGORITHM_CONVEXHULL_H
