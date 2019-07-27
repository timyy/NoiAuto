//¸¥ÂåÒÁµÂ
#include <iostream>
#include <stdlib.h>

using namespace std;

int main()
{
    int n.m;
    int u,v;
    int dis[101][101];
    int w[101][101];
    cin >> n;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        {
            cin >> w[i][j];
        }
    }
    cin >> u >> v;
    if(w[u][v]>=0)
    {
        dis[u][v]=w[u][v];
    }
    else
    {
        dis[u][v]=0x7fffffff;
    }
    for(int k=1;k<=n;k++)
    {
        for(int i=1;i<=n;i++)
        {
            for(int j=1;j<=n;j++)
            {
                if(dis[i][j]>dis[i][k]+dis[k][i])
                {
                    dis[i][j]=dis[i][k]+dis[k][j];
                }
            }
        }
    }
    cout << dis[i][j];
    system("PAUSE");
    return 0;
}
