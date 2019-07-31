#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>

using namespace std;
bool gDebug = true;
bool isShortPath = true;
int s, t; // �����յ�ĵ�š�
double points[101][3], dis[1001], w[1001];
int pre[1001]; //���·��

void printPre(int x)
{
//	for (int i = s; i <= t; i++)
//		cout << "-->" << pre[i];

	if (pre[x] == 0 || x == s)
		return; //pre[s][s]=0,˵���Ѿ��ݹ鵽���s

	printPre(pre[x]);
	cout << "--(" << dis[x] << ")-->" << x;

}
int main()
{
	double min1;
	int n, m, x, y, k;
	int f[1001][3];
	bool exist[1001];
	int team[1001];
	int head, tail;
	int u;

	memset(exist, false, sizeof(exist));
	memset(pre, false, sizeof(pre));

	cin >> n;
	if (gDebug)
		cout << "n=" << n << endl;

	for (int i = 1; i <= n; i++)
	{
		scanf("%lf%lf", &points[i][1], &points[i][2]);
		//cin >> a[i][1] >> a[i][2];
		if (gDebug)
			cout << "\t" << points[i][1] << " " << points[i][2] << endl;
	}
	cin >> m;
	if (gDebug)
		cout << "m=" << m << endl;

	for (int i = 1; i <= m + 1; i++)
	{
		dis[i] = 0x7fffffff / 3;
		f[i][1] = f[i][2] = 0x7fffffff / 3;
	}

	for (int i = 1; i <= m; i++)
	{
		scanf("%d%d", &x, &y);
		f[i][1] = x;
		f[i][2] = y;
		w[i] = sqrt(pow(points[x][1] - points[y][1], 2) + pow(points[x][2] - points[y][2], 2));
		pre[y] = x; //x��y��������Ȼ��x��y�����·��y��ǰ����x
		pre[x] = y;
		if (gDebug)
			cout << "\ti=" << i << "\t" << x << " " << y << " w[" << i << "]=" << w[i] << endl;

	}
	cin >> s >> t;
	if (gDebug)
		cout << "s=" << s << "\tt=" << t << endl;

	dis[s] = 0;

	// SPFA �㷨
	team[1] = s; head = 0; tail = 1; exist[s] = true;
	do
	{
		head++;
		u = team[head];
		exist[u] = false;
		if (gDebug)
			cout << "\thead=" << head << "\tu " << u << endl;

		for (int j = 1; j <= m; j++)
		{
			if (f[j][1] == u || f[j][2] == u) {
				int v;
				if (f[j][1] == u) {
					v = f[j][2];
				} 
				else {
					v = f[j][1];
				}
				if (gDebug)
					cout << "\t\tj=" << j << "\tu" << u << "-->v" << v << "\tdisu=" << dis[u] << "\tdisv=" << dis[v] << "\tw " << w[j] << endl;
				if (dis[v] > dis[u] + w[j]) {
					if (gDebug)
						cout << "\t\t\thead=" << head << "\tu " << u << "-->v " << v << "\tdis " << dis[v] << " ==> " << dis[u] + w[j] << endl;
					dis[v] = dis[u] + w[j];
					pre[v] = u;
					cout << "\t\t\tpre=" << v <<" " <<  u << "\t" << pre[v] << endl;
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
	printf("%.2f\n", dis[t]);
	if (isShortPath) {
		cout << "\nShortpath:\t" << s;
			printPre(t);
	}
	return 0;
}
