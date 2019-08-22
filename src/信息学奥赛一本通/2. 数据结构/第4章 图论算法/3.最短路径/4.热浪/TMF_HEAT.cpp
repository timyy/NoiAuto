#include <iostream>
#include <stdlib.h>
#include <cstring>
#include <cstdio>

using namespace std;

int link[2500][2500];

int main()
{
    int t,c,ts,te;
    int x,y;
    cin >> t >> c >> ts >> te;
    memset(link,100000,sizeof(link));
    for(int i=1;i<=c;i++)
    {
        cin >> x >> y;
        cin >> link[x][y];
    }
    for(int i=1;i<=t;i++)
    {
        for(int j=1;j<=t;j++)
        {
            for(int k=1;k<=t;k++)
            {
                link[k][j]=min(link[k][j],link[k][i]+link[i][j]);
            }
        }
    }
    cout << link[ts][te];
    system("PAUSE");
    return 0;
}
