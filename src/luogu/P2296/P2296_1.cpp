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
const int MMax = 200000;
const int INF = 0x3f3f3f3f;
int link[MMax][3];
int flink[MMax][3];
bool mark[NMax];
bool mark2[NMax];
long dis[NMax];

int head[NMax];
int fhead[NMax];

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
	memset(link, 0, sizeof(link));
	memset(flink, 0, sizeof(flink));
	memset(head, 0, sizeof(head));
	memset(fhead, 0, sizeof(fhead));

	cin >> n >> m;
	TRC_PG("n=%d m=%d\n", n,m);
	int u, v;
	for (int i = 1; i <= m; i++) {
		cin >> u >> v;
		add(i,u, v, link, head);
		add(i,v, u, flink, fhead);
		TRC_PR("%d %d\n", link[i][0], link[i][1],link[i][3]);
	}
	cin >> s >> t;
	TRC_PG("s=%d  t=%d \n", s,t);

	TRC_PR("dis=%d INF=%d\n", dis[t], INF);
}
 
// ����dfs�������յ���û�����ӡ�
void dfsf(int p){
	TRC_PR("\tStart anti search ... \n");
	for (int j = fhead[p]; j ; j = flink[j][2]) {
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

// ȥ�����в����յ�ĵ�
void delPoint() {
	for (int i = 1; i <= n; i++) {
		mark2[i] = mark[i];
	}
	for (int i = 1; i <= n; i++) {
		TRC_PR("\t mark[%d]=%d ", i, mark[i]);
	}
	TRC_PR("\n");
	for (int i = 1; i <= n; i++) {
		for (int j = head[i]; j ; j = link[j][2]) {
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
 
// ����dfs������̾���
void dfs(int p) {
	for (int j = head[p]; j ; j = link[j][2]) {
		int u, v;
		u = link[j][0];
		v = link[j][1];
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

	TRC_PG("\t%d\n",dis[t]);
	if (dis[t] < INF) {
		cout << dis[t];
	}
	else {
		cout << -1;
	}
}