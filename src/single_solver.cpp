/**测试单独的一个数独的求解
*
*1,打印题目与求解结果
*2,显示求解的平均时间
*/
#include<iostream>
#include<string>


#include"DataBase.hpp"
#include"Sudoku.hpp"
#include"Dfs.hpp"

using namespace std;

#define TEST_LOOP 300

int main(int argc,char** argv)
{

	
	DataBase db;
	

	if(argc!=2)
	{
			cerr<<"[Error]:please input sudoku!"<<endl;
			exit(1);
	}
	string str(argv[1]);
	Sudoku mysudoku(str);
	
	cout<<"-----------Before solver-----------"<<endl;
	mysudoku.showArry();

	
	SUDOKU_DFS sudoku_dfs(&db);
	sudoku_dfs.resetSudoku(&mysudoku);	
	
	cout<<"-----------After  solver-----------"<<endl;
	mysudoku.showArry();

	cout<<"----------------------normal test-----------------------"<<endl;
	cout<<"time of creating database  :"<<db.get_time()<<"ms"<<endl;
	cout<<"time of search,sort and dfs:"<<sudoku_dfs.get_time()<<"ms"<<endl;

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
	cout<<"avg_time of creating database  :"<<db_avg/TEST_LOOP<<"ms"<<endl;

	cout<<"-----------------------sudoku test("<<TEST_LOOP<<" loops)------------------------"<<endl;
	cout<<"avg_time of search,sort and dfs:"<<sudoku_avg/TEST_LOOP<<"ms"<<endl;
}
