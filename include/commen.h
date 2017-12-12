#ifndef COMMEN_H
#define COMMEN_H

#include<bitset>
#include<vector>

using namespace std;

typedef bitset<81> PosePoint;//定义位点类型，16byte
typedef unsigned short PosePointID;//定义位点的ID，2byte
typedef unsigned char NumID;
typedef vector<PosePointID> NumList;

#endif
