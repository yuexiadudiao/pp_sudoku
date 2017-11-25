#ifndef SUDOKU_HPP
#define SUDOKU_HPP

#include"commen.h"

#include<iostream>
#include<vector>
#include<string>

using namespace std;

class Sudoku{
public:
  vector<PosePoint> pp_sudoku;
public:
  Sudoku(const string& str_sudoku);
  void toArry(int a[9][9]);
  void showArry();
  void update_ppsudoku(int update_num,const PosePoint& newpp);
  PosePoint getTemplateByNum(int num);
  PosePoint createConflict(int num);//生成数字的冲突掩码
};

Sudoku::Sudoku(const string& str_sudoku)
{
  //先检测输入的合法性，81位长度的string
  if(str_sudoku.size()!=81)
  {
    std::cerr << "[Error]:input is not a valid sudoku string!" << '\n';
    return;
  }
  //cout<<"str  :"<<str_sudoku<<endl;
  //然后创建 pp_sudoku 数据
  for(int i=1;i<=9;i++)
  {
    string num(81,'0');
    for(int j=0;j<str_sudoku.size();j++)
    {
      if(str_sudoku[j] == ('1'-1+i))
        num.at(j)='1';
    }
    pp_sudoku.push_back(PosePoint(num));

  //  cout<<"num "<<i<<":"<<num<<endl;
  }
  //检测输入数独的每个 【数字位点】 是否合法（这里不采用查询数据库的方式），如果不合法，擦除数据
  //???
}

void Sudoku::toArry(int a[9][9])
{
  for(int i=0;i<9;i++)
  {
    for(int j=80;j>=0;j--)//因为是bitset<81>是从二进制串的低位编码的，所以应该倒着输入
    {
        if(pp_sudoku[i][j] == 1)
          a[(80-j)/9][(80-j)%9]= i+1;
    }
  }
}

void Sudoku::showArry()
{
  int arr_sudoku[9][9]={0};//必须初始化
  toArry(arr_sudoku);

  for(int i=0;i<9;i++)
  {
    for(int j=0;j<9;j++)
    {
      cout<<arr_sudoku[i][j];
      if(j%3==2) cout<<"|";
    }
    if(i==2 || i==5) cout<<"\n------------";
    cout<<endl;
  }
  
}

void Sudoku::update_ppsudoku(int update_num,const PosePoint& newpp)
{
  pp_sudoku[update_num-1] = newpp;
}

PosePoint Sudoku::getTemplateByNum(int num)
{
  return pp_sudoku[num-1];
}

PosePoint Sudoku::createConflict(int num)
{
  PosePoint tishe(0);
  for(int i=0;i<9;i++)
  {
    tishe|= pp_sudoku[i];//有1则1
  }
  return tishe^pp_sudoku[num-1];//题设与自身进行异或操作
}

#endif
