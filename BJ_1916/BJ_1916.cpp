/**
 * 백준 1916 - 최소비용 구하기 (Silver 1)
 *
 * 문제 URL: https://www.acmicpc.net/problem/1916
 *
 * [문제 설명]
 * N개의 도시가 있다. 그리고 한 도시에서 출발하여 다른 도시에 도착하는 M개의 버스가 있다.
 * 우리는 A번째 도시에서 B번째 도시까지 가는데 드는 버스 비용을 최소화 시키려고 한다.
 * A번째 도시에서 B번째 도시까지 가는데 드는 최소비용을 출력하여라.
 * 항상 시작점에서 도착점으로의 경로가 존재한다.
 *
 * [입력]
 * 첫째 줄에 도시의 개수 N (1 ≤ N ≤ 1,000)
 * 둘째 줄에 버스의 개수 M (1 ≤ M ≤ 100,000)
 * 셋째 줄부터 M+2줄까지 버스의 출발 도시, 도착 도시, 한 번 타는데 필요한 비용이 주어진다.
 * 버스의 비용은 0보다 크거나 같고, 100,000보다 작은 정수이다. (단방향)
 * M+3번째 줄에 출발점의 번호와 도착점의 번호가 주어진다.
 *
 * [출력]
 * 첫째 줄에 출발 도시에서 도착 도시까지 가는데 드는 최소 비용을 출력한다.
 *
 * [예제 입력 1]
 * 5
 * 8
 * 1 2 2
 * 1 3 3
 * 1 4 1
 * 1 5 10
 * 2 4 2
 * 3 4 1
 * 3 5 1
 * 4 5 3
 * 1 5
 *
 * [예제 출력 1]
 * 4
 *
 * [제한]
 * - 시간 제한: 0.4초
 * - 메모리 제한: 256MB
 * - 1 ≤ N ≤ 1,000
 * - 1 ≤ M ≤ 100,000
 * - 버스 비용: 0 이상 100,000 미만의 정수
 * - 항상 시작점 → 도착점 경로 존재
 */

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int INF = 1e9;

using pil = pair<int,int>;


int Dijkstra(vector<vector<pil>>& graph, int startnode, int endnode)
{
    vector<int> distance(graph.size(), INF);
    
    distance[startnode] = 0;
    
    priority_queue<pil,vector<pil>,greater<pil>> pq;
    
    pq.push({distance[startnode],startnode});

    while (!pq.empty())
    {
        auto top = pq.top();
        int cost = top.first, next_node = top.second;
        pq.pop();
        
        if (cost > distance[next_node]) continue;
        
        // 가중치를 최소값으로 업데이트
        for (auto i : graph[next_node])
        {
            int weight = i.first, node = i.second;
            
            if (weight + cost < distance[node])
            {
                distance[node] = weight + cost;
                pq.push({weight + cost, node});
            }
        }
    }
    
    return distance[endnode];
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N,M;
    cin >> N >> M;
    
    vector<vector<pil>> graph(N + 1);
    
    for (int i = 0; i < M; i++)
    {
        int start,end,cost;
        cin >> start >> end >> cost;
        
        graph[start].push_back({cost, end});
    }
    
    int start_city,end_city;
    cin >> start_city >> end_city;
    
    //TODO::Dijkstra
    int distance = Dijkstra(graph,start_city, end_city);
    
    cout << distance;
    
    

    return 0;
}