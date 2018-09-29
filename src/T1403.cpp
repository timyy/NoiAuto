#include <iostream>
#define MAX 10000

using namespace std;


// 构造素数序列primes[]

int makePrimes(int primes[], int num)
{
    int i, j, cnt;
    
    primes[0] = 2;
    primes[1] = 3;
    
//    cout << "Num:" << num << endl;
    for(i = 5, cnt = 2; i < num; i += 2)
    {
        int flag = true;
        for(j = 1; primes[j]*primes[j] <= i; ++j)
        {
            if(i%primes[j] == 0)
            {
                flag = false; 
                break;
            }
        }
        if(flag) {
            primes[cnt++] = i;
//            cout << i << " ";
        }
    }
//    cout << endl << "Cnt:" << cnt << endl;
    return cnt;
}

int main()
{
   int primes[MAX];
   int N;
   int cnt;

   cin >> N;

   cnt = makePrimes(primes,N);
   
//   cout << endl << "Cnt:" << cnt << endl;

   for(int i=1; i<cnt; i++){
//       cout << primes[i] << " ";
        if(primes[i]-primes[i-1] == 2 ){
            cout << primes[i-1] << " " << primes[i] << endl;
        }
   }

   return 0;
}
