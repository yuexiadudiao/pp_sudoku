
#include<iostream>
#include<ctime>
#include<memory.h>
#include<cstdio>
using namespace std;

#define PRINT_ANS 0
#define ONLY_ONE 1

#define RR 729                 // 9*9*9  表示rck总数目 r代表行，c代表列 k代表值 比如123 代表一行二列 值是三
#define CC 324                 // 9*9*4  表示 rk，ck，bk，rc 总个数 分别表示四个约束条件，每个数每行只能有一个 每列只能一个 每个九宫格只能一个  每个格子只能有一个数
#define INF 1000000000         // 假定最大值
int mem[RR+9];
int ans[RR+9];                 // 解
char ch[RR+9];                 // 谜题数组  记录题目的  由人输入
int cnt[CC+9];                 // 计数数组
struct node
{
    int r,c;            //位置
    node *up;           // 上下左右四个指针
    node *down;
    node *left;
    node *right;
} head,all[RR*CC+99],row[RR],col[CC]; //头指针， 所有节点，行数组 列数组
int all_t;    //
inline void link(int r,int c)
{
    //将坐标值为 rc 的节点 链接到 第r 行  第 c列
    //
    cnt[c]++;
    node *t=&all[all_t++];
    t->r=r;
    t->c=c;// 构造一个节点，位置rc
    t->left=&row[r];
    t->right=row[r].right;
    t->left->right=t;
    t->right->left=t;// 将t 插入到第r行这个环里
    t->up=&col[c];
    t->down=col[c].down;
    t->up->down=t;
    t->down->up=t; // 将t 插入到第c列 这个环里
}
inline void remove(int c)
{
    // 覆盖第c列
    // 覆盖列c的操作则更加有趣：把c从表头删除并且从其他列链表中去除c链表的所有行。
    //设置 L[R[c]]←L[c] 且 R[L[c]]←R[c]。
    //对于每个i←D[c]，D[D[c]]，……，当 i!=c，
    //对于每个j←R[i]，R[R{i]]，……，当 j!=i，
    //设置 U[D[j]]←U[j]，D[U[j]]←D[j]，
    //并且设置 S[C[j]]←S[C[j]]-1。*/


    node *t,*tt;
    col[c].right->left=col[c].left;
    col[c].left->right=col[c].right; // 将c 从链表col 中删除
    for(t=col[c].down; t!=&col[c]; t=t->down)
    {
        // 从 c列 依次往下走 遍历每个节点t 删掉每个节点t 所在的行
        for(tt=t->right; tt!=t; tt=tt->right)
        {
            //从t 往右走  ，从上下方向删掉每个节点tt
            cnt[tt->c]--; // 该列计数减一
            tt->up->down=tt->down;
            tt->down->up=tt->up; //  将tt从上下方向删掉
        }
        t->left->right=t->right;
        t->right->left=t->left; // 删掉t所在的行后 将t从左右方向删掉
    }
}
inline void resume(int c)
{
    // remove 的逆过程
    node *t,*tt;
    for(t=col[c].down; t!=&col[c]; t=t->down)
    {
        t->right->left=t;
        t->left->right=t;
        for(tt=t->left; tt!=t; tt=tt->left)
        {
            cnt[tt->c]++;
            tt->down->up=tt;
            tt->up->down=tt;
        }
    }
    col[c].left->right=&col[c];
    col[c].right->left=&col[c];
}
int solve(int k)
{
    // 搜索解路径
    // 请仔细阅读 dancing links 的论文
    if(head.right==&head)
        return 1; // 递归终止条件
    node*t,*tt;
    int min=INF,tc;
    for(t=head.right; t!=&head; t=t->right)
    {
        //从头结点开始依次往右走  找到一个 cnt 最小的列 记录为tc
        if(cnt[t->c]<min)
        {
            min=cnt[t->c];
            tc=t->c;
            if(min<=1)break;
        }
    }
    remove(tc); // 覆盖掉列tc   删掉tc列 及tc列中每个节点所在的行
    int scnt=0; // 解计数 初始化为0
    for(t=col[tc].down; t!=&col[tc]; t=t->down)
    {
        mem[k]=t->r; // 将 tc列 中一个节点t 所在的行 记录在 men[k]中 ，到时候 答案从这里计算得到
        t->left->right=t;// 将t 与原左边 的节点又连接上
        for(tt=t->right; tt!=t; tt=tt->right)
        {
            // t往右走，将t 所在行所有节点所在的列覆盖掉
            remove(tt->c);
        }
        t->left->right=t->right;// 将t 与左边的节点又断开
        scnt+=solve(k+1); // 递归调用 solve 寻找下一个节点
        t->right->left=t; // t 与右边节点又链接上
        for(tt=t->left; tt!=t; tt=tt->left)
        {
            //t 往左走，将t所在行所有节点所在列恢复
            resume(tt->c);
        }
        t->right->left=t->left;// t与右边节点又断开
    }
    resume(tc); // 恢复列tc
    return scnt;// 返回 解计数
}

int main(int argc, char** argv)
{
    FILE *fp = NULL;
    FILE *log = NULL;
    int case_id = 0;

    if(argc!=2)
    {
        printf("[Error]：please input test sudoku file path!\n");
        exit(1);
    }

    fp = fopen(argv[1],"r");
    if(NULL == fp)
    {
        printf("failed to open test sudoku file.\n");
        exit(1);
    }

    log = fopen("dlx_timelog.txt","w+");
    if(NULL == log)
    {
        printf("failed to open timelog file.\n");
        exit(1);
    }

    fprintf(log,"%s\n","dlx_time");
    while(fgets(ch,82,fp)!=NULL)
    {
        time_t start,end;
        start=clock();

        cout<<"dlx_sudoku case "<<++case_id<<endl;

#if PRINT_ANS
        puts(ch);
#endif
        // 得到谜题 ch
        int i;//,j,k;
        if(ch[0]=='e')break;
        all_t=1;
        memset(cnt,0,sizeof(cnt)); // 给cnt 初始化 为0
        head.left=&head;
        head.right=&head;
        head.up=&head;
        head.down=&head;
        head.r=RR;
        head.c=CC; // 初始化头结点
        for(i=0; i<CC; i++)
        {
            // 初始化 列数组， 将每个节点与左右节点链接，  上下方向自己指向自己
            col[i].c=i;
            col[i].r=RR;
            col[i].up=&col[i];
            col[i].down=&col[i];
            col[i].left=&head;
            col[i].right=head.right;
            col[i].left->right=&col[i];
            col[i].right->left=&col[i];
        }
        for(i=0; i<RR; i++)
        {
            // 初始化行数组  每个节点 与上下节点 链接  左右方向指向自己
            row[i].r=i;
            row[i].c=CC;
            row[i].left=&row[i];
            row[i].right=&row[i];
            row[i].up=&head;
            row[i].down=head.down;
            row[i].up->down=&row[i];
            row[i].down->up=&row[i];
        }
        for(i=0; i<RR; i++)
        {
            // 根据谜题 构造一个双十字链表。
            int r=i/9/9%9;// 这个r 是在 9*9格中的 行
            int c=i/9%9; //  列
            int val=i%9+1;// 值
            if(ch[r*9+c]=='.'||ch[r*9+c]=='0'||ch[r*9+c]==val+'0')
            {
                //如果Sudoku相应格子处的值 未知， 或者刚好就是符合 就连上相应节点
                link(i,r*9+val-1);  // 连上 i rk 处的节点  rk 范围 0 到80 9*9
                link(i,81+c*9+val-1);//  i 1ck 处的节点    1ck 范围 81到161
                int tr=r/3;
                int tc=c/3; // tr tc 九宫格位置
                link(i,162+(tr*3+tc)*9+val-1); // i 2bk 处的节点  2bk 范围 162到241
                link(i,243+r*9+c);  //  i rc 处的节点
            }
        }
        for(i=0; i<RR; i++)
        {
            //构造完成后 将 row数组 删除
            row[i].left->right=row[i].right;
            row[i].right->left=row[i].left;
        }
        int scnt=solve(1); // 搜索解路径
        for(i=1; i<=81; i++)
        {
            int t=mem[i]/9%81; // 计算t=rc  在九宫格中的位置
            int val=mem[i]%9+1;// rc位置处的值
            ans[t]=val; // 保存在ans数组中
        }

#if PRINT_ANS
        for(i=0; i<81; i++)
            printf("%d",ans[i]); // 将答案打印出来
        printf("\n");
        printf("scnt=%d\n",scnt);  // 打印 解的个数
#endif

        end=clock();
        fprintf(log,"%.3lf\n",(double)(end-start)/CLOCKS_PER_SEC*1000);

        fgets(ch,80,fp);   //取空行
    }

    fclose(fp);
    fclose(log);
    return 0;
}
