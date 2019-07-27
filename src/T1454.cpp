#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#define M 1010
using namespace std;
int n,ans1,ans2,a[M][M];
bool flag,v[M][M];
/*
void Floodfill(int x,int y)
{
	static const int dx[]={-1,-1,-1,0,0,1,1,1};
	static const int dy[]={-1,0,1,-1,1,-1,0,1};
	int i;
	v[x][y]=true;
	for(i=0;i<8;i++)
	{
		int xx=x+dx[i],yy=y+dy[i];
		if(xx<=0||yy<=0||xx>n||yy>n)
			continue;
		if(a[xx][yy]>a[x][y])
			flag=false;
		if(a[xx][yy]==a[x][y]&&!v[xx][yy])
			Floodfill(xx,yy);
	}
}
*/
void Floodfill(int x,int y)
{
	static const int dx[]={-1,-1,-1,0,0,1,1,1};
	static const int dy[]={-1,0,1,-1,1,-1,0,1};
	static pair<int,int> q[M*M];
	int i,r=0,h=0;
	v[x][y]=true,q[++r]=make_pair(x,y);
	while(r!=h)
	{
		x=q[h+1].first;
		y=q[h+1].second;
		q[++h]=make_pair(0,0);
		for(i=0;i<8;i++)
		{
			int xx=x+dx[i],yy=y+dy[i];
			if(xx<=0||yy<=0||xx>n||yy>n)
				continue;
			if(a[xx][yy]>a[x][y])
				flag=false;
			if(a[xx][yy]==a[x][y]&&!v[xx][yy])
				v[xx][yy]=true,q[++r]=make_pair(xx,yy);
		}
	}
}
int main()
{
	int i,j;
	cin>>n;
	for(i=1;i<=n;i++)
		for(j=1;j<=n;j++)
			scanf("%d",&a[i][j]);
	for(i=1;i<=n;i++)
		for(j=1;j<=n;j++)
			if(!v[i][j])
			{
				flag=true;
				Floodfill(i,j);
				ans1+=flag;
			}
	memset(v,0,sizeof v);
	for(i=1;i<=n;i++)
		for(j=1;j<=n;j++)
			a[i][j]=-a[i][j];
	for(i=1;i<=n;i++)
		for(j=1;j<=n;j++)
			if(!v[i][j])
			{
				flag=true;
				Floodfill(i,j);
				ans2+=flag;
			}
	cout<<ans1<<' '<<ans2<<endl;
	return 0;
}