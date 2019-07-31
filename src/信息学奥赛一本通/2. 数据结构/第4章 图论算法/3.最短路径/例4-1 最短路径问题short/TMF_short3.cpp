#include <iostream>
#include <cstdio>
#include <cmath>

using namespace std;
bool gDebug = false;

int main()
{
    double a[101][3],dis[1001],w[1001];
    double min1;
    int n,m,x,y,k,s,t;
    int f[1001][3];
    bool b[101];
    cin >> n;
	if(gDebug)
		cout << "n=" << n << endl;

	for(int i=1;i<=n;i++)
    { 
        scanf("%lf%lf",&a[i][1],&a[i][2]);
		//cin >> a[i][1] >> a[i][2];
		if (gDebug)
			cout << "\t" << a[i][1] << " " << a[i][2] << endl;
    }
    cin >> m;
	if(gDebug)
		cout << "m=" << m << endl;

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
        w[i]=sqrt(pow(a[x][1]-a[y][1],2)+pow(a[x][2]-a[y][2],2));
		if(gDebug)
			cout << "\ti=" << i << "\t" << x << " " << y << " w[" << i << "]="  << w[i] << endl;

	}
    cin >> s >> t;
	if (gDebug)
		cout << "s=" << s << "\tt=" << t << endl;

    dis[s]=0;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
			if (gDebug)
				cout << "\tf1=" << f[j][1] << " " << f [j][1] << "\tf2=" << f[j][2] << "\tdis1+wj=" <<  dis[f[j][1]] + w[j] << "\t" << dis[f[j][2]] << endl;
			if(dis[f[j][1]]+w[j] < dis[f[j][2]])
            {
                dis[f[j][2]]=dis[f[j][1]]+w[j];
            }
			if (gDebug)
				cout << "\t" << dis[f[j][2]] + w[j] << "\t" << dis[f[j][1]] << endl;
			if(dis[f[j][2]]+w[j] < dis[f[j][1]])
            {
                dis[f[j][1]]=dis[f[j][2]]+w[j];
            }
			if (gDebug)
				cout << "\t" << i << "\t" << j << "\tdis=" << dis[f[j][1]] << "\t" << dis[f[j][2]] << endl;
        }
    }
    printf("%.2f\n",dis[t]);
    return 0;
}
