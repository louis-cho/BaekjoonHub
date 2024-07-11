#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <limits.h>

using namespace std;

int main(void) {
    while (true) {
        int N, M;
        int S, D;
        int U, V, P;

        cin >> N >> M;
        if (N == 0 && M == 0)
            break;

        cin >> S >> D;

        vector<pair<int, int>> graph[501];
        for (int i = 0; i < M; i++) {
            cin >> U >> V >> P;
            graph[U].push_back({V, P});
        }

        // 최단 거리 및 경로 역추적을 위한 배열
        vector<int> dist(N + 1, INT_MAX);
        vector<vector<int>> prev(N + 1);
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        
        dist[S] = 0;
        pq.push({0, S});

        while (!pq.empty()) {
            int current_dist = pq.top().first;
            int current_vertex = pq.top().second;
            pq.pop();

            if (current_dist > dist[current_vertex]) continue;

            for (auto &edge : graph[current_vertex]) {
                int next_vertex = edge.first;
                int next_cost = edge.second;

                if (dist[next_vertex] > current_dist + next_cost) {
                    dist[next_vertex] = current_dist + next_cost;
                    pq.push({dist[next_vertex], next_vertex});
                    prev[next_vertex].clear();
                    prev[next_vertex].push_back(current_vertex);
                } else if (dist[next_vertex] == current_dist + next_cost) {
                    prev[next_vertex].push_back(current_vertex);
                }
            }
        }

        if (dist[D] == INT_MAX) {
            cout << "-1\n";
            continue;
        }

        // 최단 경로 간선을 추적하여 제외 목록에 추가
        map<pair<int, int>, bool> exclude;
        queue<int> q;
        q.push(D);

        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (int u : prev[v]) {
                if (!exclude[{u, v}]) {
                    exclude[{u, v}] = true;
                    q.push(u);
                }
            }
        }

        // 두 번째 최단 경로 찾기
        vector<int> second_dist(N + 1, INT_MAX);
        second_dist[S] = 0;
        pq.push({0, S});
        
        int second_shortest_dist = INT_MAX;

        while (!pq.empty()) {
            int current_dist = pq.top().first;
            int current_vertex = pq.top().second;
            pq.pop();

            if (current_vertex == D && current_dist > dist[D]) {
                second_shortest_dist = current_dist;
                break;
            }

            if (current_dist > second_dist[current_vertex]) continue;

            for (auto &edge : graph[current_vertex]) {
                int next_vertex = edge.first;
                int next_cost = edge.second;

                if (exclude.find({current_vertex, next_vertex}) != exclude.end()) continue;

                if (second_dist[next_vertex] > current_dist + next_cost) {
                    second_dist[next_vertex] = current_dist + next_cost;
                    pq.push({second_dist[next_vertex], next_vertex});
                }
            }
        }

        if (second_shortest_dist != INT_MAX)
            cout << second_shortest_dist << "\n";
        else
            cout << "-1\n";
    }
    return 0;
}
