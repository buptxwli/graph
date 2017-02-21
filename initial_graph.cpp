#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <queue>
#include <cstdio>
using namespace std;
struct P
{
    int x,y;
};
P point[1000];
struct E
{
    int nextx,nexty,cost;
	E(int _nextx=0,int _nexty=0,int _cost=0):nextx(_nextx),nexty(_nexty),cost(_cost){}
};
struct node
{
	int name,tmpdis;
	node(int _name=0,int _tmpdis=0):name(_name),tmpdis(_tmpdis){}
	bool operator <(const node &r)const
	{
		return tmpdis>r.tmpdis;
	}
};
char in[100][100];
vector <E> edge[1000];
int pre[1000];
bool mark[1000];
int dis[1000];
int main()
{
    freopen("input.txt","r",stdin);
	int row,line;
	while (scanf("%d%d",&row,&line)!=EOF)
	{
		int s=0;
		for(int i=0;i<row;i++)
		{
			getchar();
			for(int j=0;j<line;j++)
			{
				scanf("%c",&in[i][j]);
				point[s].x=i;
				point[s].y=j;
				s++;
			}
		}
		for(int i=0;i<s;i++)
			edge[i].clear();
		for(int i=0;i<s;i++)
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
		memset(mark,false,sizeof(mark));    //初始化标记数组
		memset(pre,-1,sizeof(pre));
		for(int i=0;i<s;i++) dis[i]=123456789;  //将不连通的距离无限大
		priority_queue<node>que;          //建立队
		while(!que.empty()) que.pop();    //清空队列
		P start,last;
		scanf("%d%d%d%d",&start.x,&start.y,&last.x,&last.y);
		dis[start.x*line+start.y]=0;
		que.push(node(start.x*line+start.y,0));     //将初始点放入队中
		node tmp;
		while(!que.empty())
		{
			tmp=que.top();
			que.pop();
			int u=tmp.name;
			if(mark[u]) continue;
			mark[u]=true;
			for(int j=0;j<edge[u].size();j++)
			{
				int m=edge[u][j].nextx;
				int n=edge[u][j].nexty;
				int c=edge[u][j].cost;
				if(!mark[m*line+n]&&dis[m*line+n]>dis[u]+c)
				{
					dis[m*line+n]=dis[u]+c;
					pre[m*line+n]=u;
					que.push(node(m*line+n,dis[m*line+n]));
				}
			}
		}
		if(dis[last.x*line+last.y]==123456789)
            printf("-1\n");
        else
        {
            printf("%d:(%d,%d)",dis[last.x*line+last.y],last.x,last.y);
            int tmppre=pre[last.x*line+last.y];
            while(tmppre>=0)
            {
                int prex=tmppre/line;
                int prey=tmppre%line;
                printf("<-(%d,%d)",prex,prey);
                tmppre=pre[tmppre];
            }
        }
	}
	return 0;
}
