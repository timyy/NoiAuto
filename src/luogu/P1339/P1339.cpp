#include <iostream>
#include <stdlib.h>
#include <cstring>

using namespace std;
// 分级处理debug 信息。
//#define DEBUG
//#define DEBUGR

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

/*
7 11 5 4
2 4 2
1 4 3
7 2 2
3 4 3
5 7 5
7 3 3
6 1 1
6 3 4
2 4 3
5 6 3
7 2 1
*/
const int nmax = 2601;
const int mmax = 13000; // 无向图，双倍
const int mmax2 = 26000;

const int inf = 0x3f3f3f3f;

int link[mmax][4];
int n, m, ts, te;
int dis[nmax];
int team[mmax2];
bool spexit[nmax];
int head[nmax];

void add(int i, int u, int v, int w)
{
	link[i][0] = u;
	link[i][1] = v;
	link[i][2] = head[u];
	link[i][3] = w;
	head[u] = i;
}

void shortspfa(int p)
{
	memset(dis, 0x3f, sizeof(dis));
	memset(spexit, false, sizeof(spexit));
	int u, v;
	int sphead = 0, tail = 1;
	dis[p] = 0;
	team[1] = p;
	spexit[p] = true;
	do
	{
		sphead++;
		sphead = (sphead - 1) % mmax2 + 1;
		u = team[sphead];
		spexit[u] = false;
		TRC_PR("\t\t%d h=%d -> t=%d\n", u, sphead, tail);
		for (int j = head[u]; j; j = link[j][2])
		{
			v = link[j][1];
			if ((dis[v] > dis[u] + link[j][3]))
			{
				dis[v] = dis[u] + link[j][3];
				if (!spexit[v])
				{
					tail++;
					tail = (tail - 1) % mmax2 + 1;
					team[tail] = v;
					spexit[v] = true;
				}
			}

			TRC_PR("\t%d -> %d == %d --> %d \n", u, v, dis[u], dis[v]);
		}

	} while (sphead < tail);
	TRC_PR("end spfa.\n");
}

int main()
{
	memset(head, 0, sizeof(head));
	int u, v,w;
	cin >> n >> m >> ts >> te;
	TRC_PG("n=%d m=%d s=%d t=%d\n", n, m, ts, te);
	for (int j = 1; j <= m; j++)
	{
		cin >> u >> v >> w;
		add(j, u, v,w); 
		add(j + m, v, u, w); // 无向图，来回都可以，所以要把另一边也加上
	}
	TRC_PG("short spfa ...\n");
	shortspfa(ts);
	TRC_PG("dis[%d] = %d\n", te, dis[te]);
	cout << (dis[te] < inf ? dis[te] : -1) << endl;
	// system("PAUSE");
	return 0;
}
