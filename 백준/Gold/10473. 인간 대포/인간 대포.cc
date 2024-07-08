#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
#include<cmath>
using namespace std;

double sx,sy,ex,ey,x,y;
int n;
vector<pair<double,double>> canon;
double dist[102];

typedef struct node {
    double dist;
    int index;

    node(double dist, int index) {
        this->dist = dist;
        this->index = index;
    }
} node;

struct cmp {
    bool operator()(const node& a, const node& b) {
        return a.dist > b.dist;
    }
};

priority_queue<node, vector<node>, cmp> pq;

double cal(int from, int to) {

    pair<double,double> from_vertex = canon.at(from);
    pair<double,double> to_vertex = canon.at(to);

    double x = fabs(from_vertex.first - to_vertex.first);
    double y = fabs(from_vertex.second - to_vertex.second);
    double val = hypot(x,y);

    return val;
}

int main(void){


    cin >> sx >> sy;    // 시작 위치
    cin >> ex >> ey;    // 종료 위치

    canon.push_back({sx, sy});

    cin >> n;
    for(int i=0; i<n; i++) {
        cin >> x >> y;
        canon.push_back({x,y});
    }
    canon.push_back({ex, ey});

    fill_n(&(dist[0]), 102, 2e9);
    dist[0] = 0;
    pq.push(node(0, 0));
    bool first = true;
    while(!pq.empty())
    {
        auto elem = pq.top();
        pq.pop();

        int cidx = elem.index;
        double cv = elem.dist;

        if(dist[cidx] < cv) {
            continue;
        }

        for(int i=1; i<=n+1; i++)
        {
            if(i == cidx)
                continue;
            double val = cal(cidx, i);
            double nv;
            if(first)
                nv = val / 5.0;
            else
                nv = min(val / 5.0, fabs(val - 50) / 5.0 + 2.0);
            if(cv + nv < dist[i]) {
                dist[i] = cv + nv;
                pq.push(node(cv + nv, i));
            }
        }
        first =false;
    }


    cout << fixed;
    cout.precision(6);
    cout << dist[n+1];
    return 0;
}