//#define PRINT_ANS //显示开关
#define JUSTONE //一解开关

#include<fstream>
#include<ctime>

#include"Dfs.hpp"

using namespace std;

int main(int argc,char** argv)
{
    if(argc!=2)
    {
        cerr<<"[Error]：please input bat sudoku file!"<<endl;
        exit(1);
    }

    DataBase db;

    SUDOKU_DFS sudoku_dfs(&db);

    ifstream batsudoku(argv[1]);
    ofstream timelog("time_log.txt");

    time_t t1,t2;

    int count=0;
    timelog<<"time"<<endl;
    while (!batsudoku.eof())
    {
        cout<<++count<<endl;
        string str;
        batsudoku>>str;

        Sudoku sudoku(str);

        t1 = clock();
        sudoku_dfs.resetSudoku(&sudoku);
        t2 = clock();
        timelog<<(double)(t2 - t1)/CLOCKS_PER_SEC*1000<<endl;
    }

    batsudoku.close();
    timelog.close();
}
