/* ====================================================
#   Copyright (C)2020 2021 fhyPayaso All rights reserved.
#
#   @Author        : fhyPayaso
#   @Date          : 2020/11/30
#   @Email         : 401619823@qq.com
#   @Description   : 
# ====================================================*/

#ifndef HITALGORITHM_QUICKSORT_H
#define HITALGORITHM_QUICKSORT_H

#include <vector>
#include <iostream>
#include <time.h>
#include <algorithm>

using namespace std;

class QuickSort
{


public:

    static void init()
    {
        for (int i = 0; i <= 10; i++)
        {
            double a = i * 1.0 / 10.0;
            cout << "<====  " << a << "===>" << endl;
            auto sort = new QuickSort();
            sort->buildList(1000000, a);
            sort->quickSort(QuickSort::STANDARD);
//            sort->quickSort(QuickSort::SINGLE);
            sort->quickSort(QuickSort::DOUBLE);
            sort->quickSort(QuickSort::TRIPLE);
        }
    }

    enum TYPE
    {
        SINGLE, // 单路快排
        DOUBLE, // 双路快排
        TRIPLE, // 三路快排
        STANDARD // 库函数
    };


    vector<int> list;

    void buildList(int size, double repeat);

    void showListInfo(vector<int> list);


    void quickSort(TYPE type)
    {
        vector<int> sortList = this->list;

        clock_t begin, end;
        begin = clock();
        switch (type)
        {
            case SINGLE:
            {
                cout << "single: ";
                singleQuickSort(sortList, 0, sortList.size() - 1);
                break;
            }
            case DOUBLE:
            {
                cout << "double: ";
                doubleQuickSort(sortList, 0, sortList.size() - 1);
                break;
            }
            case TRIPLE:
            {
                cout << "triple: ";
                tripleQuickSortHelper(sortList, 0, sortList.size() - 1);
                break;
            }
            case STANDARD:
            {
                cout << "standard: ";
                sort(sortList.begin(), sortList.end());
                break;
            }
            default:
                break;
        }
        end = clock();
        cout << end - begin << endl;

//        showListInfo(sortList);
    }

    void tripleQuickSortHelper(vector<int> &list, int left, int right);


    void doubleQuickSort(vector<int> &list, int left, int right);

    int doubleQuickSortHelper(vector<int> &list, int left, int right);

    void singleQuickSort(vector<int> &list, int left, int right);

    int singleQuickSortHelper(vector<int> &list, int left, int right);

};


#endif //HITALGORITHM_QUICKSORT_H


