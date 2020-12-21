/* ====================================================
#   Copyright (C)2020 2021 fhyPayaso All rights reserved.
#
#   @Author        : fhyPayaso
#   @Date          : 2020/11/10
#   @Email         : 401619823@qq.com
#   @Description   : 
# ====================================================*/

#ifndef HITALGORITHM_MAZE_H
#define HITALGORITHM_MAZE_H

#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <vector>
#include <string>

using namespace std;

struct APoint
{
    // 当前结点的坐标
    int x;
    int y;

    double F; // G + H
    double G; // 从起点到当前结点的代价
    double H; // 从当前结点到终点的预估代价

    APoint *parent = nullptr; // 当前结点的父结点

    int pointType;

    APoint(int xx = 0, int yy = 0) : parent(nullptr), F(0), G(0), H(0), x(xx), y(yy)
    {}
};

class Maze
{

public:

    void renderMaze(vector<vector<APoint *>> maze, APoint *pStart, APoint *pEnd);

    void renderBlock(cv::Mat &image, APoint *aPoint, int size);

    void renderText(cv::Mat &image, APoint *aPoint, int size, const string &text);

};


#endif //HITALGORITHM_MAZE_H
