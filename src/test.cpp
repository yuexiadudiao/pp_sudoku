
#include<iostream>
#include<string>


#include"DataBase.hpp"
#include"Sudoku.hpp"
#include"Dfs.hpp"

using namespace std;

/* 测试列表 */
//#define TEST_API_1
//#define TEST_API_2
//#define TEST_API_3

int main(int argc,char** argv)
{

	time_t t1=clock();
	DataBase db;
	time_t t2=clock();

	#ifdef TEST_API_1
	//测试 ismatch_posepoint 函数
	cout<<"testing function ismatch_posepoint()......"<<endl;
	PosePointID ppid1=0,ppid2=888;
	if(db.ismatch_posepoint(ppid1,ppid2))
  	cout<<"PosePointID "<<ppid1<<" and "<<"PosePointID "<<ppid2<<" is match!"<<endl;
	else
		cout<<"PosePointID "<<ppid1<<" and "<<"PosePointID "<<ppid2<<" is not match!"<<endl;
	#endif

	#ifdef TEST_API_2
	//测试 ismatch_stack 函数
	cout<<"testing function ismatch_stack()......"<<endl;
	vector<PosePointID> ppidstatck;
	PosePointID q_ppid=0;
	ppidstatck.push_back(1);
	ppidstatck.push_back(2);
	ppidstatck.push_back(3);
	cout<<"PosePointID "<<q_ppid<<" vs:"<<endl;
	for(int i=0;i<ppidstatck.size();i++)
		cout<<ppidstatck[i]<<endl;
	if(db.ismatch_stack(q_ppid,ppidstatck))
		cout<<"match stack!"<<endl;
	else
		cout<<"not match stack!"<<endl;
	#endif

	#ifdef TEST_API_3
	//测试	search 函数
	cout<<"testing function search()......"<<endl;
	vector<PosePointID> numlist;
  PosePoint a(string("000000000000000000100000000000001000010000000000000000000000100000000000000100000"));
	cout<<"now searching temple "<<a<<endl;
  db.search(a,numlist);
	cout<<"there are "<<numlist.size()<<" matched PosePoint:"<<endl;
	for(int i=0;i<numlist.size();i++)
	cout<<numlist[i]<<endl;
	#endif


	if(argc!=2)
	{
			cerr<<"[Error]:please input sudoku!"<<endl;
			exit(1);
	}
	string str(argv[1]);
	Sudoku mysudoku(str);
	
	mysudoku.showArry();	

	time_t b = clock();
	SUDOKU_DFS sudoku_dfs(&db);
	sudoku_dfs.resetSudoku(&mysudoku);
	time_t e = clock();

	cout<<"---------------------------------------------"<<endl;
	cout<<"time of creating database:"<<(double)(t2 - t1)/CLOCKS_PER_SEC*1000<<"ms"<<endl;
	cout<<"time of sort and dfs:"<<(double)(e - b)/CLOCKS_PER_SEC*1000<<"ms"<<endl;
	cout<<"---------------------------------------------"<<endl;

	mysudoku.showArry();
}
