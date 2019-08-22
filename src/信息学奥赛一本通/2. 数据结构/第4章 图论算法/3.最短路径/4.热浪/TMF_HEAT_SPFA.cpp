#include <iostream>
#include <stdlib.h>
#include <cstring>
#include <cstdio>

using namespace std;

// 分级处理debug 信息。
#define DEBUG
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
#define TRC_PR(fmt, args...) fprintf(stderr, "\033[1;32m  TRC_PG(%s:%d):\t\033[0m" fmt, __func__, __LINE__, ## args)
#else
#define TRC_PR
#endif 

const int MaxN = 7000;
int w[MaxN][4]; // 边权领接矩阵
int dis[MaxN];
int s, t;// 起点和终点的点号。
int n, m;//点数和边数

void init()
{
	cin >> n >> m;
	cin >> s >> t;
#ifdef DEBUG 
	TRC_PG("n=%d\tm=%d\ts=%d\tt=%d\n", m, n, s, t);
#endif
	for (int i = 1; i <= m; i++) {
		scanf("%d%d%d", &w[i][1], &w[i][2], &w[i][3]);
#ifdef DEBUG1 
		TRC_PG("%d\t%d\t%d\n", w[i][1], w[i][2], w[i][3]);
#endif
	}
	for (int i = 1; i <= m + 1; i++)
	{
		dis[i] = 0x1fffffff;
	}
}
void spfa()
//TODO
///
// SPFA 算法
{
	int team[MaxN];
	bool exist[MaxN];
	int head, tail;
	int u, v;

	dis[s]= 0;
	team[1] = s; head = 0; tail = 1; exist[s] = true;
	do {
		head++;
		u = team[head];
		exist[u] = false;
		for (int j = 1; j <= m; j++) {
			if (w[j][1] == u || w[j][2] == u) {
				if (w[j][1] == u) {
					v = w[j][2];
				}
				else {
					v = w[j][1];
				}
				if (dis[v] > dis[u] + w[j][3]) {
					dis[v] = dis[u] + w[j][3];
					// 同时更换最短路径的前驱
					//从u到v的最短路径更新为u→j→v，那么u到v短路径v的前驱就肯定与j到v最短路径u的前驱相同。

					if (!exist[v])
					{
						tail++;
						team[tail] = v;
						exist[v] = true;
					}
				}
			}
		}
	} while (head < tail);
	printf("%d\n", dis[t]);
}

int main()
{
	init();
	spfa();
	return 0;
}
