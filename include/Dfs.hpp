#ifndef DFS_HPP
#define DFS_HPP

#include"commen.h"
#include"DataBase.hpp"
#include"Sudoku.hpp"

#include<iostream>
#include<iomanip>//使用了格式输出
#include<map>
#include<vector>
#include<fstream>
#include<algorithm>//使用了sort函数

using namespace std;

class SUDOKU_DFS
{
private:
    DataBase*                   m_db;
    Sudoku*                     m_sudoku;
    std::map<NumID,NumList>     m_candidatelist;
    int                         order[9];//顺序数组，指明数字的顺序
    vector<PosePointID>         magic;

    int                         answer;/**< 答案计数器 */
    double                      timer;/**< 记录dfs算法时间 */
public:
    /**/
    SUDOKU_DFS(DataBase* db);

    /*设置或重新设置数独题目*/
    void resetSudoku(Sudoku* sudoku);

    /*为数独的每一个数字创建候选列表*/
    void create_candidatelist();

    /**/
    void print_candidatelist();

    /**/
    void sort_candidatelist();

    /**/
    void info_candidatelist();

    /**/
    void dfs(int layer);

    /**/
    double get_time();

    static bool comp(std::pair<NumID,NumList> a,std::pair<NumID,NumList> b);
};

double SUDOKU_DFS::get_time()
{
    return timer;
}

bool SUDOKU_DFS::comp(std::pair<NumID,NumList> a,std::pair<NumID,NumList> b)
{
    return a.second.size() < b.second.size();
}

SUDOKU_DFS::SUDOKU_DFS(DataBase* db):m_db(db), m_sudoku(NULL), answer(0), timer(0){}


void SUDOKU_DFS::create_candidatelist()
{
    bool reloopflag;
    bool hasupdate[9]= {0};
    do
    {
        m_candidatelist.clear();//清空前一次循环的结果
        reloopflag =false;
        for(int i=0; i<9; i++)
        {
            NumList numlist;
            //cout<<"num "<<i+1<<":"<<endl;
            //cout<<"temple="<<m_sudoku->getTemplateByNum(i+1)<<endl;
            //cout<<"confli="<<m_sudoku->createConflict(i+1)<<endl;
            m_db->search(m_sudoku->getTemplateByNum(i+1),m_sudoku->createConflict(i+1),numlist);
            if(numlist.size()==1 && hasupdate[i]==0) //只剩下一种情况，并且该数字没有更新过
            {
                //cout<<"num "<<i+1<<" has been confirmed!"<<endl;
                reloopflag = true;
                //修改pp_sudoku的内容
                m_sudoku->update_ppsudoku(i+1,m_db->getById(numlist[0]));
                hasupdate[i]=1;
                break;
            }
            m_candidatelist.insert(std::pair<NumID,NumList>(i+1,numlist));
        }
    }
    while (reloopflag);
    //cout<<"candidatelist has been created!"<<endl;
}

/*
显示打印candidatelist到日志文件
*/
void SUDOKU_DFS::print_candidatelist()
{
    ofstream log("./candidate_log.txt");
    for(int i=0; i<9; i++)
    {
        log<<"***********************[num "<<order[i]<<" has "<<m_candidatelist[order[i]].size()<<" candidates]***********************"<<endl;
        //有没有更新无从得知，因为更新信息数组是局部变量
        log<<"Targe:"<<m_sudoku->getTemplateByNum(order[i])<<endl;
        log<<"Confl:"<<m_sudoku->createConflict(order[i])<<endl;
        for(int j=0; j<m_candidatelist[order[i]].size(); j++)
        {
            log<<setw(5)<<m_candidatelist[order[i]][j]<<":"<<m_db->getById(m_candidatelist[order[i]][j])<<endl;
        }
        log<<endl;
    }
    log.close();
}



void SUDOKU_DFS::sort_candidatelist()
{
    //cout<<"now sort it......"<<endl;
    vector<pair<NumID,NumList> > m_candidatelist_vec(m_candidatelist.begin(),m_candidatelist.end());
    sort(m_candidatelist_vec.begin(),m_candidatelist_vec.end(),comp);
    for(int i=0; i<9; i++)
        order[i]=m_candidatelist_vec[i].first;

    //cout<<"after sort:"<<endl;
    //info_candidatelist();
}

void SUDOKU_DFS::info_candidatelist()
{
    for(int i=0; i<9; i++)
    {
        cout<<"("<<order[i]<<","<<m_candidatelist[order[i]].size()<<")";
        if(i==8)  cout<<endl;
        else      cout<<"->";
    }
}

void SUDOKU_DFS::dfs(int layer)
{
    if(layer==0)
    {
        for(int i=0; i < m_candidatelist[order[layer]].size(); i++)
        {
            magic.push_back(m_candidatelist[order[layer]][i]);
            dfs(layer+1);//递归
            magic.pop_back();
        }
        //cout<<"exit dfs!"<<endl;
    }
    else
    {
        for(int i=0; i < m_candidatelist[order[layer]].size(); i++)
        {
            //magic.push_back(m_candidatelist[order[layer]][i]);
            if(m_db->ismatch_stack(m_candidatelist[order[layer]][i],magic) )
            {
                magic.push_back(m_candidatelist[order[layer]][i]);//匹配就入栈
                if(layer!=8)
                    dfs(layer+1);//递归
                else//最后一层，且满足，说明招到答案
                {
                    ++answer;

                    #ifdef PRINT_ANS
                    cout<<"---------------------------------------------"<<endl;
                    cout<<"find anwser "<< answer <<" !"<<endl;
                    cout<<"---------------------------------------------"<<endl;
                    #endif

                    /*提交答案，并修改到sudoku中，这里有一个BUG，如果有多解，之保留最后一个
                    但是可以即时打印输出给用户*/
                    for(int i=0; i<9; i++)
                    {
                        m_sudoku->update_ppsudoku(order[i],m_db->getById(magic[i]));//提交修改
                    }

                    #ifdef PRINT_ANS
                    m_sudoku->showArryLine();
                    #endif

                    //只找一个解的开关
                    #ifdef JUSTONE
                    if(1 == answer)
                    {
                        return;
                    }
                    #endif
                }
                magic.pop_back();
            }
        }
    }
}
void SUDOKU_DFS::resetSudoku(Sudoku* sudoku)
{
    /*0，一些必要的初始化操作*/
    for(int i=0; i<9; i++) //初始化顺序数组
        order[i]=0;
    m_sudoku = sudoku;//重定向数独数据
    m_candidatelist.clear();//清空候选列表
    answer = 0;//答案计数器清零
    timer = 0;//计时器清零

    /*这个时候可以根据需要打印题目*/
#ifdef PRINT_ANS
    cout<<"---------------------------------------------"<<endl;
    cout<<"sudoku problem !"<<endl;
    cout<<"---------------------------------------------"<<endl;
    m_sudoku->showArry();
#endif

    time_t t1=clock();
    /*1,创建候选的位点*/
    create_candidatelist();

    /*2,排序*/
    sort_candidatelist();//创建完数据之后，直接对vector排序
    //print_candidatelist();//打印日志

    /*3,DFS 搜索*/
    dfs(0);
    time_t t2=clock();

    //记录时间消耗
    timer = (double)(t2 - t1)/CLOCKS_PER_SEC*1000;
}

#endif
