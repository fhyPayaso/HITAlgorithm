/* ====================================================
#   Copyright (C)2020 2021 fhyPayaso All rights reserved.
#
#   @Author        : fhyPayaso
#   @Date          : 2020/11/30
#   @Email         : 401619823@qq.com
#   @Description   : 
# ====================================================*/

#include "QuickSort.h"

void QuickSort::buildList(int size, double repeat)
{
    list.clear();
    srand(time(0));

    int size0 = size * repeat; // 重复数据
    int size1 = size - size0; // 非重复数据

    // 构建原始有序集合
    for (int i = 0; i < size; i++)
    {
        if (i < size1)
            list.push_back(i);
        else
            list.push_back(size1 / 2);
    }


    // 将原始有序集合乱序重新排列
    for (int i = size - 1; i > 0; i--)
    {
        // 生成0~i-1 范围内的随机数，并将对应的数组值与当前数组值交换
        int randVal = rand() % i;
        int temp = list[i];
        list[i] = list[randVal];
        list[randVal] = temp;
    }
//    cout << "data build done" << endl;
//    showListInfo(list);
}

void QuickSort::showListInfo(vector<int> list)
{
    for (int i : list)
        cout << i << " ";
    cout << endl;
}

void QuickSort::doubleQuickSort(vector<int> &list, int left, int right)
{
    if (left < right)
    {
        int mid = doubleQuickSortHelper(list, left, right);
        doubleQuickSort(list, left, mid - 1);
        doubleQuickSort(list, mid + 1, right);
    }
}

int QuickSort::doubleQuickSortHelper(vector<int> &list, int left, int right)
{

    int l = left, r = right;

    int diff = right - left;
    int randVal = rand();
    int i = left + randVal % (diff + 1);
    swap(list[left], list[i]);

    int X = list[left];
    while (l < r)
    {
        while (l < r && list[r] > X)
            r--;
        if (l < r)
        {
            list[l] = list[r];
            l++;
        }

        while (l < r && list[l] < X)
            l++;
        if (l < r)
        {
            list[r] = list[l];
            r--;
        }
    }
    list[l] = X;
    return l;
}

void QuickSort::singleQuickSort(vector<int> &list, int left, int right)
{
    if (left < right)
    {
        int mid = singleQuickSortHelper(list, left, right);
        singleQuickSort(list, left, mid - 1);
        singleQuickSort(list, mid + 1, right);
    }
}

int QuickSort::singleQuickSortHelper(vector<int> &list, int left, int right)
{
    int diff = right - left;
    int randVal = rand();
    int i = left + randVal % (diff + 1);
    swap(list[right], list[i]);
    int x = list[right];
    i = left - 1;
    for (int j = left; j < right; j++)
    {
        if (list[j] <= x)
        {
            i++;
            swap(list[j], list[i]);
        }
    }
    swap(list[i + 1], list[right]);
    return i + 1;
}

void QuickSort::tripleQuickSortHelper(vector<int> &list, int left, int right)
{
    if (left > right)
        return;
    int diff = right - left;
    int randIndex = left + rand() % (diff + 1);
    swap(list[left], list[randIndex]);
    int X = list[left];

    int l = left, r = right + 1;
    int i = l + 1;
    while (i < r)
    {
        if (list[i] < X)
        {
            swap(list[i], list[l + 1]);
            l++;
            i++;
        }
        else if (list[i] > X)
        {
            swap(list[i], list[r - 1]);
            r--;
        }
        else
        {
            i++;
        }
    }
    swap(list[left], list[l]);
    tripleQuickSortHelper(list, left, l - 1);
    tripleQuickSortHelper(list, r, right);
}

