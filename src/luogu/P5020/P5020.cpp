#include <iostream>
#include <stdlib.h>
#include <cstring>
#include <algorithm>
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
