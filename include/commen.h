#ifndef COMMEN_H
#define COMMEN_H

#include<bitset>
#include<vector>

using namespace std;

typedef bitset<81> PosePoint;        /**< posepoint data，16byte */
typedef unsigned short PosePointID;  /**< posepoint ID，2byte */
typedef unsigned char NumID;         /**< sudoku number */
typedef vector<PosePointID> NumList; /**< 某一个数字候选位点集合 */

#endif
