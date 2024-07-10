#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>

#define MAX_VERTEX  100000
#define MAX_TUBE    101002
using namespace std;

int N, K, M, vertex;
int arr[MAX_TUBE + 1];
vector<int> graph[MAX_TUBE];

void bfs(int start) {
    queue<pair<int, int>> q; // pair<vertex, cost>
    q.push({start, 1});
    arr[start] = 0;

    while (!q.empty()) {
        int curr = q.front().first;
        int cost = q.front().second;
        q.pop();

        if (curr == N) {
            cout << cost << endl;
            return;
        }

        for (auto next : graph[curr]) {
            if (next > MAX_VERTEX && arr[next] > cost + 1) {
                arr[next] = cost + 1;
                q.push({next, cost + 1});
            } else if(next <= MAX_VERTEX && arr[next] > cost) {
                arr[next] = cost;
                q.push({next, cost});
            }
        }
    }

    cout << -1 << endl;
}

int main() {
    cin >> N >> K >> M;

    fill_n(arr, MAX_TUBE, 1e9);

    for (int i = 1; i <= M; i++) {
        for (int j = 0; j < K; j++) {
            cin >> vertex;
            graph[MAX_VERTEX + i].push_back(vertex);
            graph[vertex].push_back(MAX_VERTEX + i);
        }
    }

    bfs(1);

    return 0;
}
