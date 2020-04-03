/***************************************************************
程序作者：yin
创建日期：2016-2-26
程序说明：该程序读取同目录下sudoku.txt文件的特定的数独格式，然后
采用回溯法求解，当找到一解后立即返回结束搜索。程序的部分代码参考
自互联网。
修改了程序使之能批量处理数独
时间记录在bftime.txt里
删除readsudoku函数
将bf搜索修改为每个格子从1-9依次尝试
************************************************************** */
#include<stdio.h>
#include<ctime>
#include<stdlib.h>

#define PRINT_ANS 0

#define MAX_LINE 1024

int result=0; //结果数
int sudoku[9][9];
void solver(int sudoku[9][9],int n);
void show_sudoku(int a[9][9])
{
    printf(" -------------------\n");
    for(int i=0; i<9; i++)
    {
        printf(" | ");
        for(int j=0; j<9; j++)
        {
            printf("%d",a[i][j]);
            if(j==2 || j==5 || j==8)printf(" | ");
        }

        printf("\n");
        if(i==2 || i==5 || i==8)printf(" -------------------\n");
    }
}


//判断是否可以将第i行、第j列的数设为k
bool check(int sudoku[9][9],int i,int j,int k)
{
    int m,n;
//判断行
    for(n=0; n<9; n++)
    {
        if(sudoku[i][n] == k)
            return false;
    }
//判断列
    for(m=0; m<9; m++)
    {
        if(sudoku[m][j] == k)
            return false;
    }
//判断所在小九宫格
    int t1=(i/3)*3,t2=(j/3)*3;
    for(m=t1; m<t1+3; m++)
    {
        for(n=t2; n<t2+3; n++)
        {
            if(sudoku[m][n] == k)
                return false;
        }
    }
//可行，返回true
    return true;
}
//数独求解函数
void solver(int sudoku[9][9],int n)
{
    if(result==1) return;
    int temp[9][9];
    int i,j;
    for(i=0; i<9; i++)
        for(j=0; j<9; j++)
            temp[i][j]=sudoku[i][j];

    i=n/9;
    j=n%9; //求出第n个数的行数和列数
	//若可以后移，就后移一个格子，若不能程序结束
    if(sudoku[i][j] != 0)
    {
        if(n == 80)//递归退出点
        {
            result++;
            // printf(" 数独的解为：\a\n");
            //show_sudoku(temp);
        }
        else    solver(temp,n+1);
    }
    else    //空各格子
    {
        for(int k=1; k<=9; k++)
        {
            bool flag=check(temp,i,j,k);
            if(flag) //第i行、第j列可以是k
            {
                temp[i][j]=k; //设为k

                //若可以后移，就后移一个格子，若不能程序结束
                if(n == 80) //递归退出点
                {
                    result++;
                    // printf(" 数独的解为：\a\n");
                    //show_sudoku(temp);
                }
                else        solver(temp,n+1);

                temp[i][j]=0; //回溯擦除这个错误
            }
        }
        //退层点
    }

}

int main(int argc, char** argv)
{
    char buf[MAX_LINE] = "0";  /*缓冲区*/
    FILE *fp = NULL;
    FILE *log = NULL;
    int case_id=0;

	//参数解析
   	if(argc!=2)
    {
		printf("[Error]：please input test sudoku file path!");
        exit(1);
    }

	fp = fopen(argv[1],"r");
	if(NULL == fp)
	{
		printf("failed to open test sudoku file.\n");
		exit(1);
	}

    log = fopen("bf_timelog.txt","w+");
	if(NULL == log)
	{
		printf("failed to open timelog file.\n");
		exit(1);
	}

	fprintf(log,"%s\n","bf_time");
	while(fgets(buf,MAX_LINE,fp) != NULL)
	{
		//解码数独字符串
		int ck=0;
		for(int i=0; i<9; i++)
			for(int j=0; j<9; j++)
				sudoku[i][j]=buf[ck++]-48;
#if  PRINT_ANS		
		//显示数独题目
		show_sudoku(sudoku);
#endif           
		//显示当前处理的用例编号
		case_id++;
		printf("%d\n",case_id);
		
		//计时开始
		time_t start,end;
		start=clock();

		//开始求解
		result=0; 
		solver(sudoku,0);
		if(result==0) 
			printf("此数独无解!\a");

		//计时结束，写入耗时到日志问文件
		end=clock();
		fprintf(log,"%.3lf\n",(double)(end-start)/CLOCKS_PER_SEC*1000);
	}

    fclose(fp);
    fclose(log);
    return 0;
}
