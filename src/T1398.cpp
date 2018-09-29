#include <iostream>

using namespace std;

float cost(int item){
    float num;
    num = (item>0?item-1:0) / 70 + 1;
    return(0.1 * num);
}
int main()
{
    int n;
    int item;
    float sum=0.0;

    //cout << "Input num:";
    cin >> n;    
    for(int i=0; i< n; i++){
        cin >> item;
        sum += cost(item);
    }
    cout << sum;
}