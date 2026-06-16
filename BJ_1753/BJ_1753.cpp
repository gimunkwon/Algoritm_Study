/**
 * 백준 1753 - 최단경로 (골드 5)
 * 
 * 문제 URL: https://www.acmicpc.net/problem/1753
 * 
 * [문제 설명]
 * 방향그래프가 주어지면 주어진 시작점에서 다른 모든 정점으로의 최단 경로를 구하는 프로그램을 작성하시오. 
 * 모든 간선의 가중치는 10 이하의 자연수이다.
 * 
 * [입력]
 * 첫째 줄에 정점의 개수 V와 간선의 개수 E가 주어진다. (1 ≤ V ≤ 20,000, 1 ≤ E ≤ 300,000) 
 * 모든 정점에는 1부터 V까지 번호가 매겨져 있다고 가정한다. 
 * 둘째 줄에는 시작 정점의 번호 K(1 ≤ K ≤ V)가 주어진다. 
 * 셋째 줄부터 E개의 줄에 걸쳐 각 간선을 나타내는 세 개의 정수 (u, v, w)가 순서대로 주어진다. 
 * 이는 u에서 v로 가는 가중치 w인 간선이 존재한다는 뜻이다. u와 v는 서로 다르며 w는 10 이하의 자연수이다.
 * 서로 다른 두 정점 사이에 여러 개의 간선이 존재할 수도 있음에 유의한다.
 * 
 * [출력]
 * 첫째 줄부터 V개의 줄에 걸쳐, i번째 줄에 i번 정점으로의 최단 경로의 경로값을 출력한다. 
 * 시작점 자신은 0을 출력하고, 경로가 존재하지 않는 경우에는 INF를 출력한다.
 * 
 * [예제 입력 1]
 * 5 6
 * 1
 * 5 1 1
 * 1 2 2
 * 1 3 3
 * 2 3 4
 * 2 4 5
 * 3 4 6
 * 
 * [예제 출력 1]
 * 0
 * 2
 * 3
 * 7
 * INF
 */

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int INF = 1e9; // 충분히 큰 값 설정 (V * 10보다 큰 값)

using pil = pair<int,int>;

vector<int> Dijkstra(int startnode, int node, vector<vector<pil>>& graph)
{
    vector<int> distance(node + 1, INF);
    distance[startnode] = 0;
    
    priority_queue<pil, vector<pil>, greater<pil>> pq;
    pq.push({distance[startnode],startnode});

    while (!pq.empty())
    {
        auto top = pq.top();
        int cost = top.first, node = top.second;
        pq.pop();
        
        if (cost > distance[node]) continue;
        
        for (const auto& edge : graph[node])
        {
            int next_node = edge.first;  // graph[node]의 first는 다음 노드 번호
            int weight = edge.second;   // graph[node]의 second는 간선 가중치
            
            if (cost + weight < distance[next_node])
            {
                distance[next_node] = cost + weight;
                pq.push({distance[next_node], next_node}); // pq에는 {누적거리, 노드번호} 순으로 push
            }
        }
    }
    
    return distance;
}

int main() 
{
    // 빠른 입출력
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    // TODO: 백준 1753번 최단경로 풀이 구현하기
    
    int V,E;
    cin >> V >> E;
    
    int start;
    cin >> start;
    
    vector<vector<pil>> graph(V + 1);
    
    for (int i = 0; i < E; i++)
    {
        int node1,node2,weight;
        cin >> node1 >> node2 >> weight;
        
        graph[node1].push_back({node2,weight});
    }
    
    vector<int> distance = Dijkstra(start,V,graph);
    
    for (int i = 1; i < distance.size(); i++)
    {
        if (distance[i] == INF)
        {
            cout << "INF" << "\n";
        }
        else
        {
            cout << distance[i] << "\n";
        }
    }
    
    
    return 0;
}
