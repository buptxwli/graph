#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <queue>
#include <cstdio>
#include <cstdlib>
using namespace std;

const int MAXROW = 20;
const int MAXCOL = 50;
const int MAXPOINT = MAXCOL*MAXROW;
const int MAXEDGE = MAXPOINT*3;
const int INF = 0x3f3f3f3f;

struct P
{
    int x,y;
};
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
class Graph {
private:
    int row, line, s;
    P point[MAXPOINT];
    vector <E> edge[MAXEDGE];
    char *in;
    int pre[MAXPOINT];
    bool mark[MAXPOINT];
    int dis[MAXPOINT];
    void build_graph() {
        s=row*line;
        for(int i=0;i<s;i++)
            edge[i].clear();
        for(int i=0;i<s;i++)
        {
            point[i].x = i/line;
            point[i].y = i%line;
            if(point[i].x==0)      //first line only down
            {
                edge[i].push_back(E(point[i].x+1,point[i].y,1));
            }
            if(point[i].x==row-1)  //last line only up
            {
                edge[i].push_back(E(point[i].x-1,point[i].y,1));
            }
            if (in[point[i].x*line+point[i].y]=='>')  //turn left
            {
                edge[i].push_back(E(point[i].x,point[i].y+1,1));
            }
            if(in[point[i].x*line+point[i].y]=='<')   //turn right
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
            if(in[point[i].x*line+point[i].y]=='X')
            {
                if(point[i].x!=line-1 && in[point[i].x*line+point[i].y+1]=='>')
                {
                    edge[i].push_back(E(point[i].x,point[i].y+1,1));
                }
                if(point[i].x!=0 && in[point[i].x*line+point[i].y-1]=='<')
                {
                    edge[i].push_back(E(point[i].x,point[i].y-1,1));
                }
                if(in[(point[i].x+1)*line+point[i].y]=='X')
                {
                    edge[i].push_back(E(point[i].x+1,point[i].y,1));
                }
                if (in[(point[i].x-1)*line+point[i].y]=='X')
                {
                    edge[i].push_back(E(point[i].x-1,point[i].y,1));
                }
            }
            if(in[point[i].x*line+point[i].y]=='Y')
            {
                if(point[i].x!=line-1 && in[point[i].x*line+point[i].y+1]=='>')
                {
                    edge[i].push_back(E(point[i].x,point[i].y+1,1));
                }
                if(point[i].x!=0 && in[point[i].x*line+(point[i].y-1)]=='<')
                {
                    edge[i].push_back(E(point[i].x,point[i].y-1,1));
                }
                if(in[(point[i].x+1)*line+point[i].y]=='Y')
                {
                    edge[i].push_back(E(point[i].x+1,point[i].y,1));
                }
                if (in[(point[i].x-1)*line+point[i].y]=='Y')
                {
                    edge[i].push_back(E(point[i].x-1,point[i].y,1));
                }
            }
        }
        return;
    }
    void print_path_sub(int start, int p) {
        if (p!=start) {
            print_path_sub( start, pre[p]);
            printf("->(%d,%d)", point[p].x, point[p].y);
        }
        else
            printf("(%d,%d)", point[start].x, point[start].y);
        return;
    }
    
public:
    Graph(int _row, int _line, char *_in) {
        row = _row;
        line = _line;
        int size = row*line;
        in = (char*)malloc(size*sizeof(char));
        memcpy(in, _in, size*sizeof(char));
        build_graph();
    }
    Graph() {
        Graph(0, 0, NULL);
    }
    ~Graph() {
        free(in);
    }
    void dijkstra(P start, P last) {
        memset(mark,false,sizeof(mark));    //³õÊ¼»¯±ê¼ÇÊý×é
        memset(pre,-1,sizeof(pre));
        for(int i=0;i<s;i++) dis[i]=INF;  //½«²»Á¬Í¨µÄ¾àÀëÎÞÏÞ´ó
        priority_queue<node>que;          //½¨Á¢¶Ó
        while(!que.empty()) que.pop();    //Çå¿Õ¶ÓÁÐ
        dis[start.x*line+start.y]=0;
        que.push(node(start.x*line+start.y,0));     //½«³õÊ¼µã·ÅÈë¶ÓÖÐ
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
        return;
    }
    void print_path(P start, P last) {
        if(dis[last.x*line+last.y]==INF)
            printf("-1\n");
        else
        {
            printf("(%d,%d)->(%d,%d)[%d]:", start.x, start.y, last.x, last.y, dis[last.x*line+last.y]);
            print_path_sub(start.x*line+start.y, last.x*line+last.y);
            printf("\n");
        }
        return;
    }
};

int main()
{
    freopen("/Users/nyhuang/Desktop/tmp/test/input.txt","r",stdin);
    //freopen("/Users/nyhuang/Desktop/tmp/test/output.txt","w",stdout);
    int _row, _line;
    char *_in = (char*)malloc(100*sizeof(char));
    while (scanf("%d%d",&_row,&_line)!=EOF)
    {
        for(int i=0;i<_row;i++)
        {
            getchar();
            for(int j=0;j<_line;j++)
            {
                scanf("%c",&_in[i*_line+j]);
            }
        }
        Graph g(_row, _line, _in);
        P start, last;
        scanf("%d%d%d%d",&start.x,&start.y,&last.x,&last.y);
        g.dijkstra(start, last);
        g.print_path(start, last);
    }
    free(_in);
    return 0;
}
