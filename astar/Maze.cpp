/* ====================================================
#   Copyright (C)2020 2021 fhyPayaso All rights reserved.
#
#   @Author        : fhyPayaso
#   @Date          : 2020/11/10
#   @Email         : 401619823@qq.com
#   @Description   : 
# ====================================================*/

#include "Maze.h"

const cv::Scalar COLOR_BLACK(0, 0, 0);
const cv::Scalar COLOR_GRAY(128, 128, 128);
const cv::Scalar COLOR_YELLOW(0, 192, 255);
const cv::Scalar COLOR_BLUE(240, 176, 0);

const cv::Scalar COLOR_PATH0(0, 176, 0);
const cv::Scalar COLOR_PATH1(0, 0, 176);


const int BLOCK_SIZE = 30;

void Maze::renderMaze(vector<vector<APoint *>> maze, APoint *pStart, APoint *pEnd)
{
    int height = maze.size();
    int width = maze[0].size();

    cv::Mat image(height * BLOCK_SIZE, width * BLOCK_SIZE, CV_8UC3, cv::Scalar(255, 255, 255));

    for (int h = 0; h < height; ++h)
        for (int w = 0; w < width; ++w)
            renderBlock(image, maze[h][w], BLOCK_SIZE);

    // 标记起始点和终止点
    renderText(image, pStart, BLOCK_SIZE, "S");
    renderText(image, pEnd, BLOCK_SIZE, "T");

    imshow("maze", image);
    cv::waitKey(0);
}

void Maze::renderBlock(cv::Mat &image, APoint *aPoint, int size)
{

    cv::Point pnt0(aPoint->x * size, aPoint->y * size);
    cv::Point pnt1((aPoint->x + 1) * size, (aPoint->y + 1) * size);

    if (aPoint->pointType == 1) // 灰色墙路径
        cv::rectangle(image, pnt0, pnt1, COLOR_GRAY, -1);
    else if (aPoint->pointType == 2) // 沙漠路径
        cv::rectangle(image, pnt0, pnt1, COLOR_YELLOW, -1);
    else if (aPoint->pointType == 3) // 河流路径
        cv::rectangle(image, pnt0, pnt1, COLOR_BLUE, -1);
    else if (aPoint->pointType == 4) // 单向最优路径
        cv::rectangle(image, pnt0, pnt1, COLOR_PATH0, -1);
    else if (aPoint->pointType == 5) // 双向最优路径
        cv::rectangle(image, pnt0, pnt1, COLOR_PATH1, -1);

    cv::rectangle(image, pnt0, pnt1, COLOR_BLACK);
}

void Maze::renderText(cv::Mat &image, APoint *aPoint, int size, const string &text)
{
    cv::Point originPnt(aPoint->x * size + 0.4 * size, aPoint->y * size + 0.6 * size);
    cv::putText(image, text, originPnt, 1.0, 1.0, COLOR_BLACK, 2.0);
}
