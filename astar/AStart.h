/* ====================================================
#   Copyright (C)2020 2021 fhyPayaso All rights reserved.
#
#   @Author        : fhyPayaso
#   @Date          : 2020/11/10
#   @Email         : 401619823@qq.com
#   @Description   : 
# ====================================================*/
// 17 1.4  21 1  8
// 24.038
// 45.038 16 + 6
//
#ifndef HITALGORITHM_ASTART_H
#define HITALGORITHM_ASTART_H

#include "Maze.h"

//#define COST_NORMAL 10.0 // 直线代价
//#define COST_DIAGONAL 14.0 // 对角代价

#define COST_NORMAL 1.0 // 直线代价
#define COST_DIAGONAL sqrt(2.0) // 对角代价
#define COST_SEA 2.0 // 溪流代价
#define COST_DESERT 4.0 // 沙漠代价


class AStart
{

public:


    explicit AStart(int type);


    static void init()
    {
        int imap = 1, iSearch = 1;
        cout << "please select map : map1->1, map2->2" << endl;
        cin >> imap;
        cout << "please select search type : single->1, double->2" << endl;
        cin >> iSearch;

        AStart *aStart = new AStart(imap - 1);
        if (iSearch == 1)
            aStart->singleAStartSearch();
        if (iSearch == 2)
            aStart->doubleAStarSearch();
        aStart->render();
    }


    APoint *getMinF(vector<APoint *> list);

    void deletePoint(APoint *p, vector<APoint *> &list);

    bool isInList(APoint *p, vector<APoint *> list);

    vector<APoint *> genNeighborPoints(APoint *curPnt, bool isFromStart);

    void render();


    void singleAStartSearch();


    void doubleAStarSearch();


    // 从起点到当前结点的代价
    double buildG(APoint *curPnt, APoint *nexPnt);

    double buildH(APoint *nexPnt, bool isFromStart);

    double judgeNeighbour(APoint *p1, APoint *p2)
    {
        int dx = abs(p1->x - p2->x);
        int dy = abs(p1->y - p2->y);

        if (dx + dy == 1)
            return COST_NORMAL;
        if (dx == 1 && dy == 1)
            return COST_DIAGONAL;
        return -1.0;
    }

    void showPointInfo(APoint *p)
    {
        cout << "<";
        cout << p->y << ", " << p->x;
        cout << " (g=" << p->G << ", h=" << p->H << ", f=" << p->F << " )>" << endl;
    }

    void showListInfo(int index)
    {
        cout << "<====================== index:" << index << " =================================>" << endl;

        if (!openListStart.empty())
        {
            cout << "open list: [ ";

            for (auto p: openListStart)
            {
                cout << "<";
                cout << p->y << ", " << p->x;
                cout << " (g=" << p->G << ", h=" << p->H << ", f=" << p->F << " ) > , ";
            }
            cout << " ]" << endl;
        }

        if (!closeListStart.empty())
        {
            cout << "close list: [";

            for (auto p: closeListStart)
            {
                cout << "<";
                cout << p->y << ", " << p->x;
                cout << " (g=" << p->G << ", h=" << p->H << ", f=" << p->F << " ) > , ";
            }
            cout << " ]" << endl;
        }

    }


public:

    int mHeight, mWidth;

    APoint *startPoint;

    APoint *endPoint;

    vector<vector<APoint *>> mazeData;

    vector<APoint *> openListStart;

    vector<APoint *> closeListStart;

    vector<APoint *> openListEnd;

    vector<APoint *> closeListEnd;

    bool isCorner = true;
};


#endif //HITALGORITHM_ASTART_H
