#include <iostream>
#include <stdlib.h>
#include <cstring>

using namespace std;
// �ּ�����debug ��Ϣ��
#define DEBUG
#define DEBUGR

#ifdef DEBUG
//�����滻�����ڴ�ӡ���������ݼ���ǰ׺,ͬʱ���붨λ�Ĺ��ܣ����ô�ӡ��ǰ׺�߱�������ɫ(\033[1;32m  \033[0m��Щ��ʾ��ɫ��\tһ���̶���ʹ��Ļ�������)
// �����ֵģ�����һ����
#define TRC_PG(fmt, args...) fprintf(stderr, "\033[1;32m  TRC_PG(%s:%d):\t\033[0m" fmt, __func__, __LINE__, ## args)
#else
#define TRC_PG 
#endif 
#ifdef DEBUGR
//�����滻�����ڴ�ӡ���������ݼ���ǰ׺,ͬʱ���붨λ�Ĺ��ܣ����ô�ӡ��ǰ׺�߱�������ɫ
// �����ֵģ����ڶ���
#define TRC_PR(fmt, args...) fprintf(stderr, "\033[1;31m  TRC_PG(%s:%d):\t\033[0m" fmt, __func__, __LINE__, ## args)
#else
#define TRC_PR
#endif 

const int cmax=501;
const int nmax=801;
const int mmax=3000;
const int INF = 0x3f3f3f3f;
int n,m,c;
int nc[nmax];
int cpoint[cmax];
int link[mmax*2][4];
int dis[nmax];
int team[mmax*2];
bool spexit[nmax];
int head[nmax];

void add(int i,int u,int v,int w)
{
    link[i][0]=u;
    link[i][1]=v;
    link[i][2]=head[u];
    head[u]=i;
	link[i][3] = w;
}

void shortspfa(int p)
{
    memset(spexit,false,sizeof(spexit));
    int u,v;
    int sphead=0,tail=1;
    dis[p]=0;
    team[1]=p;
    spexit[p]=true;
    do
    {
        sphead++;
		sphead = (sphead - 1) % (2 * mmax) + 1;
        u=team[sphead];
        spexit[u]=false;
        for(int j=head[u];j;j=link[j][2])
        {
            v=link[j][1];
            if((dis[v]>dis[u]+link[j][3]))
            {
                dis[v]=dis[u]+link[j][3];
                if(!spexit[v])
                {
                    tail++;
					tail = (tail - 1) % (2 * mmax) + 1;

                    team[tail]=v;
                    spexit[v]=true;
                }
            }
        }
    }while(sphead<tail);
}

int main()
{
    int u,v,w;
    int ans=INF;
    cin >> c >> n >> m;
    for(int i=1;i<=c;i++)
    {
        cin >> cpoint[i];  
    }
    for(int j=1;j<=m;j++)
    {
        cin >> u >> v >> w;
        add(j,u,v,w);
		add(j + m, v, u, w);
    }
    for(int i=1;i<=n;i++)
    {
        int sum=0;
        memset(dis,0x3f,sizeof(dis));
        shortspfa(i);
        for(int j=1;j<=c;j++)
        {
            sum+=dis[cpoint[j]];
        }
        if(ans>sum)
        {
            ans=sum;
        }
    }
    cout << ans;
    //system("PAUSE");
    return 0;
}
