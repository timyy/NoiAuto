#include <iostream>
#include <queue>
#include <cstring>
using namespace std;

// �ּ�����debug ��Ϣ��
#define DEBUG
// #define DEBUGR
 
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

const int NMax = 20000;
const int MMax = 200001;

struct ed {
	int u;
	int next;
}e[MMax];

int n, m, x, y, d[MMax], fir[NMax], st, s, t;
bool v[NMax], ok[NMax], vis[NMax];
void add(int u, int v)
{
	e[++st].u = u; e[st].next = fir[v]; fir[v] = st;
}

void spfa(int b)  //���· 
{
	memset(v, 0, sizeof(v));
	memset(d, 0x3f3f, sizeof(d));

	queue<int> q; 
	q.push(b); v[b] = 1; d[b] = 0;
	while (!q.empty())
	{ 
		int k = q.front(); q.pop(); v[k] = 0;
		for (int i = fir[k]; i; i = e[i].next)
		{
			int u = e[i].u, w = 1;
			if (d[u] > d[k] + w && ok[e[i].u]) {
				d[u] = d[k] + w;
				if (!v[u]) 
					v[u] = 1, q.push(u);
			}
		}
	}
}

void bfs(int t)  //��һ�ε��ѱ� 
{
	memset(v, 0, sizeof(v));
	queue<int> q; 
	q.push(t); ok[t] = v[t] = 1;
	while (!q.empty())
	{
		int k = q.front(); q.pop();
		for (int i = fir[k]; i; i = e[i].next)
			if (!v[e[i].u]) {
				int u = e[i].u;
				if (!v[u]) 
					v[u] = 1, ok[u] = 1, q.push(u);
			}
	}
}
int main()
{
	cin >> n >> m;
	TRC_PG("n=%d m=%d\n", n, m);
	for (int i = 1; i <= m; i++) cin >> x >> y, add(x, y);
	cin >> s >> t;
	bfs(t);
	for (int i = 1; i <= n; i++) vis[i] = ok[i];
	for (int i = 1; i <= n; i++)
		if (!vis[i]) for (int j = fir[i]; j; j = e[j].next) {
			if (ok[e[j].u]) ok[e[j].u] = 0;
			// ����ֱ���޸ģ��к�Ч�ԡ� 
		}
	spfa(t);
	if (d[s] >= (0x3f3f3f3f)) cout << "-1" << endl;
	else cout << d[s] << endl;
	return 0;
}