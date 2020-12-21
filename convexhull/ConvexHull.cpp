/* ====================================================
#   Copyright (C)2020 2021 fhyPayaso All rights reserved.
#
#   @Author        : fhyPayaso
#   @Date          : 2020/11/8
#   @Email         : 401619823@qq.com
#   @Description   : 
# ====================================================*/

#include "ConvexHull.h"
#include "utils/FileUtil.h"
#include "utils/TimeUtil.h"
#include <algorithm>
#include "utils/RandomUtil.h"

void ConvexHull::init()
{
    // 凸包问题

//    for (int i = 1; i < 10; i++)
//    {
//        int size = i * 1000;
//        vector<Point2i> dataPntList = RandomUtil::buildRandomPoint(size);
//        cout << "==============" << size << "===============" << endl;
//        ConvexHull::findConvexHull(ConvexHull::CHType::GrahamScan, dataPntList);
//        ConvexHull::findConvexHull(ConvexHull::CHType::DivideConquer, dataPntList);
//    }

//    for (int i = 1; i <= 10; i++)
//    {
//        int size = i * 50;
//        vector<Point2i> dataPntList = RandomUtil::buildRandomPoint(size);
//        cout << "==============" << size << "===============" << endl;
//        ConvexHull::findConvexHull(ConvexHull::CHType::BruteForce, dataPntList);
//    }

    int size = 100;
    cout<<"please input point size: "<<endl;
    cin>>size;

    // 凸包问题
//    int size = 100;
    vector<Point2i> dataPntList = RandomUtil::buildRandomPoint(size);
    ConvexHull::findConvexHull(ConvexHull::CHType::BruteForce, dataPntList);
    ConvexHull::findConvexHull(ConvexHull::CHType::GrahamScan, dataPntList);
    ConvexHull::findConvexHull(ConvexHull::CHType::DivideConquer, dataPntList);
}


void ConvexHull::findConvexHull(ConvexHull::CHType type, vector<Point2i> dataPntList)
{

//
//    if (size == -1)
//        dataPntList = FileUtil::readPoints();
//    else
//        dataPntList = RandomUtil::buildRandomPoint(size);

    string typeName = "";

    clock_t begin, end;
    begin = clock();

    vector<Point2i> res;
    switch (type)
    {
        case BruteForce:
            res = BruteForce::bruteForce(dataPntList);
            typeName += "BruteForce";
            break;
        case GrahamScan:
            res = GrahamScan::grahamScan(dataPntList);
            typeName += "GrahamScan";
            break;
        case DivideConquer:
            res = DivideConquer::divideConquer(dataPntList);
            typeName += "DivideConquer";
            break;
        default:
            break;
    }

    // 对极角进行排序
    sort(res.begin(), res.end(), [](Point2i p1, Point2i p2)
    {
        double angle1 = std::atan2(p1.y - 50, p1.x - 50);
        double angle2 = std::atan2(p2.y - 50, p2.x - 50);
        return angle1 > angle2;
    });

    end = clock();
    cout << typeName << " time: " << end - begin << endl;


//    TimeUtil::printDuration(typeName);

    for (int i = 0; i < res.size(); ++i)
    {
        Point2i p = res[i];
        cout << "index " << i + 1 << " ====> (" << p.x << " , " << p.y << ") " << endl;
    }
    cout<<"point size: "<<res.size()<<endl;
    PlotUtil::drawConvexHull(dataPntList, res, true, typeName);
    cout<<"<================================================>"<<endl;
}
