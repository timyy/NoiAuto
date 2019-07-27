//¸¥ÂåÒÁµÂ
#include <iostream>
#include <stdlib.h>
#include <cstdio>
#include <cmath>
#include <cstring>

using namespace std;

int main()
{
    int n,m,x,y,s,e;
    int dis[101][101];
    double w[101][101];
    cin >> n;
    for(int i=1;i<=n;i++)
    {
        cin >> dis[i][1] >> dis[i][2];
    }
    cin >> m;
    memset(w,0x7f,sizeof(w));
    for(int i=1;i<=m;i++)
    {
        cin >> x >> y;
        w[y][x]=w[x][y]=sqrt(pow(double(dis[x][1]-dis[y][1]),2)+pow(double(dis[x][2]-dis[y][2]),2));
    }
    cin >> s >> e;
    for(int k=1;k<=n;k++)
    {
        for(int i=1;i<=n;i++)
        {
            for(int j=1;j<=n;j++)
            {
                if((i!=j)&&(i!=k)&&(j!=k)&&(w[i][k]+w[k][j]<w[i][j]))
                {
                    w[i][j]=w[i][k]+w[k][j];
                }
            }
        }
    }
    printf("%.2f\n",w[s][e]);
    // system("PAUSE");
    return 0;
}
