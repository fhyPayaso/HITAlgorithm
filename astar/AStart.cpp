/* ====================================================
#   Copyright (C)2020 2021 fhyPayaso All rights reserved.
#
#   @Author        : fhyPayaso
#   @Date          : 2020/11/10
#   @Email         : 401619823@qq.com
#   @Description   : 
# ====================================================*/

#include "AStart.h"

#include "DataUtil.h"


AStart::AStart(int type)
{
    DataUtil::readMazeData(type, startPoint, endPoint, mazeData);
    this->mHeight = mazeData.size();
    this->mWidth = mazeData[0].size();
}

APoint *AStart::getMinF(vector<APoint *> list)
{
    if (list.empty())
        return nullptr;

    APoint *p = list[0];
    for (int i = 1; i < list.size(); ++i)
        if (list[i]->F <= p->F)
            p = list[i];

    return p;
}

void AStart::deletePoint(APoint *p, vector<APoint *> &list)
{
    if (list.empty())
        return;

    int index = -1;
    for (int i = 0; i < list.size(); ++i)
    {
        if (list[i]->x == p->x && list[i]->y == p->y)
        {
            index = i;
            break;
        }
    }
    if (index != -1)
        list.erase(list.begin() + index);
}

bool AStart::isInList(APoint *p, vector<APoint *> list)
{
    if (list.empty())
        return false;
    for (auto &i : list)
    {
        if (p->x == i->x && p->y == i->y)
            return true;
    }
    return false;
}

vector<APoint *> AStart::genNeighborPoints(APoint *curPnt, bool isFromStart)
{
    vector<APoint *> list;

    int hMove[9] = {-1, -1, -1, 0, 0, 0, 1, 1, 1};
    int wMove[9] = {-1, 0, 1, -1, 0, 1, -1, 0, 1};

    for (int i = 0; i < 9; ++i)
    {
        int y = curPnt->y + hMove[i];
        int x = curPnt->x + wMove[i];

        // 点本身或超出地图范围
        if (i == 4 || y < 0 || x < 0 || y >= mHeight || x >= mWidth)
            continue;
        APoint *nexPnt = mazeData[y][x];
        // 障碍物或已经遍历过
        if (nexPnt->pointType == 1)
            continue;

//        // 如果墙壁的拐角点不能通过
//        if (isCorner)
//        {
//            if (i == 0 && (mazeData[y + 1][x]->pointType == 1 || mazeData[y][x + 1]->pointType == 1))
//                continue;
//            if (i == 2 && (mazeData[y + 1][x]->pointType == 1 || mazeData[y][x - 1]->pointType == 1))
//                continue;
//            if (i == 6 && (mazeData[y - 1][x]->pointType == 1 || mazeData[y][x + 1]->pointType == 1))
//                continue;
//            if (i == 8 && (mazeData[y - 1][x]->pointType == 1 || mazeData[y][x - 1]->pointType == 1))
//                continue;
//        }


        if (isFromStart && isInList(nexPnt, closeListStart))
            continue;
        if (!isFromStart && isInList(nexPnt, closeListEnd))
            continue;

        list.push_back(nexPnt);
    }
    return list;
}

double AStart::buildG(APoint *curPnt, APoint *nexPnt)
{
    // 移动代价
    int dx = abs(curPnt->x - nexPnt->x);
    int dy = abs(curPnt->y - nexPnt->y);
    double moveCost = (dx + dy == 1) ? COST_NORMAL : COST_DIAGONAL;
    // 地形代价
    double landCost = 0;
    if (mazeData[nexPnt->y][nexPnt->x]->pointType == 2)
        landCost += COST_DESERT;
    else if (mazeData[nexPnt->y][nexPnt->x]->pointType == 3)
        landCost += COST_SEA;
    // 当前步代价
    double curCost = moveCost + landCost;
//    double previousCost = curPnt->parent == nullptr ? 0 : curPnt->parent->G;
    double previousCost = curPnt->G;
    return previousCost + curCost;
}

double AStart::buildH(APoint *nexPnt, bool isFromStart)
{

    APoint *finalPnt = isFromStart ? endPoint : startPoint;

    int dx = finalPnt->x - nexPnt->x;
    int dy = finalPnt->y - nexPnt->y;

    // 欧几里得距离作为启发函数
    dx = abs(dx);
    dy = abs(dy);
    return sqrt(dx * dx + dy * dy) + nexPnt->G;
//    return sqrt(dx * dx + dy * dy);
//    return (abs(dx) + abs(dy));
}

void AStart::render()
{
    Maze maze;
    maze.renderMaze(mazeData, startPoint, endPoint);
}

void AStart::singleAStartSearch()
{
    startPoint->G = 0;
    startPoint->H = buildH(startPoint, true);
    startPoint->F = startPoint->G + startPoint->H;

    openListStart.push_back(startPoint);
    while (!openListStart.empty())
    {
        APoint *curPnt = getMinF(openListStart);
        closeListStart.push_back(curPnt);
        deletePoint(curPnt, openListStart);

        // 获取当前结点周围的点
        vector<APoint *> neighbors = genNeighborPoints(curPnt, true);
        if (neighbors.empty())
            continue;

        for (APoint *nexPnt : neighbors)
        {
            if (!isInList(nexPnt, openListStart))
            {
                nexPnt->parent = curPnt;
                nexPnt->G = buildG(curPnt, nexPnt);
                nexPnt->H = buildH(nexPnt, true);
                nexPnt->F = nexPnt->G + nexPnt->H;
                openListStart.push_back(nexPnt);

            }
            else
            {
                double curG = buildG(curPnt, nexPnt);
                if (curG < nexPnt->G)
                {
                    nexPnt->parent = curPnt;
                    nexPnt->G = curG;
                    nexPnt->F = curG + nexPnt->H;
                }
            }
        }

        // 已经到达终点
        if (isInList(endPoint, openListStart))
        {
            APoint *p = endPoint;
            while (p != nullptr)
            {
                p->pointType = 4;
                p = p->parent;
            }
            showPointInfo(endPoint);
            return;
        }
    }
}

void AStart::doubleAStarSearch()
{
    openListStart.push_back(startPoint);
    openListEnd.push_back(endPoint);

    int index = 0;

    while (!openListStart.empty() && !openListEnd.empty())
    {
        APoint *curPntS = getMinF(openListStart);
        APoint *curPntE = getMinF(openListEnd);

        ++index;

        closeListStart.push_back(curPntS);
        closeListEnd.push_back(curPntE);
        deletePoint(curPntS, openListStart);
        deletePoint(curPntE, openListEnd);

        // 获取当前结点周围的点
        vector<APoint *> startNeighbors = genNeighborPoints(curPntS, true);
        vector<APoint *> endNeighbors = genNeighborPoints(curPntE, false);

        for (APoint *nexPnt : startNeighbors)
        {
            if (!isInList(nexPnt, openListStart))
            {
                nexPnt->parent = curPntS;
                nexPnt->G = buildG(curPntS, nexPnt);
                nexPnt->H = buildH(nexPnt, true);
                nexPnt->F = nexPnt->G + nexPnt->H;
                openListStart.push_back(nexPnt);
            }
//            else
//            {
//                double curG = buildG(curPntS, nexPnt);
//                if (curG < nexPnt->G)
//                {
//                    nexPnt->parent = curPntS;
//                    nexPnt->G = curG;
//                    nexPnt->F = curG + nexPnt->H;
//                }
//            }
        }

        for (APoint *nexPnt : endNeighbors)
        {
            if (!isInList(nexPnt, openListEnd))
            {
                nexPnt->parent = curPntE;
                nexPnt->G = buildG(curPntE, nexPnt);
                nexPnt->H = buildH(nexPnt, false);
                nexPnt->F = nexPnt->G + nexPnt->H;
                openListEnd.push_back(nexPnt);
            }
//            else
//            {
//                double curG = buildG(curPntE, nexPnt);
//                if (curG < nexPnt->G)
//                {
//                    nexPnt->parent = curPntE;
//                    nexPnt->G = curG;
//                    nexPnt->F = curG + nexPnt->H;
//                }
//            }
        }

        // 检查两个活结点表是否已经存在相交点
        APoint *nPntStart;
        APoint *nPntEnd;
        double dis = INT_MAX;
        bool flag = false;

        for (auto ps : openListStart)
        {
            for (auto pe : openListEnd)
            {
                double curDis = judgeNeighbour(ps, pe);
                double allDis = curDis + ps->G + pe->G;
                if (curDis > 0 && allDis < dis)
                {
                    nPntStart = ps;
                    nPntEnd = pe;
                    dis = allDis;
                    flag = true;
                }
//                if (curDis > 0 && curDis < dis)
//                {
//                    nPntStart = ps;
//                    nPntEnd = pe;
//                    dis = curDis;
//                    flag = true;
//                }
            }
        }

        if (flag)
        {
//            cout << dis + nPntStart->G + nPntEnd->G<< endl;
            cout << dis << endl;
            while (nPntStart != nullptr)
            {
                nPntStart->pointType = 4;
                nPntStart = nPntStart->parent;
            }

            while (nPntEnd != nullptr)
            {
                nPntEnd->pointType = 5;
                nPntEnd = nPntEnd->parent;
            }
            return;
        }

    }

}

