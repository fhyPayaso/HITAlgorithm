/* ====================================================
#   Copyright (C)2020 2021 fhyPayaso All rights reserved.
#
#   @Author        : fhyPayaso
#   @Date          : 2020/11/10
#   @Email         : 401619823@qq.com
#   @Description   : 
# ====================================================*/

#include "DataUtil.h"
const char *MAZE0_DATA_PATH = "D:\\Workspace\\CodeRepository\\HITAlgorithm\\astar\\data\\maze0.txt";
const char *MAZE1_DATA_PATH = "D:\\Workspace\\CodeRepository\\HITAlgorithm\\astar\\data\\maze1.txt";
const char *MAZE2_DATA_PATH = "D:\\Workspace\\CodeRepository\\HITAlgorithm\\astar\\data\\maze2.txt";


void DataUtil::readMazeData(int maze, APoint * &pStart, APoint * &pEnd, vector<vector<APoint *>> &mazeData)
{
    const char *path = maze == 0 ? MAZE1_DATA_PATH : MAZE2_DATA_PATH;

//    const char *path = MAZE0_DATA_PATH;

    ifstream in(path);

    int height, width;
    int startY, startX;
    int endY, endX;
    in >> height >> width; // 读取第一行宽高
    in >> startY >> startX; // 读取第二行起点
    in >> endY >> endX; // 读取第三行终点


    for (int h = 0; h < height; ++h)
    {
        vector<APoint *> vec;
        for (int w = 0; w < width; ++w)
        {
            int type;
            in >> type;

            auto *p = new APoint;
            p->x = w;
            p->y = h;
            p->pointType = type;
            vec.push_back(p);

            if (p->x == startX && p->y == startY)
                pStart = p;
            else if (p->x == endX && p->y == endY)
                pEnd = p;
        }
        mazeData.push_back(vec);
    }

    in.close();
}

void DataUtil::buildFirstMazeData()
{
    ofstream out(MAZE1_DATA_PATH);

    int height = 14;
    int width = 17;

    out << height << " " << width << endl;

    vector<vector<int>> mazeData;

    for (int h = 0; h < height; ++h)
    {
        vector<int> vec;
        for (int w = 0; w < width; ++w)
        {
            vec.push_back(0);
        }
        mazeData.push_back(vec);
    }

    mazeData[5][6] = 1;
    mazeData[6][6] = 1;
    mazeData[7][7] = 1;
    mazeData[8][7] = 1;
    mazeData[9][7] = 1;
    mazeData[9][8] = 1;
    mazeData[10][8] = 1;
    mazeData[11][8] = 1;


    // 起始点
    out << 8 << " " << 3 << endl;
    // 终止点
    out << 9 << " " << 14 << endl;


    if (out.is_open())
    {
        for (int h = 0; h < height; ++h)
        {
            for (int w = 0; w < width; ++w)
            {
                out << mazeData[h][w];
                if (w < width - 1)
                    out << " ";
            }
            if (h < height - 1)
                out << endl;
        }
    }
    out.close();
}

void DataUtil::buildSecondMazeData()
{
    ofstream out(MAZE2_DATA_PATH);

    int height = 20;
    int width = 40;

    out << height << " " << width << endl;

    vector<vector<int>> mazeData;

    for (int h = 0; h < height; ++h)
    {
        vector<int> vec;
        for (int w = 0; w < width; ++w)
            vec.push_back(0);

        mazeData.push_back(vec);
    }

    // 绘制灰色 1
    for (int i = 0; i < 11; ++i)
    {
        if (i == 6)
            continue;
        mazeData[2][i] = 1;
    }

    for (int i = 2; i <= 7; ++i)
        mazeData[6][i] = 1;
    for (int i = 2; i <= 5; ++i)
        mazeData[11][i] = 1;
    for (int i = 3; i <= 8; ++i)
        mazeData[15][i] = 1;

    for (int i = 6; i <= 11; ++i)
        mazeData[i][5] = 1;

    for (int i = 11; i <= 19; ++i)
    {
        if (i == 17) continue;
        mazeData[i][3] = 1;
    }

    for (int i = 2; i <= 15; ++i)
    {
        if (i == 4) continue;
        if (i >= 6 && i <= 9) continue;
        mazeData[i][8] = 1;
    }

    for (int i = 0; i < 20; ++i)
    {
        if (i >= 8 && i <= 11)
            continue;
        mazeData[i][12] = 1;
    }

    for (int i = 0; i < 20; ++i)
    {
        if (i == 3 || i == 4 || i == 8 || i == 16)
            continue;
        if (i >= 11 && i <= 14)
            continue;
        mazeData[i][7] = 1;
    }

    mazeData[0][3] = 1;
    mazeData[7][2] = 1;
    mazeData[10][2] = 1;
    mazeData[13][9] = 1;
    mazeData[13][11] = 1;


    for (int i = 10; i <= 12; ++i)
        for (int j = 19; j <= 21; ++j)
            mazeData[i][j] = 1;

    for (int i = 15; i <= 16; ++i)
        for (int j = 24; j <= 25; ++j)
            mazeData[i][j] = 1;

    mazeData[10][28] = 1;
    mazeData[11][31] = 1;
    mazeData[13][31] = 1;
    mazeData[7][36] = 1;
    mazeData[9][36] = 1;



    // 绘制黄色 2

    int l[8] = {24, 25, 26, 26, 26, 27, 27, 29};
    int r[8] = {39, 39, 39, 36, 35, 32, 32, 32};

    for (int i = 0; i < 8; i++)
        for (int j = l[i]; j <= r[i]; j++)
            mazeData[i][j] = 2;

    // 绘制蓝色 3

    int top0[9] = {19, 18, 17, 15, 13, 12, 11, 10, 10};
    int bot0[9] = {19, 19, 19, 18, 17, 16, 14, 11, 10};
    for (int i = 0; i < 9; i++)
        for (int j = top0[i]; j <= bot0[i]; j++)
            mazeData[j][i + 28] = 3;

    int top1[4] = {8, 4, 5, 7};
    int bot1[4] = {11, 10, 9, 8};
    for (int i = 0; i < 4; i++)
        for (int j = top1[i]; j <= bot1[i]; j++)
            mazeData[j][i + 32] = 3;

    mazeData[1][34] = 3;
    mazeData[2][33] = 3;
    mazeData[3][32] = 3;


    // 起始点
    out << 10 << " " << 4 << endl;
    // 终止点
    out << 0 << " " << 35 << endl;


    if (out.is_open())
    {
        for (int h = 0; h < height; ++h)
        {
            for (int w = 0; w < width; ++w)
            {
                out << mazeData[h][w];
                if (w < width - 1)
                    out << " ";
            }
            if (h < height - 1)
                out << endl;
        }
    }
    out.close();
}
