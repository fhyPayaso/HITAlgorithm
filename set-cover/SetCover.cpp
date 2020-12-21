/* ====================================================
#   Copyright (C)2020 2021 fhyPayaso All rights reserved.
#
#   @Author        : fhyPayaso
#   @Date          : 2020/11/30
#   @Email         : 401619823@qq.com
#   @Description   : 
# ====================================================*/

#include "SetCover.h"
#include <time.h>

void SetCover::pointBuilder(int originSetSize, int subSetSize)
{

    srand(time(0));
    // 构建原始有序集合
    vector<int> originSet;
    for (int i = 0; i < originSetSize; i++)
        originSet.push_back(i);

//    showSetInfo(originSet);

    // 将原始有序集合乱序重新排列
    for (int i = originSetSize - 1; i > 0; i--)
    {
        // 生成0~i-1 范围内的随机数，并将对应的数组值与当前数组值交换
        int randVal = rand() % i;
        int temp = originSet[i];
        originSet[i] = originSet[randVal];
        originSet[randVal] = temp;
    }
    this->mAllSet = originSet;
//    showSetInfo(originSet);


    // ============================================== 首先生成一组可行解 ======================================= //
    vector<int> tempSet = originSet; // 原始集合
    vector<int> sumSet; // 累加集合
    vector<vector<int>> subSetList;// 子集合序列
    //  ---------------- 1. 先取出20个结点作为S0 ----------------
    vector<int> firstS = randomSelectPoint(tempSet, subSetSize);
    addSet(sumSet, firstS);
    subSet(tempSet, firstS);
    subSetList.push_back(firstS);
    //  ---------------- 2. 计算S0 ~ Sn-1 ------------------
    while (tempSet.size() > subSetSize)
    {
        vector<int> curSubSet;

        int subSize = rand() % subSetSize + 1; // 当前子集合的长度
        int size0 = rand() % subSize + 1; // 从原始集合中取值的数量
        int size1 = subSize - size0; // 从累加集合中取值的数量


        vector<int> s0 = randomSelectPoint(tempSet, size0);
        vector<int> s1 = randomSelectPoint(sumSet, size1);
        addSet(curSubSet, s0);
        addSet(curSubSet, s1);

        addSet(sumSet, s0);
        subSet(tempSet, s0);

        if (curSubSet.size() == 1)
        {
            subSetList[0].push_back(curSubSet[0]);
        }

        subSetList.push_back(curSubSet);
    }
    //  ---------------- 3. 最后一部分作为sn ------------------

    subSetList.push_back(tempSet);

    // ============================================== 剩余的解随意生成即可 ======================================= //
    while (subSetList.size() < originSetSize)
    {
        int subSize = rand() % subSetSize + 1;
        vector<int> s = randomSelectPoint(mAllSet, subSize);
        subSetList.push_back(s);
    }

    this->mSetList = subSetList;

//    cout << "<===================== sub set list =====================>" << endl;
//    showSetListInfo(subSetList);
}

void SetCover::showSetInfo(vector<int> set)
{
    for (int i : set)
        cout << i << " ";
    cout << endl;
}

void SetCover::showSetListInfo(vector<vector<int>> setList)
{


    // 打印生成的子数组
    vector<int> test;
    int allSize = 0;
    for (int i = 0; i < setList.size(); i++)
    {
        vector<int> curSet = setList[i];
        allSize += curSet.size();
//        cout << "sub set " << i + 1 << " : [";
//        for (int num : curSet)
//            cout << " " << num;
//        cout << "] size=" << curSet.size() << endl;
        addSet(test, curSet);
    }
    cout << "set size:" << setList.size() << endl;
    cout << "cover size: " << test.size() << endl;
//    sort(test.begin(), test.end());
//    showSetInfo(test);
}

void SetCover::subSet(vector<int> &s0, vector<int> s1)
{
    vector<int> indexList;
    for (int num : s1)
    {
        int index = -1;
        for (int i = 0; i < s0.size(); i++)
        {
            if (s0[i] == num)
            {
                index = i;
                break;
            }
        }
        if (index != -1)
            s0.erase(s0.begin() + index);
    }
}

bool SetCover::isInSet(const vector<int> &set, int tag)
{
    if (set.empty())
        return false;

    for (int num:set)
        if (num == tag)
            return true;

    return false;
}

void SetCover::addSet(vector<int> &s0, vector<int> s1)
{
    if (s1.empty())
        return;

    for (auto num:s1)
        if (!isInSet(s0, num))
            s0.push_back(num);
}

vector<int> SetCover::randomSelectPoint(vector<int> set, int n)
{
    if (n >= set.size())
        return set;
    vector<int> res;

    while (res.size() < n)
    {
        int randVal = rand() % set.size();
        int num = set[randVal];
        if (!isInSet(res, num))
            res.push_back(num);
    }
    return res;
}

void SetCover::linearSetCover(bool needReal)
{
    clock_t begin, end;
    begin = clock();

    cout << "<============================= linearSetCover =============================>" << endl;

    vector<int> U = this->mAllSet;
    vector<vector<int>> S = this->mSetList;
    int size = U.size();

    // ============== 初始化 ==============
    glp_prob *lp;
    lp = glp_create_prob();
    glp_set_prob_name(lp, "sample");
    glp_set_obj_dir(lp, GLP_MIN);

    // ============== 添加行 ==============
    glp_add_rows(lp, size);
    for (int i = 1; i <= size; i++)
        glp_set_row_bnds(lp, i, GLP_LO, 1.0, 0.0); // x >= 1

    // ============== 添加列 ==============
    glp_add_cols(lp, size);
    for (int i = 1; i <= size; i++)
    {
        if (needReal)
            glp_set_col_kind(lp, i, GLP_IV);

        glp_set_col_bnds(lp, i, GLP_UP, 0.0, 1.0); // x<=1
        glp_set_col_bnds(lp, i, GLP_LO, 0.0, 0.0); // x>=0
        glp_set_obj_coef(lp, i, 1.0);
    }

    // ============== 约束矩阵的前两列 用于定位坐标 ==============
    int *ia = (int *) malloc((size * size + 1) * sizeof(int));
    int *ja = (int *) malloc((size * size + 1) * sizeof(int));
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            ia[i * size + j + 1] = i + 1;
            ja[i * size + j + 1] = j + 1;
        }
    }
    // ============== 约束矩阵的第三列 用于计算多项式 ==============
    double *es = (double *) malloc((size * size + 1) * sizeof(double));
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            es[i * size + j + 1] = 0;

    for (int i = 0; i < size; i++) // 对于原数组中每个值
    {
        for (int j = 0; j < size; j++) // 对于每个子集合
        {
            for (int k = 0; k < S[j].size(); k++) // 子集合中的每个值
            {
                // 说明U[i]在集合S[j]中出现过
                if (U[i] == S[j][k])
                    es[i * size + j + 1] = 1;
            }
        }
    }

    int maxNum = 0; // 找到子集中出现相同数字的最多次数
    for (int i = 0; i < size; i++)
    {
        // 统计每个元素在不同集合中出现的次数和
        int temp = 0;
        for (int j = 0; j < size; j++)
            temp += es[i * size + j + 1];

        if (temp > maxNum)
            maxNum = temp;
    }


    glp_load_matrix(lp, size * size, ia, ja, es); //将约束系数矩阵导入

    glp_iocp param;
    glp_init_iocp(&param);
    param.presolve = GLP_ON;
    param.msg_lev = GLP_MSG_ON;
    glp_intopt(lp, &param);


//    cout << glp_mip_obj_val(lp) << endl;
    vector<vector<int>> minSet;
    for (int i = 1; i <= size; i++)
    {
        if (glp_mip_col_val(lp, i) != 0)
        {
            if (glp_mip_col_val(lp, i) >= (1.0 / maxNum))
                minSet.push_back(mSetList[i - 1]);
        }
    }
    glp_delete_prob(lp);
    end = clock();
    clock_t diff = end - begin;

    showSetListInfo(minSet);
    cout << "time:" << diff << endl;
}

void SetCover::greedSetCover()
{
    clock_t begin, end;
    begin = clock();

    vector<int> U = this->mAllSet;
    vector<vector<int>> S = this->mSetList;

    cout << "<============================= greedSetCover =============================>" << endl;

    vector<vector<int>> minSet;
    while (!U.empty())
    {
        int index = -1;
        int maxNum = -1;
        // 寻找当前S中覆盖数最大的子集
        for (int i = 0; i < S.size(); i++)
        {
            // 寻找当前子集的覆盖数
            int coverNum = findCoverNum(U, S[i]);
            if (coverNum > maxNum)
            {
                maxNum = coverNum;
                index = i;
            }
        }

        if (index != -1)
        {
            minSet.push_back(S[index]);
            subSet(U, S[index]);
            S.erase(S.begin() + index);
        }
    }

    end = clock();
    clock_t diff = end - begin;

    showSetListInfo(minSet);
    cout << "time:" << diff << endl;
}
