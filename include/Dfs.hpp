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

using namespace std;

class SUDOKU_DFS{
private:
  DataBase* m_db;
  Sudoku* m_sudoku;
  std::map<NumID,NumList>  m_candidatelist;
public:
  SUDOKU_DFS(DataBase* db,Sudoku* sudoku);
  void resetSudoku(Sudoku* sudoku);
  void create_candidatelist();
  void print_candidatelist();
  void sort_candidatelist();
  void info_candidatelist();
  void dfs();
};

SUDOKU_DFS::SUDOKU_DFS(DataBase* db,Sudoku* sudoku)
{
  m_db = db;
  m_sudoku = sudoku;
  m_candidatelist.clear();

  create_candidatelist();//创建数据
  cout<<"show info_candidate:"<<endl;
  info_candidatelist();
  //sort_candidatelist();//创建完数据之后，直接对vector排序
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
          m_db->search(m_sudoku->getTemplateByNum(i+1),numlist);
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

void SUDOKU_DFS::print_candidatelist()
{
  ofstream log("./candidate_log.txt");
  for(int i=0;i<9;i++)
  {
    log<<"***********************[num "<<i+1<<" has "<<m_candidatelist[i+1].size()<<" candidates]***********************"<<endl;
    //有没有更新无从得知，因为更新信息数组是局部变量
    log<<"Targe:"<<m_sudoku->getTemplateByNum(i+1)<<endl;
    for(int j=0;j<m_candidatelist[i+1].size();j++)
    {
      log<<setw(5)<<m_candidatelist[i+1][j]<<":"<<m_db->getById(m_candidatelist[i+1][j]).to_string()<<endl;
    }
    log<<endl;
  }
}



void SUDOKU_DFS::sort_candidatelist()
{
  //先转换成vector进行sort，完了之后再转换回来
  vector<std::pair<NumID,NumList> > m_candidatelist_vec(m_candidatelist.begin(),m_candidatelist.end());
  std::sort(m_candidatelist_vec.begin(),m_candidatelist_vec.end(),comp);
  m_candidatelist.clear();
  for(int i=0;i<9;i++)
  {
    cout<<m_candidatelist_vec[i].first<<"-";
      m_candidatelist.insert(m_candidatelist_vec[i]);
  }
    /*
  cout<<"sort has been complete"<<endl;

  */
}

void SUDOKU_DFS::info_candidatelist()
{
  std::map<NumID,NumList>::iterator iter;
  for(iter=m_candidatelist.begin();iter!=m_candidatelist.end();iter++)
  {
    cout<<"(Num:"<<(iter->first)<<",can:"<<iter->second.size()<<")-";
  }
}

void SUDOKU_DFS::dfs()
{

}

#endif
