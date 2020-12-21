/* ====================================================
#   Copyright (C)2020 2021 fhyPayaso All rights reserved.
#
#   @Author        : fhyPayaso
#   @Date          : 2020/11/9
#   @Email         : 401619823@qq.com
#   @Description   : 
# ====================================================*/

#ifndef HITALGORITHM_PLOTUTIL_H
#define HITALGORITHM_PLOTUTIL_H

#include <opencv2/opencv.hpp>

#include "../BaseStruct.h"
#include <vector>
#include <string>

using namespace std;


class PlotUtil
{

public:

    static void
    drawConvexHull(vector<Point2i> dataPnt, vector<Point2i> resPnt, bool renderLine, string title = "convex hull")
    {

        const int IMAGE_SIZE = 1000;
        cv::Mat image(IMAGE_SIZE, IMAGE_SIZE, CV_8UC3, cv::Scalar(255, 255, 255));

        int ds = IMAGE_SIZE / 100;

        for (auto pnt: dataPnt)
        {
            cv::Point cvPnt(pnt.x * ds, pnt.y * ds);
            cv::circle(image, cvPnt, 3, cv::Scalar(0, 0, 0), -1);
        }

        for (int i = 0; i < resPnt.size(); i++)
        {
            cv::Point curPnt(resPnt[i].x * ds, resPnt[i].y * ds);

            cv::circle(image, curPnt, 3, cv::Scalar(0, 0, 255), -1);

            if (renderLine)
            {
                int nexIndex = i + 1;
                if (nexIndex == resPnt.size())
                    nexIndex = 0;

                cv::Point nexPnt(resPnt[nexIndex].x * ds, resPnt[nexIndex].y * ds);
                line(image, curPnt, nexPnt, cv::Scalar(0, 0, 255), 2);
            }
        }

//        imshow(title, image);
        string baseDir = "D:/Workspace/CodeRepository/HITAlgorithm/convexhull/data/image_";
        baseDir += std::to_string(dataPnt.size());
        baseDir += "_";
        baseDir += title;
        baseDir += ".jpg";
        cout << baseDir << endl;

        imwrite(baseDir.c_str(), image);
//        cv::waitKey(0);
    }


};


#endif //HITALGORITHM_PLOTUTIL_H
