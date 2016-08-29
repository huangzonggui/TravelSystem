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
//void Floyd(int A[M][M],int path[M],[M]);//Floyd算法
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

void guide_line()
{

}

void check_circuit()
{

}

void min_distance()//最短路径、距离
{

}

void build_road()
{

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
