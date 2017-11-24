
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

int main()
{

	DataBase db;

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

	Sudoku s1("000060000020000000090000000010006025400000910000000004000640000000000800501000002");
	Sudoku s2("600000302059030070730084000915203000406091503328547961183476259000308600204910807");//简单数独
	Sudoku s3("005300000800000020070010500400005300010070006003200080060500009004000030000009700");//世界最难数独


	SUDOKU_DFS sudoku_dfs(&db,&s1);

}
