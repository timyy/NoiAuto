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
#define TRC_PR(fmt, args...) fprintf(stderr, "\033[1;32m  TRC_PG(%s:%d):\t\033[0m" fmt, __func__, __LINE__, ## args)
#else
#define TRC_PR
#endif 

const int MaxN = 7000;
int w[MaxN][4]; // ��Ȩ��Ӿ���
int dis[MaxN];
int s, t;// �����յ�ĵ�š�
int n, m;//�����ͱ���

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
// SPFA �㷨
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
					// ͬʱ�������·����ǰ��
					//��u��v�����·������Ϊu��j��v����ôu��v��·��v��ǰ���Ϳ϶���j��v���·��u��ǰ����ͬ��

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
