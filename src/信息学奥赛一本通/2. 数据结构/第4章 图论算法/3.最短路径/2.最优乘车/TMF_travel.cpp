#include <iostream>
#include <stdlib.h>
#include <cstdio>
#include <cstring>

using namespace std;
bool gDebug = false;
int w[1001][1001], link[10001];

int main()
{
    int m,n;
    int x;
    //memset(w,0x7f,sizeof(w));
    cin >> m >> n;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			w[i][j] = 10000;
		}
	}
	if (gDebug) {
		cout << m << "\t" << n << "\t" << w[1][1] << endl;
	}
	for(int i=1;i<=m;i++)
    {
        int tot=0;
        do
        {
            cin >> x;
            link[++tot]=x;
			if (gDebug) {
				cout << x << "  ";
			}
        }while(getchar()!='\n');
		if (gDebug) {
			cout << endl;
		}
		for(int j=1;j<=tot-1;j++)
        {
            for(int k=j+1;k<=tot;k++)
            {
                w[link[j]][link[k]]=1;
            }
        }
    }
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        {
            for(int k=1;k<=n;k++)
            {
                w[j][k]=min(w[j][k],w[j][i]+w[i][k]);
            }
        }
    }
    if(w[1][n]<=m+1)
    {
        cout << w[1][n]-1 << endl;
    }
    else
    {
        cout << "NO" << endl;
    }
    // system("PAUSE");
    return 0;
}
