#include <iostream>
#include <stdlib.h>
#include <cstdio>
#include <cstring>

using namespace std;

bool debug=false;

int main()
{
    int m,n;
    int v,u;
    int link[1001][3],dis[1001],w[1001];
	int maxN = 1000000;
    cin >> n >> m;
    if(debug)
    {
        cout <<  "\t" <<n << " " << m << endl;
    }
    memset(w, maxN,sizeof(w));
	memset(dis, maxN, sizeof(dis));
    for(int i=1;i<=m;i++)
    {
        cin >> link[i][1] >> link[i][2];
        cin >> w[i];
    }
    if(debug)
    {
        for(int i=1;i<=m;i++)
        {
            cout << "\t" << link[i][1] << " " << link[i][2] << " " << w[i] << endl;
        }
    }
    dis[1]=0;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            if((link[j][1]==i)||(link[j][2]==i))
            {

                if(link[j][1]==i)
                {
                    v=link[j][2];
                }
                else
                {
                    v=link[j][1];
                }
				if (debug)
				{
					cout << "\t\t" << i << "->" << v << "\t" << dis[v] << "\t" << dis[i]+ w[j] << endl;
				}

                if(dis[v]>dis[i]+w[j])
                {
                    dis[v]=dis[i]+w[j];
                }
            }
        }
    }
    int maxx=0;
    for(int i=1;i<=n;i++)
    {
        if(maxx<dis[i])
        {
            maxx=dis[i];
        }
    }
    cout << maxx << endl;
    if(debug)
		system("PAUSE");
    return 0;
}
