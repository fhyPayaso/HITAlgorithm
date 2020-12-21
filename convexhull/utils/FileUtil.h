/* ====================================================
#   Copyright (C)2020 2021 fhyPayaso All rights reserved.
#
#   @Author        : fhyPayaso
#   @Date          : 2020/11/9
#   @Email         : 401619823@qq.com
#   @Description   : 
# ====================================================*/

#ifndef HITALGORITHM_FILEUTIL_H
#define HITALGORITHM_FILEUTIL_H

#include <fstream>
#include <sstream>
#include "../BaseStruct.h"
#include <vector>

using namespace std;

const char *POINT_TXT_DATA = "D:\\fhyPayaso\\workspace\\Code\\HITAlgorithm\\convexhull\\data\\point.txt";
const char *POINT_TXT_DATA_1000 = "D:\\fhyPayaso\\workspace\\Code\\HITAlgorithm\\convexhull\\data\\point.txt";

class FileUtil
{

public:

    static void writePoints(vector<Point2i> pntList, const char *path = POINT_TXT_DATA)
    {
        ofstream out(path);
        if (out.is_open())
        {
            for (auto p : pntList)
                out << p.x << " " << p.y << endl;
        }
        out.close();
    }

    static vector<Point2i> readPoints( const char *path = POINT_TXT_DATA)
    {
        vector<Point2i> list;

        ifstream in(path);
        int s;
        while ( !in.eof() )
        {
            Point2i pnt;
            in >> pnt.x;
            in >> pnt.y;
            list.push_back(pnt);
        }
        in.close();

        return list;
    }


};


#endif //HITALGORITHM_FILEUTIL_H
