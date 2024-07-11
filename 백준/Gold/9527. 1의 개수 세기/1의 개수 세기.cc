#include<iostream>
using namespace std;

#define MAX 55

long long pow2[MAX];
long long A,B;


long long countOne(long long num) {
    long long ret = num & 1;

    for(int i=MAX-1; i>0; i--) {
        long long n = (1LL << i);
        if(num & n) {                           // i번째 비트가 켜져있으면
            ret += pow2[i-1] + (num - n + 1);   // i번째 비트가 켜진 수보다 작은 수의 조합 + i번째 비트가 켜진 횟수
            num -= n;                           // i번째 비트 끄기
        }
    }

    return ret;
}

int main(void){
    cin >> A >> B;

    pow2[0] = 1;
    for(int i=1; i<MAX; i++) {
        pow2[i] = 2 * pow2[i-1] + (1LL << i);
    }

    cout << countOne(B) - countOne(A - 1);
    return 0;
}