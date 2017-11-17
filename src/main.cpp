
#include<iostream>
#include<string>


#include"DataBase.hpp"

using namespace std;

int main()
{
	
	DataBase db;
	
  cout<<db.ismatch_posepoint(46275,46275)<<endl;
  vector<PosePointID> numlist;
  PosePoint a(string("000000000000000000000000000000000000000000000000000000000000000000000000000000000"));
  db.search(a,numlist);

}
