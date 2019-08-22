#include <iostream>
#include <stdlib.h>
#include <string>
#include <cstdio>
#include <stack>

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
#define TRC_PR(fmt, args...) fprintf(stderr, "\033[1;31m  TRC_PR(%s:%d):\t\033[0m" fmt, __func__, __LINE__, ## args)
#else
#define TRC_PR
#endif 

const int NMax = 200;
char o[NMax], code[100][NMax];
int l;
 
bool isNum(char c) {
	if (c >= '0' && c <= '9')
		return true;
	return false;
}

int readNum(char str[]) {
	int value = 0;
	int pos = 0;
	char c;

	while ((c = str[pos++]) != 0)
	{
		if (c == 'n')
		{
			value = 10e6;
			break;
		}
		if (isNum(c))
			value = value * 10 + c - '0';
		else
			break;
	}
	return value;
}
int len(int i) {
	int n = 1;

	while ((i = i / 10) != 0) {
		n++;
	}
	return n;
}
int check()
{
	stack <int> s; //��ջ����F
	bool usedVar[26]; //����ʹ����û�С�
	int cnt=0, ans=0;
	int runFlag=-1;
	int runVar[26];

	for (int i = 0; i < 26; i++) {
		usedVar[i] = false;
		runVar[i] = false;
	}


	for (int i = 0; i < l; i++) { // code һ��
		int varPosion = 0;
		if (code[i][0] == 'F') { // F ѭ��
			// ����F i x y
			// ������
			varPosion = code[i][2] - 'a'; // ����ֻ����Сд�����
			 
			s.push(varPosion);
			if (usedVar[varPosion]) // ������ռ
				return -1;
			else 
			{
				usedVar[varPosion] = true;
			}
			int x=0, y=0; //x,y����Ϊ���ֻ���n
			x = readNum(&code[i][4]);
			y = readNum(&code[i][4+len(x)+1]); //���õ���������������ʽ������trim+split.
			TRC_PR("x=%d\ty=%d\n", x,y);

			if (y - x > 1000) // ����Ǹ��Ӷ�Ϊn�����
			{ 
				if (runFlag == -1) {
					cnt++;  // ��ѭ�����Ӷ�+1
					runVar[varPosion] = true; //  ��¼��ѭ���ı������Ա����POPʱ��������Ϊ���ܻ��и��ֲ��ţ�Ƕ�������
					ans = max(cnt, ans); //ans������ѭ��������Ǹ���
				}

			}else
			if (x > y) { //��ֵ����ֵ�󣬲�ѭ����������ر�Ҫ������
				// RunFlag == -1 ��ʾ�ϲ�û�в�ѭ������������ǵ�һ�Ρ���FLAG��ס��һ����ʼ��ѭ���ı�����
				// ��Ϊ�Ժ���ܻ����в�ѭ���ģ���������û�г�����Ҫ���µĳ��򶼼���ˣ�(������п��ܳ���)
				// ��ס����Ϊ������POPʱҪ���FLAG�������ٺ��ѭ��Ҳ���ɵ��ˡ�
				if (runFlag == -1)
				{
					runFlag = varPosion;
				}
			}
			else { // ������ѭ�������Ӷ�Ϊ0

			}
		}
		if (code[i][0] == 'E') { // E ѭ��
			if (s.empty())
				return -1;
			varPosion = s.top();
			usedVar[varPosion] = false;
			if (runFlag == varPosion) {
				runFlag = -1; // POP����һ��0ѭ���ˣ��ѱ��ȥ��
			}
			if (runVar[varPosion]) {
				runVar[varPosion] = false;
				cnt--;
			}
			s.pop();
		}
	}
	if (s.size() > 0)
		return -1;
	TRC_PR("ans=%d\n", ans);
	return ans;
}

int transo()
{
	int i = 4;
	char c;
	int var = 0;

	TRC_PG("%s\n", o);
	if (o[2] == '1')
	{
		var = 0;
	}
	else
	{
		while ( (c = o[i++]) && isNum(c))
		{
				var = var * 10 + c - '0';
		}
	}
	TRC_PR("%d\n", var);
	return var;
}
void getl(char str[]) {
	char c;
	int i = 0;
	while ((c = getchar()) != EOF) {
		if (c != '\n') {
			str[i++] = c;
		}
		else {
			break;
		}
	}
	str[i] = 0;
}
int main()
{
	int t, no, noc;

	cin >> t;

	TRC_PG("%d\n", t);
	for (int i = 0; i < t; i++)
	{
		scanf("%d %s", &l, o);
		TRC_PG("%d %s\n\n", l, o);
		no = transo();
		getchar();
		for (int j = 0; j < l; j++)
		{
			getl(code[j]);
			TRC_PR("%s\n", code[j]);
		}
		noc = check();

		if (noc == -1)
		{
			cout << "ERR" << endl;
		}
		else
		{
			if (noc == no)
			{
				cout << "Yes" << endl;
			}
			else
			{
				cout << "No" << endl;
			}
		}
	}
	// system("PAUSE");
	return 0;
}











