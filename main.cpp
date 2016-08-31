#include <iostream>

using namespace std;

#include <conio.h>
#include <cstdlib>//清屏函数头文件

#define M 100
#define INF 999666333

//函数声明
void Welcome();//欢迎界面
void returnMainFace();//返回主界面
void MainFace();//主界面
void create_graph();//创建景区景点图
void print_graph();//输出景区景点图
void guide_line();//导游线路
void DFS(int c);//深度优先搜索导游线路
void checked();//检查是否存在一个合法的景区景点分布图
void Num_Name();//打印景点编号与景点名称的对应信息
void Floyd(int A[M][M],int path[M][M]);//Floyd算法
void Y_N();//选择判断函数
void check_circuit();//判断回路
void min_distance();
void build_road();

//定义数据结构
struct Matrix
{
    int m[M][M];//景点邻接矩阵
    string Pname[M];//各个景点的名称
};

typedef struct
{
    string Sname;//景区名称
    int count;//景区总数量
    int edge;//道路数量
    Matrix mat;//邻接矩阵
}Scenic;
//景区数据类型为全局变量
Scenic S;

int main()
{
    system("color f4");
    Welcome();
    return 0;
}


void Welcome(){
    cout<<"\n\n\t\t******欢迎使用景区旅游信息管理系统******\n\n";
    cout<<"\t\t\t按任意键进入系统......";
    getch();
    MainFace();
}

void MainFace()//主界面
{
    system("cls");
    cout<<"\n主菜单:\n";
    cout<<"\t1、创建景区景点分布图；\n";
    cout<<"\t2、输出景区景点分布图（邻接矩阵）；\n";
    cout<<"\t3、输出导游线路图；\n";
    cout<<"\t4、判断导游线路图有无回路；\n";
    cout<<"\t5、求两个景点间的最短路径和最短距离；\n";
    cout<<"\t6、输出道路修建规划图；\n";
    cout<<"\t0、退出。\n";
    cout<<"\n*请输入操作选择；";
    char c;
    c=getch();/*从键盘上读入一个字符不回显送给字符变量c*/
    cout<<c<<endl;
    while(!c>='0'&&c<='6'){
        cout<<"*输入有误，请重新输入：";
        c=getch();
        cout<<c<<endl;
    }
    switch(c){
    case '1':
        create_graph();//创建景区景点分布图
        break;
    case '2':
        print_graph();//输出景区景点分布图（邻接矩阵）
        break;
    case '3':
        guide_line();//导游线路
        break;
    case '4':
        check_circuit();//判断回路
        break;
    case '5':
        min_distance();//最短距离
        break;
    case '6':
        build_road();//最小生成树
        break;
    case '0':
        cout<<"\n\t\t\t*按任意键关闭本系统\n";
        exit(0);
    }
}

//创建一个景区的邻接矩阵
void create_graph()//case1
{
    if(S.count>0)
    {
        cout<<"\n*当前已存在一个景区景点分布图！\n*继续操作将覆盖该景区景点分布图!(Y/N）";
        Y_N();
    }
    cout<<"\n*请输入景区的名称：";
    cin>>S.Sname;
    cout<<"\n*请输入该景区的景点总数目：";
    cin>>S.count;
    cout<<"\n*请输入景区的道路总数目：";
    cin>>S.edge;
    int i,j;
    //mat是Matrix的邻接矩阵
    for(i=0;i<S.count;i++){
        for(j=0;j<S.count;j++){
            //全部初始化为0
            S.mat.m[i][j]=0;
        }
    }
    cout<<"\n*请输入道路两边连接的两个景点编号、名称及道路的长度\n";
    cout<<"\t (格式：景点输入请按照小号在前大号在后的原则，景点编号从1开始)";
    for(i=0;i<S.edge;i++){
        cout<<"\n*第"<<i+1<<"条道路\n";
        int n1,n2;
        //编号输入从1开始，矩阵下标从零开始,所以要自减一
        cout<<"\t-道路起点景点编号：";
        cin>>n1;
        n1--;
        cout<<"\t-道路起点景点名称：";
        cin>>S.mat.Pname[n1];

        cout<<"\t-道路终点景点编号：";
        cin>>n2;
        n2--;
        cout<<"\t-道路终点景点名称：";
        cin>>S.mat.Pname[n2];

        cout<<"\t-两个景点之间的道路长度：";
        cin>>S.mat.m[n1][n2];
        S.mat.m[n2][n1]=S.mat.m[n1][n2];
    }
    cout<<"\n*景区创建成功！";
    returnMainFace();
}

void print_graph()//以邻接矩阵的形式输出景点分布
{
    checked();
    cout<<"\n*景区景点分布图（邻接矩阵表示）查询成功！\n";
    cout<<"*景区名称："<<S.Sname<<endl;
    int i,j;
    cout<<"\n\t-------";
    for(i=0;i<S.count;i++){
        cout<<"---";
    }
    cout<<endl;
    cout<<"\t|编号|";
    //cout<<"   |";
    for(i=0;i<S.count;i++){
        cout<<' '<<i+1<<' ';
    }
    cout<<'|'<<endl<<"\t|-----";
    for(i=0;i<S.count;i++){
        cout<<"---";
    }
    cout<<'|'<<endl;
    for(i=0;i<S.count;i++){
        for(j=0;j<S.count;j++){
            if(j==0){
                cout<<"\t| "<<i+1<<"  | "<<S.mat.m[i][j]<<' ';
            }else{
                cout<<' '<<S.mat.m[i][j]<<' ';
            }
        }
        cout<<'|'<<endl;
    }
    cout<<"\t-------";
    for(i=0;i<S.count;i++){
        cout<<"---";
    }
    Num_Name();
    cout<<"注：\n\t'0'表示两个景点间没有直接达到的路径，或景点到自身路径不需要！\n";
    returnMainFace();
}

//----------------
//深度优先搜索导游线路
int visited[M]={0};
int np=0;//找到的景点个数
int p[M];//表示各个景点的入度值
void DFS(int c){
    //c为景点编号
    np++;//每递归调用一次就自加一次，作为判断是否到了最后一个景点
    p[c]++;
    if(np==S.count){
        //到了最后一个景点
        cout<<S.mat.Pname[c]<<endl;
        returnMainFace();
    }else{
        cout<<S.mat.Pname[c]<<"-->";
    }
    visited[c]=1;
    for(int i=0;i<S.count;i++){
        if(S.mat.m[c][i]>0&&visited[i]==0){
            DFS(i);
            if(S.count>np){
                cout<<S.mat.Pname[c]<<"-->";
                p[c]++;
            }
        }
    }
    if(np==S.count)
        returnMainFace();
}

void guide_line()//导游线路
{
    checked();
    cout<<"\n*请输入起始景点的景点编号：";
    int c;
    cin>>c;
    c--;
    for(int i=0;i<S.count;i++){
        visited[i]=0;
        p[i]=0;//入度置初值为0
    }
    np=0;
    cout<<"*形成的导游线路图（采取深度优先策略）如下所示：\n\n\t";
    DFS(c);
}



void check_circuit()//判断的对象是导游线路，判断是否有重复走过的景点)
{
    checked();
    if(np==0){
        cout<<"\n*缺少合法的导游线路图！\n*请先创建一个合法的导游线路图！\n";
        returnMainFace();
    }
    bool f=true;//true表示没有回路
    for(int i=0;i<S.count;i++){
        //p[i]表示景点入度值
        if(p[i]>1){
                if(f){
                    cout<<"\n*该导游线路图存在回路\n线路中的重复走过的景点显示如下：\n\t";
                    f=false;
                }
                cout<<"编号："<<i+1<<","<<"景点名称："<<S.mat.Pname[i]<<"\n\t"<<endl;
        }
    }
    if(f){
        cout<<"\n\t*未找到存在于该导游线路图中的回路。\n";
    }
    returnMainFace();
}

//Floyd（佛洛依德）算法，A[M][M]表示权值(最短距离)，path[M][M]表示辅助数组，记住最短路径
void Floyd(int A[M][M],int path[M][M]){
    int i,j,k;
    for(i=0;i<S.count;i++){
        for(j=0;j<S.count;j++){
            if(S.mat.m[i][j]==0&&i!=j){
                //如果两点之间没有边相连，则权为无穷大
                A[i][j]=INF;//INF=999666333
            }else if(i==j){
                A[i][j]=0;
            }else{
                //S.mat.m[i][j]表示两个景点之间的道路长度
                A[i][j]=S.mat.m[i][j];
            }
            //给所有的path[i][j]赋值
            if(i!=j&&S.mat.m[i][j]<INF){
                path[i][j]=i;//?先初始化Path
            }else{
                //（i==j&&S.mat.m[i][j]=INF）
                path[i][j]=-1;
            }
        }
    }
//        for(i=0;i<S.count;i++){
//            for(j=0;j<S>count;j++){
//                cout<<path[i][j]<<'';
//            }
//            cout<<endl;
//        }
        for(k=0;k<S.count;k++){
            for(i=0;i<S.count;i++){
                for(j=0;j<S.count;j++){
                    if(A[i][j]>A[i][k]+A[k][j]){//如果i->j的权值大于i->k->j的权值
                        A[i][j]=A[i][k]+A[k][j];
                        path[i][j]=path[k][j];
                    }
                }
            }
        }
}

void min_distance()//最短路径、距离
{
    checked();
    int A[M][M],path[M][M];
    Floyd(A,path);
    while(true){
        //system("cls");
        Num_Name();//编号对应的景点名称
        int i,j,k,s;
        int apath[M],d;
        cout<<"*请输入要查询的最短路径和最短距离的两个景点的编号:\n";
        cout<<"\t-景点1：";
        cin>>i;
        i--;
        cout<<"\t-景点2：";
        cin>>j;
        j--;
        if(A[i][j]<INF&&i!=j){
            k=path[i][j];//取值
            d=0;
            apath[d]=j;
            while(k!=-1&&k!=i){
                d++;
                apath[d]=k;
                k=path[i][k];
            }
            d++;
            apath[d]=i;
            cout<<"\n*从 "<<S.mat.Pname[i]<<" 到 "<<S.mat.Pname[j]<<"  最短路径为：";
            cout<<S.mat.Pname[apath[d]];
            for(s=d-1;s>=0;s--){
                cout<<" -->"<<S.mat.Pname[apath[s]];
                //cout<<',apath[s]='<<apath[s];
            }
            cout<<" ，最短距离为："<<A[i][j]<<endl;
        }else if(i==j){
            cout<<"\n*景点输入不合法，输入的两个景点不能相同!\n";
        }else{
            cout<<"\n*这两个景点间不存在路径\n";
        }
        cout<<"\n是否继续执行最短路径和最短距离的查询（Y/N）";
        Y_N();
    }
    returnMainFace();
}

void build_road()//道路修建规划图、最小生成树(prime算法)
{
    checked();
    cout<<"\n*道路修建规划图（prime算法）规划如下：\n";
    int lowcost[M],min,closest[M],i,j,k,v=0,sum=0,num=0;
    int A[M][M];
    //赋权值
    for(i=0;i<S.count;i++){
        for(j=0;j<S.count;j++){
            if(S.mat.m[i][j]==0&&i!=j){
                A[i][j]=INF;
            }else if(i==j){
                A[i][j]=0;
            }else{
                A[i][j]=S.mat.m[i][j];
            }
        }
    }
    for(i=0;i<S.count;i++){
        lowcost[i]=A[v][i];
        closest[i]=v;
    }
    for(i=1;i<S.count;i++){
        min=INF;
        for(j=0;j<S.count;j++){
            if(lowcost[j]!=0&&lowcost[j]<min){
                min=lowcost[j];
                k=j;
            }
        }
        if(min<INF){
            cout<<"\t-第 "<<++num<<" 条路： 从 "<<S.mat.Pname[closest[k]]<<" 到"<<S.mat.Pname[k]<<" , 该道路长度为： "<<min<<endl;
            sum+=min;
        }
        lowcost[k]=0;
        for(j=0;j<S.count;j++){
            if(A[k][j]!=0&&A[k][j]<lowcost[j]){
                lowcost[j]=A[k][j];
                closest[j]=k;
            }
        }
    }
    cout<<"*修建道路的总长度为："<<sum<<endl;
    returnMainFace();
}


void Y_N()
{
    char ch;
    while(ch=getch())
    {
        if(ch=='Y'||ch=='y')
        {
            cout<<ch<<endl;
            break;
        }
        if(ch=='N'||ch=='n')
        {
            cout<<ch<<endl;
            returnMainFace();
        }
    }

}

void checked(){
    system("cls");
    if(S.count<=1){
        cout<<"\n*缺少合法的景区景点分布图！\n*请先创建一个合法的景区景点分布图！\n";
        returnMainFace();
    }
}

void Num_Name(){
    cout<<"\n*编号对应的景点名称：\n";
    for(int i=0;i<S.count;i++){
        cout<<"\t"<<i+1<<": "<<S.mat.Pname[i]<<endl;
    }
}

void returnMainFace(){
    cout<<"\n\t\t\t*按任意键返回主菜单......\n";
    getch();
    system("cls");//调用系统命令
    MainFace();
}
