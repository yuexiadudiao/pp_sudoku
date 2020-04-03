/**测试单独的一个数独的循环求解
*
*显示求解的平均时间
*/

//#define PRINT_ANS //显示开关
#define TEST_LOOP 300

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

    string str(argv[1]);

    int loop = TEST_LOOP;
    double db_avg = 0;
    double sudoku_avg = 0;
    while(loop--)
    {
        DataBase db;
        Sudoku mysudoku(str);
        SUDOKU_DFS sudoku_dfs(&db);
        sudoku_dfs.resetSudoku(&mysudoku);

        db_avg+= db.get_time();
        sudoku_avg+= sudoku_dfs.get_time();
    }

    cout<<"----------------------database test("<<TEST_LOOP<<" loops)-----------------------"<<endl;
    cout<<"avg_time of creating database :"<<db_avg/TEST_LOOP<<"ms"<<endl;

    cout<<"-----------------------sudoku test("<<TEST_LOOP<<" loops)------------------------"<<endl;
    cout<<"avg_time of match,sort and dfs:"<<sudoku_avg/TEST_LOOP<<"ms"<<endl;
}
