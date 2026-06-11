#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

// {가중치, 도착노드}
typedef pair<int, int> pii;

// -------------------------------------------------------
// 다익스트라 - 우선순위 큐(Min-Heap) 방식
// 시간복잡도: O((V + E) log V)
//
// start : 출발 노드
// n     : 전체 노드 수
// graph : 인접 리스트 graph[u] = { {w, v}, ... }
// 반환  : dist[i] = start에서 i까지의 최단 거리
// -------------------------------------------------------
vector<int> dijkstra(int start, int n, vector<vector<pii>>& graph)
{
    vector<int> dist(n + 1, INT_MAX);
    // 우선순위 큐: {거리, 노드}, 거리가 작은 것부터 꺼냄
    priority_queue<pii, vector<pii>, greater<pii>> pq;

    dist[start] = 0;
    pq.push({ 0, start });

    while (!pq.empty())
    {
        auto top = pq.top();
        int cost = top.first, u = top.second;
        pq.pop();

        // 큐에서 꺼낸 거리가 이미 갱신된 값보다 크면 스킵
        // (같은 노드가 여러 번 큐에 들어갈 수 있기 때문)
        if (cost > dist[u]) continue;

        for (int i = 0; i < (int)graph[u].size(); i++)
        {
            int w = graph[u][i].first;
            int v = graph[u][i].second;
            if (dist[u] + w < dist[v])
            {
                dist[v] = dist[u] + w;
                pq.push({ dist[v], v });
            }
        }
    }

    return dist;
}

int main()
{
    // 예시 그래프 (노드 5개, 간선 6개)
    //
    //    2       5
    // 1 --→ 2 --→ 4
    // |     |
    // 3↓   1↓
    // |     |
    // 3 --→ 4 --→ 5
    //    1       2
    //
    // 노드: 1~5
    // 간선: 1→2(2), 1→3(3), 2→3(1), 2→4(5), 3→4(1), 4→5(2)

    int n = 5; // 노드 수
    vector<vector<pii>> graph(n + 1);

    // graph[출발].push_back({가중치, 도착})
    graph[1].push_back({ 2, 2 });
    graph[1].push_back({ 3, 3 });
    graph[2].push_back({ 1, 3 });
    graph[2].push_back({ 5, 4 });
    graph[3].push_back({ 1, 4 });
    graph[4].push_back({ 2, 5 });

    int start = 1;
    vector<int> dist = dijkstra(start, n, graph);

    cout << "노드 " << start << "에서 각 노드까지의 최단 거리:" << "\n";
    for (int i = 1; i <= n; i++)
    {
        if (dist[i] == INT_MAX)
            cout << "노드 " << i << " : 도달 불가" << "\n";
        else
            cout << "노드 " << i << " : " << dist[i] << "\n";
    }

    return 0;
}

// -------------------------------------------------------
// 기대 출력:
//   노드 1 : 0
//   노드 2 : 2
//   노드 3 : 3  (1→2→3 = 2+1, 1→3 = 3 이므로 동일, 둘 다 3)
//   노드 4 : 4  (1→2→3→4 = 2+1+1 = 4)
//   노드 5 : 6  (1→2→3→4→5 = 4+2 = 6)
// -------------------------------------------------------