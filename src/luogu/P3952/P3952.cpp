#include <iostream>
#include <stdlib.h>
#include <string>
#include <cstdio>
#include <stack>

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
	stack <int> s; //堆栈，存F
	bool usedVar[26]; //变量使过了没有。
	int cnt=0, ans=0;
	int runFlag=-1;
	int runVar[26];

	for (int i = 0; i < 26; i++) {
		usedVar[i] = false;
		runVar[i] = false;
	}


	for (int i = 0; i < l; i++) { // code 一行
		int varPosion = 0;
		if (code[i][0] == 'F') { // F 循环
			// 处理F i x y
			// 变量名
			varPosion = code[i][2] - 'a'; // 变量只能是小写，如果
			 
			s.push(varPosion);
			if (usedVar[varPosion]) // 变量被占
				return -1;
			else 
			{
				usedVar[varPosion] = true;
			}
			int x=0, y=0; //x,y可能为数字或者n
			x = readNum(&code[i][4]);
			y = readNum(&code[i][4+len(x)+1]); //更好的做法是用正则表达式，或者trim+split.
			TRC_PR("x=%d\ty=%d\n", x,y);

			if (y - x > 1000) // 这个是复杂度为n的情况
			{ 
				if (runFlag == -1) {
					cnt++;  // 本循环复杂度+1
					runVar[varPosion] = true; //  记录本循环的变量，以便后面POP时减掉。因为可能会有各种并排，嵌套情况。
					ans = max(cnt, ans); //ans是所有循环中最大那个。
				}

			}else
			if (x > y) { //初值比终值大，不循环。这个最特别要做处理
				// RunFlag == -1 表示上层没有不循环的情况，这是第一次。用FLAG记住第一个开始不循环的变量。
				// 因为以后可能还会有不循环的，而且这里没有出错，还要把下的程序都检查了，(后面的有可能出错。)
				// 记住是因为后面在POP时要清掉FLAG，否则再后的循环也被干掉了。
				if (runFlag == -1)
				{
					runFlag = varPosion;
				}
			}
			else { // 常数次循环，复杂度为0

			}
		}
		if (code[i][0] == 'E') { // E 循环
			if (s.empty())
				return -1;
			varPosion = s.top();
			usedVar[varPosion] = false;
			if (runFlag == varPosion) {
				runFlag = -1; // POP到第一个0循环了，把标记去掉
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











