#include<iostream>
using namespace std;

int N;
long long DP[100][1024][10];    // [N번째 자리] [사용한 숫자 비트마스크] [마지막에 사용한 숫자]
const long long MOD = 1000000000;

int main(void){
    cin >> N;

    // 초기화: 길이 1짜리 계단 수 (1부터 9까지)
    for(int i = 1; i < 10; i++) {
        DP[0][1 << i][i] = 1;
    }

    for(int i = 0; i < N-1; i++) {                      // 길이 i짜리를 구하자
        for(int j = 0; j < 1024; j++) {               // 방문한 모든 경우에 대해
            for(int k = 0; k < 10; k++) {             // 마지막으로 사용한 숫자
                if(DP[i][j][k] == 0) continue;
                // xxxxk는 xxx(k-1)k 혹은 xxx(k+1)k
                if(k-1 >= 0) {
                    DP[i+1][j | (1 << (k-1))][k-1] += DP[i][j][k];  // xxx(k-1)(k)를 추가
                    DP[i+1][j | (1 << (k-1))][k-1] %= MOD;
                }
                if(k+1 < 10) {
                    DP[i+1][j | (1 << (k+1))][k+1] += DP[i][j][k]; // xxx(k+1)(k)를 추가
                    DP[i+1][j | (1 << (k+1))][k+1] %= MOD;
                }
            }
        }
    }

    long long answer = 0;

    // 결과 집계: 길이 N짜리 계단 수 중에서 0부터 9까지 모두 사용한 경우
    for(int i = 0; i < 10; i++) {
        answer += DP[N-1][1023][i];
        answer %= MOD;
    }

    cout << answer << "\n";
    return 0;
}
