/**
 * 백준 1854 - K번째 최단경로 찾기 (Gold 3)
 *
 * 문제 URL: https://www.acmicpc.net/problem/1854
 *
 * [문제 설명]
 * n개의 도시가 있다. 도시와 도시 사이에는 도로가 있고, 길이가 있다.
 * 1번 도시에서 출발해 나머지 각 도시까지의 K번째 최단경로를 구하여라.
 * 최단경로는 경로 상의 같은 도시를 여러 번 방문해도 되며,
 * 두 경로가 같은 길이라도 다른 경로로 친다.
 *
 * [입력]
 * 첫째 줄: n, m, k (도시 수, 도로 수, 몇 번째 최단경로)
 *   - 1 ≤ n ≤ 1,000
 *   - 0 ≤ m ≤ 2,000,000
 *   - 1 ≤ k ≤ 1,000
 * 둘째 줄부터 m+1번째 줄: 단방향 도로 정보 (u v w)
 *   - u에서 v로 가는 가중치 w (1 ≤ w ≤ 1,000)
 *
 * [출력]
 * 1번 도시에서 1번 도시까지 포함, 각 도시(1~n)까지의 K번째 최단경로를 한 줄에 하나씩.
 * K번째 최단경로가 없으면 -1 출력.
 *
 * [예제 입력 1]
 * 5 10 2
 * 1 2 2
 * 1 3 4
 * 1 4 1
 * 1 5 10
 * 2 4 3
 * 2 3 2
 * 3 4 2
 * 3 5 1
 * 4 5 3
 * 4 2 2
 *
 * [예제 출력 1]
 * 0
 * 4
 * 6
 * 4
 * 7
 *
 * [힌트]
 * - dist[v]: 노드 v까지 도달한 거리들을 최대 k개 저장하는 최대힙(max priority_queue)
 * - dist[v]의 크기가 k보다 작으면 새 거리를 무조건 추가
 * - dist[v]의 크기가 k이고 top > 새 거리이면 → pop 후 push (더 좋은 경로 발견)
 * - dist[v]의 크기가 k이고 top ≤ 새 거리이면 → 무시 (이미 k번 이하 비용 경로 있음)
 * - 최종적으로 dist[v].size() == k이면 top이 k번째 최단경로, 아니면 -1
 */

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

using pil = pair<int, int>;

int n, m, k;
vector<vector<pil>> graph;

void dijkstra()
{
    // TODO: dist 배열 초기화 (각 노드마다 최대힙)
    vector<priority_queue<int>> dist(n + 1);
    dist[1].push(0);
    priority_queue<pil, vector<pil>, greater<pil>> pq;
    pq.push({0,1});
    // TODO: 다익스트라 수행
    while (!pq.empty()) 
    {
        auto top = pq.top();
        int cost = top.first, next_node = top.second;
        pq.pop();
        
        if ((int)dist[next_node].size() == k && dist[next_node].top() <= cost) continue;
        
        for (auto i : graph[next_node])
        {
            int weight = i.first, node = i.second;
            int new_cost = weight + cost;
            
            if ((int)dist[node].size() < k || dist[node].top() > new_cost)
            {
                if ((int)dist[node].size() == k)
                {
                    dist[node].pop();
                }
                dist[node].push(new_cost);
                pq.push({new_cost,node});
            }
        }
    }

    // TODO: 각 도시 k번째 최단경로 출력
    for (int i = 1; i < dist.size(); i++)
    {
        if (dist[i] == INT_MAX)
        {
            cout << -1 <<"\n";
        }
        else
        {
            cout << dist[i] << "\n";
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m >> k;

    graph.resize(n + 1);

    for (int i = 0; i < m; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u].push_back({w, v});
    }

    dijkstra();

    return 0;
}
