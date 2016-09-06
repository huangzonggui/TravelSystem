#include <iostream>
#include <fstream>

using namespace std;

#include <conio.h>
#include <cstdlib>//清屏函数头文件

#define M 100
#define INF 999666333

//函数声明
void returnMainFace();//返回主界面
void create_graph();//创建景区景点图
void print_graph();//输出景区景点图
void guide_line();//导游线路
void DFS(int c);//深度优先搜索导游线路
void checked();//检查是否存在一个合法的景区景点分布图
void Num_Name();//打印景点编号与景点名称的对应信息
void Floyd(int A[M][M],int path[M][M]);//Floyd算法
void Y_N();//选择判断函数
void check_circuit();//判断是否有重复经过的景点
void min_distance();
void build_road();
void write_file();
void read_file();
void add_scenic();

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
    system("color e4");
    cout<<"\n\n\t\t******欢迎使用景区旅游信息管理系统******\n\n";
    cout<<"\n主菜单:\n";
    cout<<"\t1、创建景区景点分布图；\n";
    cout<<"\t2、景区景点分布图（邻接矩阵）；\n";
    cout<<"\t3、输出导游线路图；\n";
    cout<<"\t4、判断导游线路图有无回路；\n";
    cout<<"\t5、求两个景点间的最短路径和最短距离；\n";
    cout<<"\t6、输出道路修建规划图；\n";
    cout<<"\t7、将景区景点分布图保存；\n";
    cout<<"\t8、读取指定文件名的景区景点分布图；\n";
    cout<<"\t9、为当前的景区添加景点道路；\n";
    cout<<"\t0、退出。\n";
    cout<<"\n*请输入操作选择:";
    char c;
    c=getch();/*从键盘上自动读取一个字符，不回显送给字符变量c*/
    cout<<c<<endl;
    while(!(c>='0'&&c<='9')){
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
    case '7':
        write_file();
        break;
    case '8':
        read_file();
        break;
    case '9':
        add_scenic();
        break;
    case '0':
        cout<<"\n\t\t\t*按任意键关闭本系统\n";
        exit(0);
    }
    return 0;
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


//判断的对象是导游线路，判断是否有重复走过的景点)
void check_circuit()
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

//Floyd（佛洛依德）算法，A[M][M]表示最短距离，path[M][M]表示辅助数组，记住前驱
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
                path[i][j]=i;
            }else{
                //（i==j&&S.mat.m[i][j]=INF
                path[i][j]=-1;
            }
        }
    }
        for(k=0;k<S.count;k++){//k 注意放到最外层，让A[i][j]检测都经过每一个k
            for(i=0;i<S.count;i++){
                for(j=0;j<S.count;j++){
                    if(A[i][j]>A[i][k]+A[k][j]){//如果i->j的权值大于i->k->j的权值
                        A[i][j]=A[i][k]+A[k][j];
                        path[i][j]=path[k][j];//path[k][j]=k前驱?k是指向的下一个景点
                    }
                }
            }
        }
}

void min_distance()//最短路径、距离
{
    checked();
    int A[M][M],path[M][M];
    Floyd(A,path);//A是一个景点到另一个景点的最短路径的长度
    while(true){
        Num_Name();//编号对应的景点名称
        int i,j,k,s;
        int apath[M],d;//apath[M]是记录路径的数组
        bool flag=true;
        while(flag){
            cout<<"\t-景点1：";
            cin>>i;
            i--;
            if(i<0||i>S.count-1){
                cout<<"*请输入合法的景点编号:\n";
            }else{
                flag=false;
            }
        }
        flag=true;
        while(flag){
            cout<<"\t-景点2：";
            cin>>j;
            j--;
            if(j<0||j>S.count-1){
                cout<<"*请输入合法的景点编号:\n";
            }else{
                flag=false;
            }
        }
        if(A[i][j]<INF&&i!=j){
            k=path[i][j];//k是指向的下一个景点
            d=0;//路径有d+2个景点,是数组apath的下标
            //将待输出的路径的点存放在栈apath中
            apath[d]=j;//最后一个景点
            while(k!=-1&&k!=i){
                d++;
                apath[d]=k;
                //再继续判断还有没有景点
                k=path[i][k];
            }
            d++;
            apath[d]=i;//加上第一点
            cout<<"\n*从 "<<S.mat.Pname[i]<<" 到 "<<S.mat.Pname[j]<<"  最短路径为：";
            cout<<S.mat.Pname[apath[d]];//apath[M]数组最后一个，就是第一个起点,相当于栈
            for(s=d-1;s>=0;s--){//将剩下的景点（apath[M]数组剩下的元素）打印出来
                cout<<" -->"<<S.mat.Pname[apath[s]];
            }
            cout<<" ，最短距离为："<<A[i][j]<<endl;//Floyd算法已经将最短路径算出来存放到了A[i][j](将INF的值用最短路径代替了)
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

//道路修建规划图、最小生成树(prime算法)
void build_road()
{
    checked();
    cout<<"\n*道路修建规划图（prime算法）规划如下：\n";
    //Ai[M]表示待选边的权值,邻接矩阵的一行,closest[M]：点编号数组，记录下一条路的起点景点的编号
    int Ai[M],min,closest[M],i,j,k,sum=0,num=0;//num表示第几条路
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
        Ai[i]=A[0][i];//取第一行存四个Ai[i]，就是一个景点到所有景点的权值
        closest[i]=0;//0
    }
    for(i=1;i<S.count;i++){
        min=INF;
        //从Ai[j]中选出最小的值存放在min
        for(j=0;j<S.count;j++){
            if(Ai[j]!=0&&Ai[j]<min){
                min=Ai[j];
                k=j;//记录最小的值的列j:k=j，为了下面标志此路已选
            }
        }
        if(min<INF){
            cout<<"\t-第 "<<++num<<" 条路： 从 "<<S.mat.Pname[closest[k]]<<" 到"<<S.mat.Pname[k]<<" , 该道路长度为： "<<min<<endl;
            sum+=min;//sum累计道路长度，即是已选的权值
        }
        Ai[k]=0;//标志为已选的边的权值，避免重复选择
        //例子：对比a到c和b到c的权值，取最小存进Ai[j]中
        for(j=0;j<S.count;j++){
            if(A[k][j]!=0&&A[k][j]<Ai[j]){
                Ai[j]=A[k][j];
                closest[j]=k;//点编号数组，记录下一条路的起点景点的编号
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
        cout<<"\n*缺少合法的景区景点分d布图！\n*请先创建一个合法的景区景点分布图！\n";
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
    system("cls");//调用dos命令
    main();
}

//将景区保存到文件
void write_file(){
    checked();
    string outfilename;
    ofstream outfile;//建立ofstream对象
    cout<<"将景区景点保存为文件的文件名：";
    cin>>outfilename;
    //建立对象与文件之间的联接
    string s="file/"+outfilename;
    const char* path=s.c_str();
    outfile.open(path,ios::trunc);//c_str()函数返回一个指向正规C字符串的指针, 内容与本string串相同  ios::trunc:如果文件已存在则先删除该文件
    if(outfile.is_open()){
        outfile<<S.Sname<<endl;//将景区的名称输出
        outfile<<S.count<<endl;
        outfile<<S.edge<<endl;
        for(int i=0;i<S.count;i++){
            outfile<<S.mat.Pname[i]<<endl;//将景区景点的名称输出
        }
        for(int i=0;i<S.count;i++){
            for(int j=0;j<S.count;j++){
                outfile<<S.mat.m[i][j]<<endl;//将邻接矩阵的每个元素输出
            }
        }
        //关闭对象与文件之间的联接
        outfile.close();
    }else{
        cout<<"不能打开文件!"<<endl;
    }
    returnMainFace();
}

//读取指定文件名的景区景点
void read_file(){
    ifstream infile;
    string s,filename;
    bool flag=true;

    while(flag){//判断是否存在此文件
        cout<<"请输入文件名：";
        cin>>filename;
        s="file/"+filename;
        const char* path=s.c_str();
        infile.open(path,ios::in);
        if(!infile){
            cout<<"打开失败，没有此文件"<<endl;
        }else{
            flag=false;
        }
    }

    infile>>S.Sname;
    infile>>S.count;
    infile>>S.edge;
    for(int i=0;i<S.count;i++){
          infile>>S.mat.Pname[i];
    }
    for(int i=0;i<S.count;i++){
        for(int j=0;j<S.count;j++){
            infile>>S.mat.m[i][j];
        }
    }
    infile.close();
    print_graph();
}

//给当前景区添加景点
void add_scenic(){
    checked();
    int a,b;
    cout<<"\n*请输入要在该景区中添加景点总数目：";
    cin>>a;
    S.count=S.count+a;
    cout<<"\n*请输入要在该景区中添加道路总数目：";
    cin>>b;
    S.edge=S.edge+b;
    cout<<"\n*请添加道路、景点编号、名称及道路的长度\n";
    cout<<"\t (格式：景点输入请按照小号在前大号在后的原则，景点编号从1开始)";
    for(int i=S.edge-b;i<S.edge;i++){
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
    cout<<"\n*景区添加景点成功！";
    returnMainFace();
}
