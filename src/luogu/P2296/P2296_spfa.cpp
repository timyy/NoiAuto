//
// 这题可以不搞反向图，而是直接反向图，求最短路径就求终点到起点的最短路径，它和起点到终点的最短路是等价的。
//
#include <iostream>
#include <stdlib.h>
#include <cstring>
#include <cstdio>

using namespace std;

// 分级处理debug 信息。
#define DEBUG
#define DEBUGR

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
const int NMax = 10001;
const int MMax = 200001;
const int INF = 0x3f3f3f3f;
int flink[MMax][3];
int fhead[NMax];

bool mark[NMax];
bool mark2[NMax];
long dis[NMax];

// 加 边号，起点号，终点， 边数组， 点数组
void add(int i, int u, int v, int links[][3], int heads[]) {

	links[i][0] = u;
	links[i][1] = v;
	links[i][2] = heads[u];
	heads[u] = i; //这个好，不用像下面那样要遍历一遍。
	// 就是把当前heads[点]存到next中，然后更新heads【点】到当前边号。
	// 行成了一个逆序的队列，不用从头挨个查，第一个heads[i]为0，所以没有问题。
	// 很巧妙
/*
	for (int j = heads[u]; j>0; j = links[j][2]) {
		if((j != i) && (links[j][2] == 0))
			links[j][2] = i;
		TRC_PR("\t%d %d %d\n", links[j][0], links[j][1], links[j][2]);

	}
	if (heads[u] == 0) {
		heads[u] = i;
	}
	*/
}

void init() {
	memset(dis, 0x3f, sizeof(dis));
	memset(mark, false, sizeof(mark));
	memset(mark2, false, sizeof(mark2));
	memset(flink, 0, sizeof(flink));
	memset(fhead, 0, sizeof(fhead));

	cin >> n >> m;
	TRC_PG("n=%d m=%d\n", n, m);
	int u, v;
	for (int i = 1; i <= m; i++) {
		cin >> u >> v;
		add(i, v, u, flink, fhead); //直接存反向图
		TRC_PR("%d %d\n", flink[i][0], flink[i][1], flink[i][2]);
	}
	cin >> s >> t;
	TRC_PG("s=%d  t=%d \n", s, t);

	TRC_PR("dis=%d INF=%d\n", dis[t], INF);
}

// 反向dfs，查点和终点有没有连接。
void dfsf(int p) {
	TRC_PR("\tStart anti search ... \n");
	for (int j = fhead[p]; j; j = flink[j][2]) {
		int u, v;
		u = flink[j][0];
		v = flink[j][1];
		mark[u] = true;
		if (!mark[v]) {
			mark[v] = true;
			dfsf(v);
			TRC_PR("\tu=%d v=%d\n", u, v);
		}
	}
}
// 反向dfs，查点和终点有没有连接。
// spfa，单纯的dfs在数据过大的情况下，会因为系统堆栈溢出崩溃，所以要改为用队列的spfa
// p为开始点。

struct SPFA {
	int team[MMax];
	int head;
	int tail;
	bool exist[NMax]; // 点在队列的标记，避免队列中有重复的点。
} spfa;

void check_spfa(int p) {
	int u, v;
	memset(spfa.exist, 0, sizeof(spfa.exist));
	spfa.head = 0;
	spfa.tail = 1;
	spfa.team[1] = p;
	spfa.exist[p] = true;
	do {
		spfa.head++;
		spfa.head = ((spfa.head - 1) % MMax) + 1; // 循环队列
		u = spfa.team[spfa.head];
		spfa.exist[u] = false;

		mark[u] = true;
		for (int j = fhead[u]; j; j = flink[j][2]) {
			v = flink[j][1];
			if (!spfa.exist[v]) {
				mark[v] = true;
				spfa.tail++;
				spfa.tail = ((spfa.tail - 1) % MMax) + 1; // 循环队列
				spfa.team[spfa.tail] = v;
				spfa.exist[v] = true;
			}
		}

	} while (spfa.head < spfa.tail);
}

// 去掉所有不到终点的点
void delPoint() {
	for (int i = 1; i <= n; i++) {
		mark2[i] = mark[i];
	}
	// 不用从点开始，只要遍历所有的边，（因为是反向图），只要把起点被mark为0，终点mark2标为0即可。
	for (int j = 1; j <= m; j++) {
		int u, v;
		u = flink[j][0]; // 反向图。
		v = flink[j][1];
		TRC_PR("\t\t[%d]-->(%d) \n", v, u);
		if (!mark[u]) {
			mark2[v] = false;
		}
	}

}
// 正向dfs，查最短距离
void dfs(int p) {
	for (int j = fhead[p]; j; j = flink[j][2]) {
		int u, v;
		u = flink[j][0];
		v = flink[j][1];
		if (u == p) {
			if (mark2[v]) {
				dis[v] = dis[v] > dis[u] + 1 ? dis[u] + 1 : dis[v];
				dfs(v);
			}
		}
	}
}

void short_spfa(int p) {
	int u, v;
	memset(spfa.exist, 0, sizeof(spfa.exist));
	spfa.head = 0;
	spfa.tail = 1;
	spfa.team[1] = p;
	spfa.exist[p] = true;
	do {
		spfa.head++;
		spfa.head = ((spfa.head - 1) % MMax) + 1; // 循环队列
		u = spfa.team[spfa.head];
		spfa.exist[u] = false;

		for (int j = fhead[u]; j; j = flink[j][2]) {
			v = flink[j][1];
			if (mark2[v] && dis[v] > dis[u] + 1) {
				dis[v] = dis[u] + 1;
				TRC_PR("\t\t%d-->%d = %d --> %d\n", u, v, dis[u], dis[v]);
				if (!spfa.exist[v]) { //只有是最小点，才往下遍历，否则就不往下了。
					spfa.tail++;
					spfa.tail = ((spfa.tail - 1) % MMax) + 1; // 循环队列
					spfa.team[spfa.tail] = v;
					spfa.exist[v] = true;
				}
			}

		}

	} while (spfa.head < spfa.tail);
}

int main() {
	init();
	check_spfa(t);
	delPoint();
	dis[t] = 0;
	short_spfa(t); // 反向图，从终点开始

	TRC_PG("\t%d\n", dis[s]);
	if (dis[s] < INF) {
		cout << dis[s];
	}
	else {
		cout << -1;
	}
}