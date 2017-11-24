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

class SUDOKU_DFS{
private:
  DataBase* m_db;
  Sudoku* m_sudoku;
  std::map<NumID,NumList>  m_candidatelist;
  int order[9];//顺序数组，指明数字的顺序
public:
  SUDOKU_DFS(DataBase* db,Sudoku* sudoku);
  void resetSudoku(Sudoku* sudoku);
  void create_candidatelist();
  void print_candidatelist();
  void sort_candidatelist();
  void info_candidatelist();
  void dfs();
  static bool comp(std::pair<NumID,NumList> a,std::pair<NumID,NumList> b);
};

bool SUDOKU_DFS::comp(std::pair<NumID,NumList> a,std::pair<NumID,NumList> b)
{
  return a.second.size() < b.second.size();
}

SUDOKU_DFS::SUDOKU_DFS(DataBase* db,Sudoku* sudoku)
{
  for(int i=0;i<9;i++)
    order[i]=0;//初始化顺序数组
  m_db = db;
  m_sudoku = sudoku;
  m_candidatelist.clear();

  create_candidatelist();//创建数据
  sort_candidatelist();//创建完数据之后，直接对vector排序
  print_candidatelist();//打印日志
  //dfs();//最后一步搜索
}

void SUDOKU_DFS::create_candidatelist()
{
  bool reloopflag;
  bool hasupdate[9]={0};
  do
  {
      m_candidatelist.clear();//清空前一次循环的结果
      reloopflag =false;
      for(int i=0;i<9;i++){
          NumList numlist;
          m_db->search(m_sudoku->getTemplateByNum(i+1),m_sudoku->createConflict(i+1),numlist);
          if(numlist.size()==1 && hasupdate[i]==0) //只剩下一种情况，并且该数字没有更新过
          {
              cout<<"num "<<i+1<<" has been confirmed!"<<endl;
              reloopflag = true;
              //修改pp_sudoku的内容
              m_sudoku->update_ppsudoku(i+1,m_db->getById(numlist[0]));
              hasupdate[i]=1;
              break;
          }
          m_candidatelist.insert(std::pair<NumID,NumList>(i+1,numlist));
      }
  } while (reloopflag);
  cout<<"candidatelist has been created!"<<endl;
}

/*
显示打印candidatelist到日志文件
*/
void SUDOKU_DFS::print_candidatelist()
{
  ofstream log("./candidate_log.txt");
  for(int i=0;i<9;i++)
  {
    log<<"***********************[num "<<order[i]<<" has "<<m_candidatelist[order[i]].size()<<" candidates]***********************"<<endl;
    //有没有更新无从得知，因为更新信息数组是局部变量
    log<<"Targe:"<<m_sudoku->getTemplateByNum(order[i])<<endl;
    for(int j=0;j<m_candidatelist[order[i]].size();j++)
    {
      log<<setw(5)<<m_candidatelist[order[i]][j]<<":"<<m_db->getById(m_candidatelist[order[i]][j])<<endl;
    }
    log<<endl;
  }
}



void SUDOKU_DFS::sort_candidatelist()
{
  cout<<"now sort it......"<<endl;
  vector<pair<NumID,NumList> > m_candidatelist_vec(m_candidatelist.begin(),m_candidatelist.end());
  sort(m_candidatelist_vec.begin(),m_candidatelist_vec.end(),comp);
  for(int i=0;i<9;i++)
    order[i]=m_candidatelist_vec[i].first;

  cout<<"after sort:"<<endl;
  info_candidatelist();
}

void SUDOKU_DFS::info_candidatelist()
{
  for(int i=0;i<9;i++)
  {
    cout<<"("<<order[i]<<","<<m_candidatelist[order[i]].size()<<")";
    if(i==8)  cout<<endl;
    else      cout<<"->";
  }
}

void SUDOKU_DFS::dfs()
{

}

#endif
