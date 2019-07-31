//µœΩ‹ÀπÃÿ¿≠
#include <iostream>
#include <stdlib.h>
#include <cstdio>
#include <cstring>
#include <cmath>

bool gDebug = false;
using namespace std;

int main()
{
	int n, m, x, y, s, e, k;
	int dis[101][3];
	double w[101];
	bool b[101];
	double f[101][101];
	double min1;
	double maxx = 1e30;
	cin >> n;
	for (int i = 1; i <= n; i++)
	{
		cin >> dis[i][1] >> dis[i][2];
		//		cout << dis[i][1] << "  " << dis[i][2] << endl;
	}
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			f[i][j] = maxx;
		}
	}
	//	cout << endl;
	cin >> m;
	for (int i = 1; i <= m; i++)
	{
		cin >> x >> y;
		f[x][y] = f[y][x] = sqrt(pow(double(dis[x][1] - dis[y][1]), 2)
			+ pow(double(dis[x][2] - dis[y][2]), 2));
		//		cout << x << "  " << y << "  " << f[x][y] << endl;

	}
	cin >> s >> e;
	//	cout << endl;
	//	cout << s << " " << e << endl << endl;

	for (int i = 1; i <= n; i++)
	{
		w[i] = f[s][i];
		//		cout << w[i] << " ";
	}
	//	cout << endl << endl;
	memset(b, false, sizeof(b));
	b[s] = true;
	w[s] = 0;

	for (int i = 1; i <= n - 1; i++)
	{
		if (gDebug)
			cout << "i:" << i << endl;
		min1 = maxx;
		k = 0;
		for (int j = 1; j <= n; j++)
		{
			if (gDebug)
				cout << "  j:" << j << " " << b[j] << " " << w[j] << endl;

			if ((!b[j]) && (w[j] < min1))
			{
				min1 = w[j];
				k = j;
				if(gDebug)
					cout << min1 << "   " << k;
			}
		}
		if (k == 0)
		{
			break;
		}
		b[k] = true;
		for (int j = 1; j <= n; j++)
		{
			if (w[k] + f[k][j] < w[j])
			{
				w[j] = w[k] + f[k][j];
			}
		}

	}
	printf("%.2f\n", w[e]);
	// system("PAUSE");
	return 0;
}
