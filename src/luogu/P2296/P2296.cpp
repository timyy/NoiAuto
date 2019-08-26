#include <iostream>
#include <stdlib.h>
#include <cstring>
#include <cstdio>

using namespace std;

// 分级处理debug 信息。
#undef DEBUG
#undef DEBUGR

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
int n, m;
int s, t;
const int NMax = 200001;
const int INF = 0x3f3f3f3f;
int link[NMax][2];
int flink[NMax][2];
bool mark[NMax];
bool mark2[NMax];
long dis[NMax];

void init() {
	cin >> n >> m;
	TRC_PG("n=%d m=%d\n", n,m);
	for (int i = 1; i <= m; i++) {
		cin >> link[i][0] >> link[i][1];
		flink[i][1] = link[i][0];
		flink[i][0] = link[i][1];
		TRC_PG("%d %d\n", link[i][0], link[i][1]);
	}
	cin >> s >> t;
	TRC_PR("s=%d  t=%d \n", s,t);
	memset(dis, 0x3f, sizeof(dis));
	memset(mark, false, sizeof(mark));
	memset(mark2, false, sizeof(mark2));

	TRC_PR("dis=%d INF=%d\n", dis[t], INF);
}
 
// 反向dfs，查点和终点有没有连接。
void dfsf(int p){
	TRC_PG("\tStart anti search ... \n");
	for (int i = 1; i <= m; i++) {
		if (flink[i][0] == p) {
			int u, v;
			u = flink[i][0];
			v = flink[i][1];
			mark[u] = true;
			if (!mark[v]) {
				mark[v] = true;
				dfsf(v);
				TRC_PR("\tu=%d v=%d\n", u, v);
			}
		}
	}
}

// 去掉所有不到终点的点
void delPoint() {
	for (int i = 1; i <= n; i++) {
		mark2[i] = mark[i];
	}
	for (int i = 1; i <= n; i++) {
		TRC_PR("\t mark[%d]=%d ", i, mark[i]);
	}
	TRC_PR("\n");
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			int u, v;
			u = link[j][0];
			v = link[j][1];
			if (u == i) {
				if (!mark[v]) {
					mark2[u] = false;
				}
			}
		}

	}
	for (int i = 1; i <= n; i++) {
		TRC_PR("\t mark2[%d]=%d ", i,mark2[i]);
	}
	TRC_PR("\n");
}
 
// 正向dfs，查最短距离
void dfs(int p) {
	for (int i = 1; i <= m; i++) {
		int u, v;
		u = link[i][0];
		v = link[i][1];
		if (u == p) {
			if (mark2[v]) {
				dis[v] = dis[v] > dis[u] + 1 ? dis[u] + 1 : dis[v];
				dfs(v);
			}
		}
	}
}

int main() {
	init();
	dfsf(t);
	delPoint();
	dis[s] = 0;
	dfs(s);

	if (dis[t] < INF) {
		cout << dis[t];
	}
	else {
		cout << -1;
	}
}