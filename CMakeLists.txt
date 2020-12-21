cmake_minimum_required(VERSION 3.17)
project(HITAlgorithm)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_PREFIX_PATH   D:/Workspace/opencv/build)
set(OpenCV_INCLUDE_DIRS D:/Workspace/opencv/build/include)
#set(OpenCV_LIBS D:/Workspace/opencv/build/x64/vc15/lib)
set(GLPK_INCLUDE_DIRS D:/Workspace/CodeRepository/HITAlgorithm/set-cover/glpk/include)
set(GLPK_LIB_DIRS D:/Workspace/CodeRepository/HITAlgorithm/set-cover/glpk/lib)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

include_directories(${GLPK_INCLUDE_DIRS})
link_directories(${GLPK_LIB_DIRS})

add_executable(HITAlgorithm main.cpp convexhull/utils/RandomUtil.h convexhull/ConvexHull.cpp convexhull/ConvexHull.h convexhull/utils/PlotUtil.h convexhull/BaseStruct.h convexhull/utils/FileUtil.h convexhull/algorithm/BruteForce.cpp convexhull/algorithm/BruteForce.h convexhull/algorithm/GrahamScan.cpp convexhull/algorithm/GrahamScan.h convexhull/algorithm/DivideConquer.cpp convexhull/algorithm/DivideConquer.h convexhull/utils/TimeUtil.h astar/AStart.cpp astar/AStart.h astar/Maze.cpp astar/Maze.h astar/DataUtil.h astar/DataUtil.cpp set-cover/SetCover.cpp set-cover/SetCover.h quick-sort/QuickSort.cpp quick-sort/QuickSort.h)

target_link_libraries(HITAlgorithm ${OpenCV_LIBS} glpk)
#${GLPK_LIB_DIRS}/glpk_4_45.lib
