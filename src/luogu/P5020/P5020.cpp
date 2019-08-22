#include <iostream>
#include <stdlib.h>
#include <cstring>
#include <algorithm>
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
#define TRC_PR(fmt, args...) fprintf(stderr, "\033[1;32m  TRC_PG(%s:%d):\t\033[0m" fmt, __func__, __LINE__, ## args)
#else
#define TRC_PR
#endif 

using namespace std;

int check(int,int, int );
int n;
int k0;
int a[100];
bool state[100];

int main()
{
    int t;
    cin >> t;
    for(int i=0;i<t;i++)
    {
        memset(state,0,sizeof(state));
        cin >> n;
		TRC_PG("%d\n", n);

        for(int j=0;j<n;j++)
        {
             cin >> a[j];
			TRC_PG("%d  ", a[j]);
        }
        sort(a,a+n);
        for(int j=1;j<n;j++)
        {
            k0=0;
            check(0,a[j],j-1);
			TRC_PR("\tj=%d  %d  k0=%d\n", j,a[j],k0);
            if(k0)
            {
                state[j]=true;
            }
        }
        int m=0;
        for(int j=0;j<n;j++)
        {
            if(!state[j])
            {
                m++;
            }
        }
        cout << m << endl;
    }
    //system("PAUSE");
    return 0;
} 

int check(int i,int k , int n0)
{
    int w;
    if(k==0)
    {
        k0=1;
        return 0;
    }
	if (k < 0) { return 0; }
    if(k0==1)
    {
        return 0;
    }
    if(i>n0)
    {
        return 0;
    }
    w=k/a[i];
    for(int j=0;j<=w;j++)
    {
        if(k-a[i]>=0)
        {
            check(i+1,k-j*a[i],n0);
        }

    }
    return 0;
}
