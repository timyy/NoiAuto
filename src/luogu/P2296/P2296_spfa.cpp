//
// ������Բ��㷴��ͼ������ֱ�ӷ���ͼ�������·�������յ㵽�������·����������㵽�յ�����·�ǵȼ۵ġ�
//
#include <iostream>
#include <stdlib.h>
#include <cstring>
#include <cstdio>

using namespace std;

// �ּ�����debug ��Ϣ��
#define DEBUG
#define DEBUGR

#ifdef DEBUG
//�����滻�����ڴ�ӡ���������ݼ���ǰ׺,ͬʱ���붨λ�Ĺ��ܣ����ô�ӡ��ǰ׺�߱�������ɫ(\033[1;32m  \033[0m��Щ��ʾ��ɫ��\tһ���̶���ʹ��Ļ�������)
// �����ֵģ�����һ����
#define TRC_PG(fmt, args...) fprintf(stderr, "\033[1;32m  TRC_PG(%s:%d):\t\033[0m" fmt, __func__, __LINE__, ## args)
#else
#define TRC_PG 
#endif 
#ifdef DEBUGR
//�����滻�����ڴ�ӡ���������ݼ���ǰ׺,ͬʱ���붨λ�Ĺ��ܣ����ô�ӡ��ǰ׺�߱�������ɫ
// �����ֵģ����ڶ���
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

// �� �ߺţ����ţ��յ㣬 �����飬 ������
void add(int i, int u, int v, int links[][3], int heads[]) {

	links[i][0] = u;
	links[i][1] = v;
	links[i][2] = heads[u];
	heads[u] = i; //����ã���������������Ҫ����һ�顣
	// ���ǰѵ�ǰheads[��]�浽next�У�Ȼ�����heads���㡿����ǰ�ߺš�
	// �г���һ������Ķ��У����ô�ͷ�����飬��һ��heads[i]Ϊ0������û�����⡣
	// ������
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
		add(i, v, u, flink, fhead); //ֱ�Ӵ淴��ͼ
		TRC_PR("%d %d\n", flink[i][0], flink[i][1], flink[i][2]);
	}
	cin >> s >> t;
	TRC_PG("s=%d  t=%d \n", s, t);

	TRC_PR("dis=%d INF=%d\n", dis[t], INF);
}

// ����dfs�������յ���û�����ӡ�
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
// ����dfs�������յ���û�����ӡ�
// spfa��������dfs�����ݹ��������£�����Ϊϵͳ��ջ�������������Ҫ��Ϊ�ö��е�spfa
// pΪ��ʼ�㡣

struct SPFA {
	int team[MMax];
	int head;
	int tail;
	bool exist[NMax]; // ���ڶ��еı�ǣ�������������ظ��ĵ㡣
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
		spfa.head = ((spfa.head - 1) % MMax) + 1; // ѭ������
		u = spfa.team[spfa.head];
		spfa.exist[u] = false;

		mark[u] = true;
		for (int j = fhead[u]; j; j = flink[j][2]) {
			v = flink[j][1];
			if (!spfa.exist[v]) {
				mark[v] = true;
				spfa.tail++;
				spfa.tail = ((spfa.tail - 1) % MMax) + 1; // ѭ������
				spfa.team[spfa.tail] = v;
				spfa.exist[v] = true;
			}
		}

	} while (spfa.head < spfa.tail);
}

// ȥ�����в����յ�ĵ�
void delPoint() {
	for (int i = 1; i <= n; i++) {
		mark2[i] = mark[i];
	}
	// ���ôӵ㿪ʼ��ֻҪ�������еıߣ�����Ϊ�Ƿ���ͼ����ֻҪ����㱻markΪ0���յ�mark2��Ϊ0���ɡ�
	for (int j = 1; j <= m; j++) {
		int u, v;
		u = flink[j][0]; // ����ͼ��
		v = flink[j][1];
		TRC_PR("\t\t[%d]-->(%d) \n", v, u);
		if (!mark[u]) {
			mark2[v] = false;
		}
	}

}
// ����dfs������̾���
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
		spfa.head = ((spfa.head - 1) % MMax) + 1; // ѭ������
		u = spfa.team[spfa.head];
		spfa.exist[u] = false;

		for (int j = fhead[u]; j; j = flink[j][2]) {
			v = flink[j][1];
			if (mark2[v] && dis[v] > dis[u] + 1) {
				dis[v] = dis[u] + 1;
				TRC_PR("\t\t%d-->%d = %d --> %d\n", u, v, dis[u], dis[v]);
				if (!spfa.exist[v]) { //ֻ������С�㣬�����±���������Ͳ������ˡ�
					spfa.tail++;
					spfa.tail = ((spfa.tail - 1) % MMax) + 1; // ѭ������
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
	short_spfa(t); // ����ͼ�����յ㿪ʼ

	TRC_PG("\t%d\n", dis[s]);
	if (dis[s] < INF) {
		cout << dis[s];
	}
	else {
		cout << -1;
	}
}