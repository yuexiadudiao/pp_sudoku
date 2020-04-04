/**测试单独的一个数独的求解
*
*打印题目与求解结果
*/

#define PRINT_ANS //显示开关

#include<iostream>
#include<string>

#include"DataBase.hpp"
#include"Sudoku.hpp"
#include"Dfs.hpp"

using namespace std;

int main(int argc,char** argv)
{
    if(2 != argc)
    {
        cerr<<"[Error]:please input sudoku!"<<endl;
        exit(1);
    }
    
    bool success = false;

    /*1，创建数据库*/
    DataBase db("./posepoint.txt");
    /*2，创建数独*/
    string str(argv[1]);
    Sudoku mysudoku(str);
    /*3，创建求解器*/
    SUDOKU_DFS sudoku_dfs(&db);
    /* 设置只有一个解 */
    //sudoku_dfs.set_onlyone(true);
    /*4，求解器开始工作*/
    
    success = sudoku_dfs.resetSudoku(&mysudoku);
    if(!success)
    {
        cerr<<"[Error]:Failed to solve problem!"<<endl;
        return 0;
    }
    cout<<"----------------------normal test-----------------------"<<endl;
    cout<<"time of creating database :"<<db.get_time()<<"ms"<<endl;
    cout<<"time of match,sort and dfs:"<<sudoku_dfs.get_time()<<"ms"<<endl;
}
