/**本文件测试了相关的几个函数
*/
#include<iostream>
#include<string>


#include"DataBase.hpp"
#include"Sudoku.hpp"
#include"Dfs.hpp"

using namespace std;

/* 测试列表 */
#define TEST_API_1
#define TEST_API_2


int main(int argc,char** argv)
{

    time_t t1=clock();
    DataBase db;
    time_t t2=clock();

#ifdef TEST_API_1
    //测试 ismatch_posepoint 函数
    cout<<"testing function ismatch_posepoint()......"<<endl;
    PosePointID ppid1=0,ppid2=888;
    if(db.ismatch_posepoint(ppid1,ppid2))
        cout<<"PosePointID "<<ppid1<<" and "<<"PosePointID "<<ppid2<<" is match!"<<endl;
    else
        cout<<"PosePointID "<<ppid1<<" and "<<"PosePointID "<<ppid2<<" is not match!"<<endl;
#endif

#ifdef TEST_API_2
    //测试 ismatch_stack 函数
    cout<<"testing function ismatch_stack()......"<<endl;
    vector<PosePointID> ppidstatck;
    PosePointID q_ppid=0;
    ppidstatck.push_back(1);
    ppidstatck.push_back(2);
    ppidstatck.push_back(3);
    cout<<"PosePointID "<<q_ppid<<" vs:"<<endl;
    for(int i=0; i<ppidstatck.size(); i++)
        cout<<ppidstatck[i]<<endl;
    if(db.ismatch_stack(q_ppid,ppidstatck))
        cout<<"match stack!"<<endl;
    else
        cout<<"not match stack!"<<endl;
#endif

}
