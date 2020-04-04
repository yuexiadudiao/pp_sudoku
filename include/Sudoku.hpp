#ifndef SUDOKU_HPP
#define SUDOKU_HPP

#include"commen.h"

#include<iostream>
#include<vector>
#include<string>

using namespace std;

/**这个是sudoku的数据结构
*
*这里并不是采用二维数组存储数独，而是用数字位点表示数独，
*这种表示方法能快速生成数字的模板位点和冲突位点，只是最
*后结果需要转换一下
*/
class Sudoku
{
public:
    vector<PosePoint> pp_sudoku;
public:
    /* 根据行数独构造类 */
    Sudoku(const string& str_sudoku);

    /* 转换为二维数组 */
    void toArry(int sudoku_array[9][9]);

    /* 转换为二维数组，并九宫格显示 */
    void showArry();

    /* 转换为二维数组，并行显示 */
    void showArryLine();

    /* 获取题设中某一个数字的位点 */
    PosePoint getTemplateByNum(int num);

    /* 生成数字的冲突掩码 */
    PosePoint createConflict(int num);

    /* 如果确定了一个数字，就更新 */
    void update_ppsudoku(int update_num,const PosePoint& newpp);

    /* 校验数独的合法性 */
    bool check_sudoku();
};

/* 根据长数独字符串构造数独
 *
 * @param[in]   str_sudoku  长数独字符串
 *
 */
Sudoku::Sudoku(const string& str_sudoku)
{
    /* 输入必须是81个长度的字符串 */
    if(81 != str_sudoku.size())
    {
        std::cerr << "[Error]:input is not a valid sudoku string!\n";
        return;
    }
    //cout<<"str  :"<<str_sudoku<<endl;
    //然后创建 pp_sudoku 数据
    for(int i=1; i<=9; i++)
    {
        string num(81,'0');
        for(int j=0; j<str_sudoku.size(); j++)
        {

            if(str_sudoku[j] == ('1' - 1 + i))
                num.at(j)='1';
        }
        //题设给定的可能是不合法的，这里需要检测
        pp_sudoku.push_back(PosePoint(num));

        //  cout<<"num "<<i<<":"<<num<<endl;
    }
}

/*把长字符串数独转换成我们常用的二维数组形式
 *
 * @param[out]    sudoku_array  数独的二维数组形式
 *
 * return 无
 * 
 */
void Sudoku::toArry(int sudoku_array[9][9])
{
    for(int i=0; i<9; i++)
    {
        for(int j=80; j>=0; j--) //因为是bitset<81>是从二进制串的低位编码的，所以应该倒着输入
        {
            if(pp_sudoku[i][j] == 1)
                sudoku_array[(80-j)/9][(80-j)%9]= i+1;
        }
    }
}

/* 显示已经求解后的数独，转换为二维数组，并以九宫格显示
 *
 * @param[in]   无
 *
 * return 无
 *
 */
void Sudoku::showArry()
{
    int arr_sudoku[9][9]= {0}; //必须初始化
    toArry(arr_sudoku);

    for(int i=0; i<9; i++)
    {
        for(int j=0; j<9; j++)
        {
            if(arr_sudoku[i][j])
                cout<<arr_sudoku[i][j];
            else
                cout<<"_";
                
            if(j%3==2) cout<<"|";
        }
        if(i==2 || i==5) cout<<"\n------------";
        cout<<endl;
    }
}

/* 显示已经求解后的数独，转换为二维数组，并以行显示
 *
 * @param[in]   无
 *
 * return 无
 *
 */
void Sudoku::showArryLine()
{
    int arr_sudoku[9][9]= {0};
    toArry(arr_sudoku);
    for(int i=0; i<9; i++)
    {
        for(int j=0; j<9; j++)
        {
            cout<<arr_sudoku[i][j];
        }
    }
    cout<<endl;
}

/* 查询数独已经填写的数字对应的位点数据
 *
 * @param[in]   num     数独中数字
 *
 * return 数独中已经确定的数字对应的位点数据
 *
 */
PosePoint Sudoku::getTemplateByNum(int num)
{
    return pp_sudoku[num-1];
}

/* 如果确定了一个数字，就更新
 *
 * @param[in]   update_num      已经确定的数字
 * @param[in]   newpp           该数字对应的位点数据
 *
 * return 无
 *
 */
void Sudoku::update_ppsudoku(int update_num,const PosePoint& newpp)
{
    pp_sudoku[update_num-1] = newpp;
}

/* 题设除去特定数字
 *
 * @param[in]   
 *
 * return 无
 *
 */
PosePoint Sudoku::createConflict(int num)
{
    PosePoint tishe(0);
    for(int i=0; i<9; i++)
    {
        tishe|= pp_sudoku[i];//有1则1
    }
    return tishe^pp_sudoku[num-1];//题设与自身进行异或操作
}

bool Sudoku::check_sudoku()
{
    return true;
}

#endif