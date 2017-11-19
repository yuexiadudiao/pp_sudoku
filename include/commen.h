#ifndef COMMEN_H
#define COMMEN_H

#include<bitset>

using namespace std;

typedef bitset<81> PosePoint;//定义位点类型，16byte
typedef unsigned short PosePointID;//定义位点的ID，2byte
typedef unsigned char NumID;
typedef vector<PosePointID> NumList;

bool comp(std::pair<NumID,NumList>& i,std::pair<NumID,NumList>& j)
{
  return i.second.size()<i.second.size();
}

#endif
