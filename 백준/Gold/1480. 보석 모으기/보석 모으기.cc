#include<iostream>
#include<algorithm>
using namespace std;

int N,M,C;
int dp[10][1<<13][21];  // 가방 인덱스, 방문 여부 비트, 가방 남은 용량
int jewel[13];

int solve(int,int,int);

int main(void){
    cin >> N >> M >> C;
    for(int i=0; i<N; i++) {
        cin >> jewel[i];
    }

    cout << solve(0,0,C) << "\n";
    return 0;
}

int solve(int cur, int visited, int capacity) {
    if(cur == M) {  // 가방 탐색 완료
        return 0;
    }
    if(dp[cur][visited][capacity] != 0) {   // 이미 계산된 값을 반환
        return dp[cur][visited][capacity];
    }

    for(int i=0; i<N; i++)  // 보석을 살펴보며
    {
        if(visited & (1 << i)) {    // 이미 선택했던 보석
            continue;
        }

        if(capacity < jewel[i]) {   // 넣을 수 없는 보석
            dp[cur][visited][capacity] = max(dp[cur][visited][capacity], solve(cur + 1, visited, C));   // 바로 다음 가방으로 넘어가기
        } else {
            dp[cur][visited][capacity] = max(dp[cur][visited][capacity], solve(cur, visited | (1 << i), capacity - jewel[i]) + 1);  // i번째 보석을 cur번째 가방에 넣고, capacity 감소. dp값 1증가
        }
    }
    return dp[cur][visited][capacity];
}