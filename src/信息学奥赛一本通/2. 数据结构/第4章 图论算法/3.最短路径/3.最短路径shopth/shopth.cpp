#include <iostream>
#include <cstdio>
#include <stdlib.h>
#include <cstring>

using namespace std;
bool debug = false;
long long dMax = 0x1fffffffffff;

long long minlong(long long a, long long b) {
	return a < b ? a : b;
}
int main()
{
	int n, v;

	long long w[101][101];
	cin >> n;
	cin >> v;
	if (debug) {
		cout << n << "\t" << v << endl << endl;
	}
	memset(w, 0x1f, sizeof(w));
	getchar();
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			char c;
			int sign = 0;
			bool isNum = false;
			w[i][j] = 0;

			while (c = getchar())
			{
				if (debug) {
					if (c != EOF)
						cout << c;
				}
				if (c == '-')
				{
					sign = -1;
					isNum = true;
				}
				if ((c >= '0') && (c <= '9'))
				{
					isNum = true;
					if (sign >= 0) {
						w[i][j] = w[i][j] * 10.0 + c - '0';
					}
					else
					{
						w[i][j] = w[i][j] * 10.0 - c + '0';
					}
				}
				if ((c == '\n') || (c == ' ') || (c == EOF))
				{
					if (w[i][j] == 0 && sign < 0) {
						w[i][j] = dMax;
					}
					if (isNum)
						break;
					if (c == EOF) {
						break;
					}
				}
			}
		}
	}
	if (debug)
	{
		cout << endl;
		for (int i = 1; i <= n; i++)
		{
			for (int j = 1; j <= n; j++)
			{
				if (w[i][j] < dMax) {
					cout << w[i][j] << "\t";
				}
				else {
					cout << "-" << "\t";
				}
			}
			cout << endl;
		}
	}
	for (int k = 1; k <= n; k++)
	{
		for (int i = 1; i <= n; i++)
		{
			for (int j = 1; j <= n; j++)
			{
				w[i][j] = minlong(w[i][j], w[i][k] + w[k][j]);
			}
		}
	}
	if (debug)
	{
		cout << endl;
		cout << "W:" << endl;
		for (int i = 1; i <= n; i++)
		{
			for (int j = 1; j <= n; j++)
			{
				if (w[i][j] < dMax / 2) {
					cout << w[i][j] << "\t";
				}
				else {
					cout << "-" << "\t";
				}
			}
			cout << endl;
		}
	}
	for (int t = 1; t <= n; t++)
	{
		if (t != v)
		{
			cout << "(" << v << " -> " << t << ") = " << w[v][t] << endl;
		}
	}
	// system("PAUSE");
	return 0;

}
