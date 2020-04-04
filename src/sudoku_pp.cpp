//#define PRINT_ANS //显示开关

#include<fstream>
#include<ctime>

#include"Dfs.hpp"

using namespace std;

int main(int argc,char** argv)
{
    if(argc!=2)
    {
        cerr<<"[Error]：please input test sudoku file path!"<<endl;
        exit(1);
    }

    DataBase db("./posepoint.txt");

    SUDOKU_DFS sudoku_dfs(&db);

    ifstream batsudoku(argv[1]);
    ofstream timelog("pp_timelog.txt");

    time_t t1,t2;

    int count=0;
    bool success = false;
    timelog<<"pp_time"<<endl;
    while (!batsudoku.eof())
    {
        cout<<"pp_sudoku case "<<++count<<endl;
        string str;
        batsudoku>>str;

        Sudoku sudoku(str);

        t1 = clock();
        success = sudoku_dfs.resetSudoku(&sudoku);
        if(!success)
        {
            cerr<<"[Error]:Failed to solve problem!"<<endl;
            goto out;
        }
        t2 = clock();
        timelog<<(double)(t2 - t1)/CLOCKS_PER_SEC*1000<<endl;
    }

out:
    batsudoku.close();
    timelog.close();
}
