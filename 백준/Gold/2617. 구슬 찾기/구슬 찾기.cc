#include<iostream>
#include<vector>
#include<stack>
using namespace std;

int N,M,u,v;
int graph[101][101];
int cnt, reverse_cnt;
bool visited[101], reverse_visited[101];


stack<int> st;
stack<int> reverse_st;

int main(void){



    cin >> N >> M;
    int limit_bound = (N + 1) / 2;
    int answer = 0;
    for(int i=0; i<M; i++)
    {
        cin >> u >> v;
        graph[u][v] = 1;
        graph[v][u] = -1;
    }

    for(int i=1; i<=N; i++)
    {
        st.push(i);
        reverse_st.push(i);
        
        cnt = 0;
        reverse_cnt = 0;

        fill_n(visited, 101, false);
        fill_n(reverse_visited, 101, false);

        while(!st.empty())
        {
            auto elem = st.top();
            st.pop();

            
            int current_vertex = elem;

            visited[current_vertex] = true;


            for(int next_vertex = 1; next_vertex <= N; next_vertex++)
            {
                if(next_vertex == current_vertex)
                    continue;
                if(graph[current_vertex][next_vertex] > 0 && !visited[next_vertex]) {
                    visited[next_vertex] = true;
                    cnt++;
                    st.push(next_vertex);
                }
            }
        }

        while(!reverse_st.empty())
        {
            auto elem = reverse_st.top();
            reverse_st.pop();

            
            int current_vertex = elem;
            reverse_visited[current_vertex] = true;


            for(int next_vertex = 1; next_vertex <= N; next_vertex++)
            {
                if(next_vertex == current_vertex)
                    continue;
                if(graph[current_vertex][next_vertex] < 0 && !reverse_visited[next_vertex]) {
                    reverse_visited[next_vertex] = true;
                    reverse_cnt++;
                    reverse_st.push(next_vertex);
                }
            }
        }

        if(cnt >= limit_bound || reverse_cnt >= limit_bound)
            answer++;
    }




    cout << answer;


    return 0;
}