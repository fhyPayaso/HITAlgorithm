/* ====================================================
#   Copyright (C)2020 2021 fhyPayaso All rights reserved.
#
#   @Author        : fhyPayaso
#   @Date          : 2020/11/10
#   @Email         : 401619823@qq.com
#   @Description   : 
# ====================================================*/

#ifndef HITALGORITHM_DATAUTIL_H
#define HITALGORITHM_DATAUTIL_H

#include <fstream>
#include <sstream>
#include <vector>
#include "Maze.h"

using namespace std;


class DataUtil
{

public:


    static void buildFirstMazeData();

    static void buildSecondMazeData();

    static void readMazeData(int maze, APoint *&pStart, APoint *&pEnd, vector<vector<APoint *>> &mazeData);


};


#endif //HITALGORITHM_DATAUTIL_H
