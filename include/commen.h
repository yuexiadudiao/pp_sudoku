#ifndef COMMEN_H
#define COMMEN_H

#include<bitset>
#include<vector>

using namespace std;

typedef bitset<81> PosePoint;        /**< 定义位点数据，16byte */
typedef unsigned short PosePointID;  /**< 定义位点的ID，2byte */
typedef unsigned char NumID;         /**< 数独数字 */
typedef vector<PosePointID> NumList; /**< 某一个数字候选位点集合 */

#endif
