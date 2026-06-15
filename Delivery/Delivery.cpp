#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;


using pil = pair<int,int>;
// N : 마을 갯수 K: 최대 허용 배달 시간 road: 도시와 연결된 도로 정보
int solution(int N, vector<vector<int>> road, int K) 
{
    vector<vector<pil>> v_graph(N + 1);
    // 인접 배열 리스트 정리
    sort(road.begin(), road.end());
    
    // TODO::Fix
    for (int i = 0; i < (int)road.size(); i++)
    {
        v_graph[road[i][0]].push_back({road[i][2],road[i][1]});
        v_graph[road[i][1]].push_back({road[i][2],road[i][0]});
    }
    
    // 방문 배열 무한대 초기화
    vector<int> visited(N + 1, INT_MAX);
    visited[1] = 0;
    
    // 우선순위 큐에 삽입
    priority_queue<pil, vector<pil>, greater<pil>> pq;
    pq.push({0, 1});

    while (!pq.empty())
    {
        auto top = pq.top();
        int cost = top.first, currentnode = top.second;
        pq.pop();
        
        if (cost > visited[currentnode]) continue;
        
        for (int i = 0; i < (int)v_graph[currentnode].size(); i++)
        {
            int weight = v_graph[currentnode][i].first;
            int linked_node = v_graph[currentnode][i].second;
            
            if (cost + weight < visited[linked_node])
            {
                visited[linked_node] = cost + weight;
                pq.push({visited[linked_node],linked_node});
            }
        }
        
    }
    
    int enable_deliver_count = 0;
    
    for (int i : visited)
    {
        if (i <= K)
        {
            enable_deliver_count++;
        }
    }
    
    cout << enable_deliver_count << "\n";

    return enable_deliver_count;
}

int main()
{
    int answer = solution(5, {{1, 2, 1}, {2, 3, 3}, {5, 2, 2}, {1, 4, 2}, {5, 3, 1}, {5, 4, 2}},3);
    
    cout << answer << "\n";
}