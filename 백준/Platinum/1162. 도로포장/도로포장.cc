#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstring>

using namespace std;

#define MAX_N 10001
#define MAX_K 21
#define INF 1000000000000LL

int N, M, K, from, to, cost;
long long dist[MAX_N][MAX_K];
vector<pair<int, int>> road[MAX_N];

struct Node {
    long long cost;
    int vertex;
    int pavement;
    
    bool operator>(const Node &other) const {
        return cost > other.cost;
    }
};

void dijkstra() {
    priority_queue<Node, vector<Node>, greater<Node>> pq;
    pq.push({0, 1, 0});
    dist[1][0] = 0;

    while (!pq.empty()) {
        Node current = pq.top();
        pq.pop();

        if (current.cost > dist[current.vertex][current.pavement]) {
            continue;
        }

        for (auto &edge : road[current.vertex]) {
            int next_vertex = edge.first;
            long long next_cost = current.cost + edge.second;

            // 포장하지 않는 경우
            if (next_cost < dist[next_vertex][current.pavement]) {
                dist[next_vertex][current.pavement] = next_cost;
                pq.push({next_cost, next_vertex, current.pavement});
            }

            // 포장하는 경우
            if (current.pavement < K && current.cost < dist[next_vertex][current.pavement + 1]) {
                dist[next_vertex][current.pavement + 1] = current.cost;
                pq.push({current.cost, next_vertex, current.pavement + 1});
            }
        }
    }
}

int main() {
    cin >> N >> M >> K;
    for (int i = 0; i < M; ++i) {
        cin >> from >> to >> cost;
        road[from].push_back({to, cost});
        road[to].push_back({from, cost});
    }

    // 초기화
    for (int i = 0; i <= N; ++i) {
        fill(dist[i], dist[i] + MAX_K, INF);
    }

    // 다익스트라 알고리즘 실행
    dijkstra();

    long long answer = INF;
    for (int i = 0; i <= K; ++i) {
        answer = min(answer, dist[N][i]);
    }

    cout << answer << '\n';

    return 0;
}
