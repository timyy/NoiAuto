#include <iostream>
#include <stdlib.h>
#include <cstring>

using namespace std;
// 分级处理debug 信息。
#define DEBUG
#define DEBUGR

#ifdef DEBUG
//名字替换，并在打印出来的内容加上前缀,同时加入定位的功能，并让打印的前缀具备特殊颜色(\033[1;32m  \033[0m这些表示颜色，\t一定程度上使屏幕输出对齐)
// 出绿字的，当第一级。
#define TRC_PG(fmt, args...) fprintf(stderr, "\033[1;32m  TRC_PG(%s:%d):\t\033[0m" fmt, __func__, __LINE__, ## args)
#else
#define TRC_PG 
#endif 
#ifdef DEBUGR
//名字替换，并在打印出来的内容加上前缀,同时加入定位的功能，并让打印的前缀具备特殊颜色
// 出红字的，当第二级
#define TRC_PR(fmt, args...) fprintf(stderr, "\033[1;31m  TRC_PG(%s:%d):\t\033[0m" fmt, __func__, __LINE__, ## args)
#else
#define TRC_PR
#endif 
 
const int nmax=10001;
const int mmax=200001;
int n,m;
int flink[mmax][3];
int fhead[nmax];

int s,t;
bool nop[nmax];
bool nop2[nmax];
int dis[nmax];
const int inf=0x3f;
int team[nmax];
bool spexit[nmax];

bool debug=false;

void add(int i,int u,int v)
{
    flink[i][0]=u;
    flink[i][1]=v;
    flink[i][2]=fhead[u];
    fhead[u]=i;
}

void cspfa2()
{
    int u,v;
    nop[t]=true;
    for(int i=1;i<=n;i++)
    {
        nop2[i]=nop[i];
    }
    for(int j=1;j<=m;j++)
    {
        u=flink[j][0];
        v=flink[j][1];
        if(!nop[u])
        {
            nop2[v]=false;
        }
    }
}

void cspfa(int p)
{
    memset(nop,false,sizeof(nop));
    memset(spexit,false,sizeof(spexit));
    int u,v;
    int sphead=0,tail=1;
    team[1]=p;
    spexit[p]=true;
    do
    {
        sphead++;
        u=team[sphead];
        nop[u]=true;
        spexit[u]=false;
        for(int j=fhead[u];j;j=flink[j][2])
        {
            v=flink[j][1];
            nop[v]=true;
            if(!spexit[v])
            {
                tail++;
                team[tail]=v;
                spexit[v]=true;
            }
        }
    }while(sphead<tail);
}

void shortspfa(int p)
{
    memset(dis,inf,sizeof(dis));
    memset(spexit,false,sizeof(spexit));
    int u,v;
    dis[p]=0;
    int sphead=0,tail=1;
    team[1]=p;
    spexit[p]=true;
    do
    {
        sphead++;
        u=team[sphead];
        spexit[u]=false;
        for(int j=fhead[u];j;j=flink[j][2])
        {
            v=flink[j][1];
            if((dis[v]>dis[u]+1)&&(nop2[v]))
            {
                dis[v]=dis[u]+1;
                if(!spexit[v])
                {
                    tail++;
                    team[tail]=v;
                    spexit[v]=true;
                }
            }
        }
    }while(sphead<tail);
}

void spfa(int p)
{
    memset(spexit,false,sizeof(spexit));
    int u,v;
    int sphead=0,tail=1;
    team[1]=p;
    spexit[p]=true;
    do
    { 
        sphead++;
        u=team[sphead];
        spexit[u]=false;
        for(int j=fhead[u];j;j=flink[j][2])
        {
            v=flink[j][1];
            if(!spexit[v])
            {
                tail++;
                team[tail]=v;
                spexit[v]=true;
            }
        }
    }while(sphead<tail);
}

void dij()
{
    for(int i=1;i<=n;i++)
    {
        if(nop2[i])
        {
            for(int j=fhead[i];j;j=flink[j][2])
            {
                if(flink[j][0]==i)
                {
                    int u=flink[j][0];
                    int v=flink[j][1];
                    if(dis[v]>dis[u]+1)
                    {
                        dis[v]=dis[u]+1;
                    }
                }
            }
        }
    }
}

void check2()
{
    nop[t]=true;
    for(int i=1;i<=n;i++)
    {
        nop2[i]=nop[i];
    }
    for(int i=1;i<=n;i++)
    {
        if(!nop[i])
        {
            for(int j=1;j<=m;j++)
            {
                if(flink[j][1]==i)
                {
                    nop2[flink[j][0]]=false;
                }
            }
        }
    }
}

void check(int p)
{
    nop[p]=true;
    for(int i=1;i<=m;i++)
    {
        if(flink[i][0]==p)
        {
            check(flink[i][1]);
        }
    }
}

int main()
{
    memset(dis,inf,sizeof(dis));
    memset(nop,false,sizeof(nop));
    memset(fhead,0,sizeof(fhead));
    cin >> n >> m;

	TRC_PG("n=%d m=%d\n", n, m);
    for(int i=1;i<=m;i++)
    {
        int u,v;
        cin >> u >> v;
        add(i,v,u);
    }
    cin >> s >> t;
	TRC_PG("s=%d t=%d\n", s, t);

    /*check(t);
    check2();
    dis[s]=0;
    dij();*/
    cspfa(t);
    if(debug)
    {
        cout << endl;
        for(int i=1;i<=n;i++)
        {
            cout << i << " " << nop[i] << endl;
        }
        cout << endl;
    }
    cspfa2();
    if(debug)
    {
        cout << endl;
        for(int i=1;i<=n;i++)
        {
            cout << i << " " << nop2[i] << endl;
        }
        cout << endl;
    }
    shortspfa(t);
    if(dis[s]>=inf)
    {
        cout << -1;
    }
    else
    {
        cout << dis[s];
    }
    return 0;
}
