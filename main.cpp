#include <iostream>
#include <cmath>
#include <cstdlib>

#include "convexhull/ConvexHull.h"
#include "astar/AStart.h"
#include "astar/DataUtil.h"

#include "set-cover/SetCover.h"
#include "quick-sort/QuickSort.h"


void showMenu()
{
    cout << "<=====================================>" << endl;
    cout << "please select algorithm: " << endl;
    cout << "1.  Convex hull " << endl;
    cout << "2.  AStart search " << endl;
    cout << "3.  Set cover " << endl;
    cout << "4.  Quick sort " << endl;
}

int main()
{

    int flag;
    showMenu();
    while (cin >> flag)
    {
        switch (flag)
        {
            case 1:
                ConvexHull::init();
                break;
            case 2:
                AStart::init();
                break;
            case 3:
                SetCover::init();
                break;
            case 4:
                QuickSort::init();
                break;
            default:
                cout << "please select 1~4" << endl;
                break;
        }
        showMenu();
    }
    return 0;
}