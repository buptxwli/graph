#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <queue>
#include <cstdio>
using namespace std;
const int maxnum=100;
const int maxrow=100;
const int maxline=50;
const int maxtime=maxnum*maxrow*maxline;
bool graph_mark[1000];
bool mark_point[maxrow][maxline];
int step_total[maxnum];
int row,line,num;  // whole situation
char in[100][100];   //graph
int graph_pre[1000];
int graph_dis[1000];
int graph_size;
struct P
{
	int x,y;
	bool operator ==(const P &A) const
	{
	    return (x==A.x && y==A.y);
	}
	bool operator !=(const P &A) const
	{
	    return (x!=A.x || y!=A.y);
	}
};
P point[1000]; //graph
P startpoint[maxnum];  //whole situation
P endpoint[maxnum];   //whole situation
P shortest_path[maxnum][maxtime]; //whole situation
struct E    //graph only
{
    int nextx,nexty,cost;
	E(int _nextx=0,int _nexty=0,int _cost=0):nextx(_nextx),nexty(_nexty),cost(_cost){}
};
vector <E> edge[1000];  //graph
struct node  //graph only
{
	int name,tmpdis;
	int turn;
	node(int _name=0,int _tmpdis=0,int _turn=0):name(_name),tmpdis(_tmpdis),turn(_turn){}
	bool operator <(const node &r)const
	{
        if(tmpdis!=r.tmpdis)
            return tmpdis>r.tmpdis;
        else
            return turn>r.turn;
	}
};
priority_queue<node>que; //graph
void graph_input()
{
    graph_size=0;
	for(int i=0;i<row;i++)
	{
		getchar();
		for(int j=0;j<line;j++)
		{
			scanf("%c",&in[i][j]);
			point[graph_size].x=i;
			point[graph_size].y=j;
			graph_size++;
		}
	}
	return;
}
void graph_build()
{
    for(int i=0;i<graph_size;i++)
		edge[i].clear();
    for(int i=0;i<graph_size;i++)
    {
        if(point[i].x==0)      //first line only down
        {
            edge[i].push_back(E(point[i].x+1,point[i].y,1));
        }
        if(point[i].x==row-1)  //last line only up
        {
            edge[i].push_back(E(point[i].x-1,point[i].y,1));
        }
        if (in[point[i].x][point[i].y]=='>')  //turn left
        {
            edge[i].push_back(E(point[i].x,point[i].y+1,1));
        }
        if(in[point[i].x][point[i].y]=='<')   //turn right
        {
            edge[i].push_back(E(point[i].x,point[i].y-1,1));
        }
        if(point[i].x==1)
        {
            edge[i].push_back(E(point[i].x-1,point[i].y,1));
        }
        if(point[i].x==row-2)
        {
            edge[i].push_back(E(point[i].x+1,point[i].y,1));
        }
        if(in[point[i].x][point[i].y]=='X')
        {
            if(point[i].x!=line-1 && in[point[i].x][point[i].y+1]=='>')
            {
                edge[i].push_back(E(point[i].x,point[i].y+1,1));
            }
            if(point[i].x!=0 && in[point[i].x][point[i].y-1]=='<')
            {
                edge[i].push_back(E(point[i].x,point[i].y-1,1));
            }
            if(in[point[i].x+1][point[i].y]=='X')
            {
                edge[i].push_back(E(point[i].x+1,point[i].y,1));
            }
            if (in[point[i].x-1][point[i].y]=='X')
            {
                edge[i].push_back(E(point[i].x-1,point[i].y,1));
            }
        }
        if(in[point[i].x][point[i].y]=='Y')
        {
            if(point[i].x!=line-1 && in[point[i].x][point[i].y+1]=='>')
            {
                edge[i].push_back(E(point[i].x,point[i].y+1,1));
            }
            if(point[i].x!=0 && in[point[i].x][point[i].y-1]=='<')
            {
                edge[i].push_back(E(point[i].x,point[i].y-1,1));
            }
            if(in[point[i].x+1][point[i].y]=='Y')
            {
                edge[i].push_back(E(point[i].x+1,point[i].y,1));
            }
            if (in[point[i].x-1][point[i].y]=='Y')
            {
                edge[i].push_back(E(point[i].x-1,point[i].y,1));
            }
        }
    }
}
void graph_inital()
{
    memset(graph_mark,false,sizeof(graph_mark));
    memset(graph_pre,-1,sizeof(graph_pre));
    for(int i=0;i<graph_size;i++) graph_dis[i]=123456789;
    while(!que.empty()) que.pop();
}
void find_shortest(int i)
{
    graph_dis[startpoint[i].x*line+startpoint[i].y]=0;
    que.push(node(startpoint[i].x*line+startpoint[i].y,0,0));
    node tmp;
    while(!que.empty())
    {
        tmp=que.top();
        que.pop();
        int u=tmp.name;
        if(graph_mark[u]) continue;
        graph_mark[u]=true;
        for(int j=0;j<edge[u].size();j++)
        {
            int m=edge[u][j].nextx;
            int n=edge[u][j].nexty;
            int c=edge[u][j].cost;
            if(!graph_mark[m*line+n]&&graph_dis[m*line+n]>graph_dis[u]+c)
            {
                graph_dis[m*line+n]=graph_dis[u]+c;
                graph_pre[m*line+n]=u;
                que.push(node(m*line+n,graph_dis[m*line+n]));
            }
        }
    }
    if(graph_dis[endpoint[i].x*line+endpoint[i].y]==123456789)
        step_total[i]=-1;
    else
    {
        step_total[i]=graph_dis[endpoint[i].x*line+endpoint[i].y]+1;
        int tmppre=graph_pre[endpoint[i].x*line+endpoint[i].y];
        shortest_path[i][step_total[i]-1]=endpoint[i];
        int j=1;
        while(tmppre>=0)
        {
            int prex=tmppre/line;
            int prey=tmppre%line;
            shortest_path[i][step_total[i]-1-j].x=prex;
            shortest_path[i][step_total[i]-1-j].y=prey;
            tmppre=graph_pre[tmppre];
            j++;
        }
    }
    return;
}
void debug_graph(int x)
{
    if(step_total[x]==-1)
    {
        printf("can't arrive");
        return;
    }
    printf("step=%d:\n",step_total[x]-1);
    for(int i=0;i<step_total[x]-1;i++)
    {
        printf("(%d,%d)->",shortest_path[x][i].x,shortest_path[x][i].y);
    }
    printf("(%d,%d)\n",shortest_path[x][step_total[x]-1].x,shortest_path[x][step_total[x]-1].y);
    return;
}
void debug(int x)
{
    char tmp[maxrow][maxline];
    for(int i=0;i<row;i++)
    {
        for(int j=0;j<line;j++)
            tmp[i][j]=in[i][j];
    }
    for(int i=0;i<=step_total[x]-1;i++)
        tmp[shortest_path[x][i].x][shortest_path[x][i].y]='0'+x;
    for(int i=0;i<row;i++)
    {
        for(int j=0;j<line;j++)
            printf("%c",tmp[i][j]);
        printf("\n");
    }
    return ;
}
int main()
{
    freopen("input.txt","r",stdin);
    while (scanf("%d%d",&row,&line)!=EOF)
    {
        graph_input();
        graph_build();
        scanf("%d",&num);
        for(int i=0;i<num;i++)
        {
            graph_inital();
            scanf("%d%d%d%d",&startpoint[i].x,&startpoint[i].y,&endpoint[i].x,&endpoint[i].y);
            printf("car[%d]\n",i);
            find_shortest(i);
            debug_graph(i);
            debug(i);
        }
    }
    return 0;
}
