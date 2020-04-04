#ifndef DATABASE_H
#define DATABASE_H

#include <vector>
#include <iostream>
#include <fstream>
#include <string>

#include "commen.h"//使用位点

using namespace std;

//数据库的大小是1550kb，约1.5M内存,但是实际测试显示内存占用为0.3M
class DataBase
{
private:
    vector<PosePoint> m_diindex;/**< 记录0-46655号位点的具体数据 */
    vector<vector<PosePointID> > m_inindex;/**< 反向索引0-80,820.125kb(bug1,还可以用bitset<46656>做，大约460kb，直接按位与运算) */
    string path;/**< posepoint文件位置 */
    double timer;/**< 创建数据库耗时 */
public:
    /* 创建数据库，并记录时间 */
    DataBase(const string& path_to_pp);

    /* 读取文件创建正向和反向索引 */
    void create_allindex();

    /* 获取一个ID对应的位点数据 */
    PosePoint getById(PosePointID ppid)
    {
        return m_diindex[ppid];
    }

    /* 检索出满足给定数字又不与已填空格冲突的候选位点 */
    void search(const PosePoint& pp,const PosePoint& conflict,vector<PosePointID>& numlist);

    /* 检查一个位点是否与另一个匹配 */
    bool ismatch_posepoint(const PosePointID& ppid1,const PosePointID& ppid2);

    /* 检查一个位点是否与一个位点集合匹配 */
    bool ismatch_stack(const PosePointID& ppid,const vector<PosePointID> & ppid_stack);//这个magicstack可能要用std::map<NumID,PosePointID>

    /* 获取数据库创建的时间 */
    double get_time()
    {
        return timer;
    }
};

/* 数据库构造函数
 *
 * @param[in]   posepoint文件所在位置
 *
 * return null
 *
 */
DataBase::DataBase(const string& path_to_pp):path(path_to_pp)
{
    timer = 0;

    time_t t1 = clock();
    create_allindex();
    time_t t2 = clock();

    timer = (double)(t2 - t1)/CLOCKS_PER_SEC*1000;
}

/* 创建数据库正向和反向索引
 *
 * @param[in] 无
 *
 * return 无
 *
 */
void DataBase::create_allindex()
{
    ifstream in(path);

    if(!in.is_open())
    {
        cerr<<"[Error]:cannot open posepoint.txt file!"<<endl;
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
        for(int i=0; i<line.size(); i++)
            if(line[i]=='1')
                this->m_inindex[80-i].push_back(ppid);//string的i位其实是二进制的高位

        count--;
    }
    in.close();
}

/* 比较一个位点是否与另一个匹配
 *
 * @param[in]   ppid1   需要比较的第一个位点
 * @param[in]   ppid2   需要比较的第二个位点
 *
 * @return 匹配返回true，不匹配返回false
 *
 */
bool DataBase::ismatch_posepoint(const PosePointID& ppid1,const PosePointID& ppid2)
{
    /* 检查位点id和合法性 */
    if(ppid1<0 || ppid2<0 || ppid1>46655 || ppid2>46655 )
    {
        cerr<<"[Error]:PosePointID is not valid!"<<endl;
    }

    /* 进行按位与操作，双1则冲突，和谐则0，若全0则匹配 */
    if(((this->m_diindex[ppid1])&(this->m_diindex[ppid2])) == PosePoint(0))//还可以用none，any等函数
    {
        return true;
    }
    else
    {
        return false;
    }
}

/* 比较一个位点是否与位点集合匹配
 *
 * @param[in]   ppid        待比较的一个位点
 * @param[in]   ppid_stack  待匹配的位点集合
 *
 * return 匹配返回true，不匹配返回false
 *
 */
bool DataBase::ismatch_stack(const PosePointID& ppid,const vector<PosePointID>& ppid_stack )
{
    for(int i=0; i < ppid_stack.size(); i++)
    {
        if(!ismatch_posepoint(ppid,ppid_stack[i]))
        {
            return false;
        }
    }
    return true;
}

/**搜索出候选位点
*
*候选位点必须满足以下条件：
*1,满足模板 pp
*2,不与已经填写的数字有冲突
*
* @param[in]    pp          满足模板
* @param[in]    conflict    题设中已经填写的数字
* @param[out]    numlist    满足以上两个条件的候选位点集合
*
* return 无
*/
void DataBase::search(const PosePoint& pp,const PosePoint& conflict,vector<PosePointID>& numlist)
{
    if(pp == PosePoint(0))//先处理全0的特殊情况
    {
        //for(PosePointID ppid=0;ppid<46656;ppid++)
        //  numlist.push_back(ppid);
        for(PosePointID ppid=0; ppid<46656; ppid++)
        {
            if((conflict & this->m_diindex[ppid]) == 0)
            {
                numlist.push_back(ppid);
            }
        }

        return ;
    }

    for(PosePointID ppid=0; ppid<46656; ppid++)
    {
        if( (pp & this->m_diindex[ppid])== pp)
        {
            if((conflict & this->m_diindex[ppid]) == 0)
            {
                numlist.push_back(ppid);
            }
        }
    }
}
#endif
