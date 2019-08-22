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

int n,m;
const int NMax = 1000;
int link[NMax][2];
int w[NMax];
long long MaxWW, ans;
void init() {
	cin >> n;
	TRC_PG("%d\n", n);
	for (int i = 1; i <= n - 1; i++) {
		cin >> link[i][0] >> link[i][1];
		TRC_PG("%d %d\n", link[i][0] , link[i][1]);
	}
	for (int i = 1; i <= n; i++) {
		cin >> w[i];
		TRC_PR("%d ", w[i]);
	}
	TRC_PR("\n");
}

void dfs(int f, int gf) {
	int Son[NMax];
	int nSon;
	long long ww;

	nSon = 0;
	for (int i = 1; i <= n - 1; i++)
	{
		if (link[i][0] == f) {
			dfs(link[i][1], f);
			Son[nSon++] = link[i][1];
		}
	}
	for (int i = 0; i < nSon; i++)
	{
		if (gf != -1) {
			ww = w[Son[i]] * w[gf];
			MaxWW = MaxWW > ww ? MaxWW : ww;
			ans += ww;
			ans %= 10007;

		}
		for (int j = i + 1; j < nSon; j++) {
			ww = w[Son[i]] * w[Son[j]] ;
			MaxWW = MaxWW > ww ? MaxWW : ww;
			ans += ww;
			ans %= 10007;
		}
	}
}

int main() {
	init();
	dfs(1,-1);
	cout << MaxWW << " " << ans*2 % 10007;
}