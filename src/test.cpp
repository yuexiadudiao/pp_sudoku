
#include<iostream>
#include<string>


#include"DataBase.hpp"

using namespace std;

#define TEST_API_2

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
  PosePoint a(string("100000000000000000000000000000000000000000000000000000000000000000000000000000000"));
	cout<<"now searching temple "<<a<<endl;
  db.search(a,numlist);
	cout<<"there are "<<numlist.size()<<" matched PosePoint:"<<endl;
	for(int i=0;i<numlist.size();i++)
	cout<<numlist[i]<<endl;
	#endif
}
