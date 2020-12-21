/* ====================================================
#   Copyright (C)2020 2021 fhyPayaso All rights reserved.
#
#   @Author        : fhyPayaso
#   @Date          : 2020/11/30
#   @Email         : 401619823@qq.com
#   @Description   : 集合覆盖问题
# ====================================================*/

#ifndef HITALGORITHM_SETCOVER_H
#define HITALGORITHM_SETCOVER_H


#include <vector>
#include <set>
#include <iostream>
#include <algorithm>
#include <glpk.h>

using namespace std;

class SetCover
{

private:

    vector<int> mAllSet;

    vector<vector<int>> mSetList;

public:

    static void init()
    {

//        for (int i = 2; i < 10; i++)
//        {
//            cout << "==========" << i << "==========" << endl;
//            int size = i * 100;
//            auto setCovert = new SetCover();
//            setCovert->pointBuilder(size, 20);
//            setCovert->greedSetCover();
//            setCovert->linearSetCover(false);
//
//        }

        int size = 100 , subSize = 20;
        cout<< "please input origin size"<<endl;
        cin>>size;
        cout<< "please input set size"<<endl;
        cin>>subSize;

        auto setCovert = new SetCover();
        setCovert->pointBuilder(100, 20);
        setCovert->greedSetCover();
        setCovert->linearSetCover(false);
//        setCovert->linearSetCover(true);
    }


    void linearSetCover(bool needReal);


    void greedSetCover();

    int findCoverNum(vector<int> U, vector<int> S)
    {
        int res = 0;
        for (int i = 0; i < S.size(); i++)
        {
            if (isInSet(U, S[i]))
                res++;
        }
        return res;
    }


    /**
     * 从集合中随机选取n个元素
     *
     * @param set
     * @param n
     * @return
     */
    vector<int> randomSelectPoint(vector<int> set, int n);


    /**
     * 集合元素相加
     * @param s0
     * @param s1
     */
    void addSet(vector<int> &s0, vector<int> s1);

    bool isInSet(const vector<int> &set, int tag);

    /**
     * 集合元素相减
     * @param s0 被减集合
     * @param s1 减集合
     */
    void subSet(vector<int> &s0, vector<int> s1);


    void showSetInfo(vector<int> set);

    void showSetListInfo(vector<vector<int>> setList);

    void pointBuilder(int originSetSize, int subSetSize);


};


#endif //HITALGORITHM_SETCOVER_H