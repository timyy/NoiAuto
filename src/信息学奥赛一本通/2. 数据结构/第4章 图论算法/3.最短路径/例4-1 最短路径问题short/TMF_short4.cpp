#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <stdlib.h>

using namespace std;

int main()
{
    double points[101][3],dis[1001],w[1001];
    double min1;
    int n,m,x,y,k,s,t;
    int f[1001][3];
	bool exist[1001];
	int team[1001];
	int head, tail;
	int u;
    cin >> n;
	for(int i=1;i<=n;i++)
    {
        scanf("%lf%lf",&points[i][1],&points[i][2]);
    }
    cin >> m;
    for(int i=1;i<=m+1;i++)
    {
        dis[i]=0x7fffffff/3;
        f[i][1]=f[i][2]=0x7fffffff/3;
    }
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d",&x,&y);
        f[i][1]=x;
        f[i][2]=y;
        w[i]=sqrt(pow(points[x][1]-points[y][1],2)+pow(points[x][2]-points[y][2],2));
	}
    cin >> s >> t;
	memset(exist,false,sizeof(exist));
    dis[s]=0;
	team[1]=s;
	head=0;
	tail=1;
	exist[s]=true;
	do
	{
		head++;
		u=team[head];
		exist[u]=false;
		for(int j=1;j<=m;j++)
		{
			if(f[j][1]==u||f[j][2]==u)
            {
				int v;
				if(f[j][1]==u)
				{
					v=f[j][2];
				}
				else
				{
					v=f[j][1];
				}
				if(dis[v]>dis[u]+w[j])
                {
					dis[v]=dis[u]+w[j];
					if (!exist[v])
					{
						tail++;
						team[tail]=v;
						exist[v]=true;
					}
				}
			}
		}
	}while(head<tail);
    printf("%.2f\n",dis[t]);
    return 0;
}
