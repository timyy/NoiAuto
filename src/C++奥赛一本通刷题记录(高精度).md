# C++奥赛一本通刷题记录(高精度)

[TOC]

2018年01月14日 21:04:38 小哈里 阅读数：128更多
个人分类： 月赛
C++奥赛一本通刷题记录(高精度)

    2017.11.15 By gwj1139177410

##    大整数加法 openjudge10

```c
    //Add Template

    #include<iostream>


    #include<algorithm>


    #include<string>

    using namespace std;
    const int maxn = 220;
    int a[maxn], b[maxn], c[maxn];
    int main(){
       string s1, s2;  cin>>s1>>s2;
       a[0] = s1.size();  b[0] = s2.size();
       for(int i = 1; i <= a[0]; i++)a[i]=s1[a[0]-i]-'0';
       for(int i = 1; i <= b[0]; i++)b[i]=s2[b[0]-i]-'0';
       c[0] = max(a[0],b[0])+1;
       for(int i = 1; i <= c[0]; i++){
           c[i] += a[i]+b[i];
           if(c[i] >= 10){
               c[i] %= 10;
               c[i+1]++;
           }
       }
       while(c[0]>1 && c[c[0]]==0)c[0]--;
       for(int i = c[0]; i >= 1; i--)cout<<c[i];
       return 0;
    }
```

##    大整数减法 openjudge11

```c
    //Sub Template

    #include<iostream>


    #include<algorithm>


    #include<string>

    using namespace std;
    const int maxn = 220;
    int a[maxn], b[maxn], c[maxn];
    int main(){
       string s1, s2;  cin>>s1>>s2;
       if(s1.size()<s2.size()||(s1.size()==s2.size()&&s1<s2)){
           cout<<"-";  swap(s1,s2);
       }
       a[0] = s1.size();  b[0] = s2.size();
       for(int i = 1; i <= a[0]; i++)a[i]=s1[a[0]-i]-'0';
       for(int i = 1; i <= b[0]; i++)b[i]=s2[b[0]-i]-'0';
       c[0] = max(a[0],b[0])+1;
       for(int i = 1; i <= c[0]; i++){
           if(a[i]<b[i]){ a[i+1]--; a[i]+=10; }
           c[i] = a[i]-b[i];
       }
       while(c[0]>1 && c[c[0]]==0)c[0]--;
       for(int i = c[0]; i >= 1; i--)cout<<c[i];
       return 0;
    }
```

##    计算2的N次方 openjudge12

```c
    //大数计算本质, 模拟即可

    #include<iostream>

    using namespace std;
    const int maxn = 110;
    int a[maxn];
    int main(){
       int n;  cin>>n;  a[0]=n+1;//可能进位
       a[1] = 1;
       for(int i = 1; i <= n; i++){
           for(int j = 1; j <= a[0]; j++)a[j]=a[j]+a[j];//每次乘以2
           for(int j = 1; j <= a[0]; j++){//单独处理进位避免覆盖
               if(a[j]>=10){
                   a[j+1] += a[j]/10;
                   a[j] %= 10;
               }
           }
       }
       while(a[0]>1 && a[a[0]]==0)a[0]--;
       for(int i = a[0]; i >= 1; i--)cout<<a[i];
       return 0;
    }
```

##    大整数因子 openjudge13

```c
    //高精除低精,模板

    #include<iostream>


    #include<string>

    using namespace std;
    const int maxn = 40;
    int a[maxn], flag=1;
    int mod(int a[], int b){//return a%b;
       int x = 0;
       for(int i = a[0]; i >= 1; i--){
        //c[i] = (a[i]+x*10)/b;
        x = (a[i]+x*10)%b;
    }
       return x;
    }
    int main(){
       string s;  cin>>s;  a[0]=s.size();
       for(int i = 1; i <= a[0]; i++)a[i]=s[a[0]-i]-'0';
       for(int i = 2; i <= 9; i++){
           if(mod(a,i)==0){
               cout<<i<<" ";
               flag = 0;
           }
       }
       if(flag)cout<<"none\n";
       return 0;
    }
```

##    求10000以内n的阶乘 openjudge14

```c
    //高精乘低精,模板

    #include<iostream>


    #include<string>

    using namespace std;
    const int maxn = 50010;//bugs:10000!得50000位啊
    int a[maxn];
    void mul(int a[], int b){ //a=a*b
       int x = 0; //进位位
       for(int i = 1; i <= a[0]; i++){
           a[i] = a[i]*b+x;  x = 0;
           if(a[i]>=10){
               x = a[i]/10;
               a[i] %= 10;
               if(i == a[0])a[0]++;
           }
       }
    }
    int main(){
       int n;  cin>>n;  a[0]=1; a[1]=1;
       for(int i = 2; i <= n; i++)mul(a,i);
       for(int i = a[0]; i >= 1; i--)cout<<a[i];
       return 0;
    }
```

##    阶乘和 openjudge15

```c
    //高精乘低精,高精加法,模板

    #include<iostream>


    #include<algorithm>


    #include<string>


    #include<cstring>

    using namespace std;
    const int maxn = 50010;
    int a[maxn], b[maxn], c[maxn];
    void mul(int a[], int b){ //a=a*b
       int x = 0; //进位位
       for(int i = 1; i <= a[0]; i++){
           a[i] = a[i]*b+x;  x = 0;
           if(a[i]>=10){
               x = a[i]/10;
               a[i] %= 10;
               if(i == a[0])a[0]++;
           }
       }
    }
    void add(int a[], int b[]){ //a=a+b
       for(int i = 0; i <= a[0]; i++){ c[i]=a[i]; a[i]=0;}//copy
       a[0]=max(b[0],c[0])+1;
       for(int i = 1; i <= a[0]; i++){
           a[i] += b[i]+c[i];
           if(a[i]>=10){
               a[i+1]++;
               a[i] %= 10;
           }
       }
       while(a[a[0]]==0 && a[0]>1)a[0]--;
    }
    int main(){
       int n;  cin>>n;  a[0]=b[0]=1; a[1]=b[1]=1;
       for(int i = 2; i <= n; i++){
           mul(b,i);  add(a,b);
       }
       for(int i = a[0]; i >= 1; i--)cout<<a[i];
       return 0;
    }
```

##    大整数除法 openjudge09

```c
    //高精除高精,模板

    #include<iostream>


    #include<algorithm>


    #include<string>


    #include<cstring>

    using namespace std;
    const int maxn = 220;
    int a[maxn], b[maxn], c[maxn], t[maxn];
    int compare(int x[], int y[]){
    if(x[0] < y[0])return -1;
    if(x[0] > y[0])return 1;
    for(int i = x[0]; i > 0; i--){ //越后面的位越大啊
        if(x[i] < y[i])return -1;
        if(x[i] > y[i])return 1;
    }
    return 0;
    }
    void times(int x[], int y[], int k){
    for(int i = 1; i <= x[0]; i++)y[i+k-1] = x[i];
    y[0] = x[0]+k-1;
    }
    int main(){
    string s1, s2;  cin>>s1>>s2;
    a[0] = s1.size();  b[0] = s2.size();
    //bugs:a比b小的情况,就是...如果只剩0的话这个商的长度的也会变成0 错误数据:0 100
    if(a[0]<b[0]||(a[0]==b[0]&&s1<s2)){ cout<<"0\n"; return 0; }
    for(int i = 1; i <= a[0]; i++)a[i] = s1[a[0]-i]-'0';
    for(int i = 1; i <= b[0]; i++)b[i] = s2[b[0]-i]-'0';
    c[0] = a[0]-b[0]+1;
    for(int i = c[0]; i > 0; i--){
        memset(t,0,sizeof(t));
        times(b,t,i);
        while(compare(a,t)>=0){
            c[i]++;
            for(int j = 1; j <= a[0]; j++){
                if(a[j] < t[j]){
                    a[j+1]--;
                    a[j] += 10;
                }
                a[j] -= t[j];
            }
            while(!a[a[0]] && a[0]>1)a[0]--;
        }
    }
    while(!c[c[0]] && c[0]>1)c[0]--;
    for(int i = c[0]; i > 0; i--)cout<<c[i];
    return 0;
    }
```

##    除以13 openjudge27

```c
    //高精除低精,模板

    #include<iostream>
    #include<string>

    using namespace std;
    const int maxn = 110;
    int a[maxn], c[maxn];
    int main(){
       string s;  cin>>s;  c[0]=a[0]=s.size();
       for(int i = 1; i <= a[0]; i++)a[i]=s[a[0]-i]-'0';
       int x = 0;
       for(int i = a[0]; i >= 1; i--){
        c[i] = (a[i]+x*10)/13;
        x = (a[i]+x*10)%13;
    }
       while(!c[c[0]] && c[0]>1)c[0]--;
       for(int i = c[0]; i >= 1; i--)cout<<c[i];
       cout<<"\n"<<x<<"\n";
       return 0;
    }
```