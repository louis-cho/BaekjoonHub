#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;

#define MAX 1001
#define INF 2e9

int N, M, u, v, w;
vector<pair<int, int>> graph[MAX];
int dist[MAX], max_dist, max_diff = -1;

typedef struct node {
    vector<int> path;
    int cost;
    node() {}

    node(vector<int> path, int cost) {
        this->path = path;
        this->cost = cost;
    }
} node;

struct cmp {
    bool operator()(const node& a, const node& b) {
        return a.cost > b.cost;
    }
};

priority_queue<node, vector<node>, cmp> pq;
vector<int> shortest_path;

void dijkstra(int start, int ignore_u = -1, int ignore_v = -1) {
    fill(dist, dist + MAX, INF);

    vector<int> path;
    path.push_back(start);
    pq.push(node(path, 0));
    dist[start] = 0;

    while (!pq.empty()) {
        auto elem = pq.top();
        pq.pop();

        int current_vertex = elem.path.back();
        int current_cost = elem.cost;

        if (current_cost > dist[current_vertex]) continue;

        for (auto &edge : graph[current_vertex]) {
            int next_vertex = edge.first;
            int next_cost = edge.second;

            if ((current_vertex == ignore_u && next_vertex == ignore_v) ||
                (current_vertex == ignore_v && next_vertex == ignore_u)) {
                continue;
            }

            if (dist[next_vertex] > current_cost + next_cost) {
                dist[next_vertex] = current_cost + next_cost;
                vector<int> new_path(elem.path);
                new_path.push_back(next_vertex);
                pq.push(node(new_path, dist[next_vertex]));
            }
        }
    }
}

int main(void) {
    cin >> N >> M;
    for (int i = 0; i < M; i++) {
        cin >> u >> v >> w;
        graph[u].push_back({v, w});
        graph[v].push_back({u, w});
    }

    dijkstra(1);
    if (dist[N] == INF) {
        cout << -1;
        return 0;
    }

    max_dist = dist[N];
    int current = N;

    while (current != 1) {
        shortest_path.push_back(current);
        for (auto &edge : graph[current]) {
            int next_vertex = edge.first;
            int next_cost = edge.second;
            if (dist[current] == dist[next_vertex] + next_cost) {
                current = next_vertex;
                break;
            }
        }
    }
    shortest_path.push_back(1);
    reverse(shortest_path.begin(), shortest_path.end());

    for (int i = 0; i < shortest_path.size() - 1; i++) {
        int u = shortest_path[i];
        int v = shortest_path[i + 1];
        dijkstra(1, u, v);

        if (dist[N] == INF) {
            max_diff = -1;
            break;
        } else {
            max_diff = max(max_diff, dist[N] - max_dist);
        }
    }

    cout << max_diff;
    return 0;
}
