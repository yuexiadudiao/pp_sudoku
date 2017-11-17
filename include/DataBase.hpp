#ifndef DATABASE_H
#define DATABASE_H

#include<vector>
#include<iostream>
#include<fstream>//需要读取文件
#include<algorithm>

#include"commen.h"//使用位点

using namespace std;

//数据库的大小是1550kb，约1.5M内存,但是实际测试显示内存占用为0.3M 
class DataBase{
private:
  vector<PosePoint> m_diindex;//正向索引0-46655,729kb
  vector<vector<PosePointID> > m_inindex;//反向索引0-80,820.125kb(bug1,还可以用bitset<46656>做，大约460kb，直接按位与运算)
public:
  DataBase();//构造函数自动创建数据库
  void create_allindex();//从文件中同时创建正向和反向索引
  //search API
  void search(PosePoint& pp,vector<PosePointID>& numlist);
  //match API
  bool ismatch_posepoint(const PosePointID& ppid1,const PosePointID& ppid2);
  bool ismatch_stack(const PosePointID& ppid,const vector<PosePointID> & magicstack);//这个magicstack可能要用std::map<NumID,PosePointID> 
};

DataBase::DataBase()
{
  create_allindex();
}

void DataBase::create_allindex()
{
  ifstream in("posepoint.txt");

  if(!in.is_open())
  {
    cerr<<"cannot open posepoint.txt file!"<<endl;
    exit(0);
  }

  string line;
  unsigned short count=46656;//已知行的情况下
  while(count>0)
  {
    PosePointID ppid=46656-count;//cout<<"ppid="<<ppid<<endl;

    line.clear();
    in>>line;

    //创建正向索引
    this->m_diindex.push_back(PosePoint(line));
    //创建反向索引
    this->m_inindex.resize(81);//必须初始化 
    for(int i=0;i<line.size();i++)
      if(line[i]=='1')
        this->m_inindex[i].push_back(ppid);

    count--;
  }
  in.close();
}

bool DataBase::ismatch_posepoint(const PosePointID& ppid1,const PosePointID& ppid2)
{
	//进行按位与操作，双1则冲突，和谐则0，若全0则匹配 
	if(((this->m_diindex[ppid1])&(this->m_diindex[ppid2]))==PosePoint(0))//还可以用none，any等函数 
		return true;
	else
		return false;
} 


void DataBase::search(PosePoint& pp,vector<PosePointID>& numlist)
{
	if(pp==PosePoint(0))//先处理全0的特殊情况 
	{
		for(PosePointID ppid=0;ppid<46656;ppid++)
			numlist.push_back(ppid);
		return ;
	}
	int count=0;
	
	vector<PosePointID> tmp;
	vector<PosePointID>::iterator itend;
	for(size_t i=0;i<pp.size();i++ )
	{
		if( pp.test(i) ) 
		{++count;
			if(count==1){
				tmp.insert(tmp.end(),(this->m_inindex[i]).begin(),(this->m_inindex[i]).end());
				itend = tmp.end();	
			}		
			else{
				itend = set_intersection(tmp.begin(), itend, (this->m_inindex[i]).begin(), (this->m_inindex[i]).end(), tmp.begin());
			}
		}
	}
	
	numlist.insert(numlist.end(),tmp.begin(),itend);
}
#endif