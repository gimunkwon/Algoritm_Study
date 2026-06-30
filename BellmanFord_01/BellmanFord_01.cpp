/**
 * 벨만-포드 알고리즘 (Bellman-Ford Algorithm)
 *
 * [핵심 개념]
 * - 단일 출발점 최단경로 알고리즘 (다익스트라와 동일한 목적)
 * - 다익스트라와 달리 음수(negative) 가중치 간선을 처리할 수 있음
 * - 음수 사이클(negative cycle) 존재 여부도 감지 가능
 * - 시간복잡도: O(V * E)  → 다익스트라 O(E log V)보다 느림
 *
 * [다익스트라 vs 벨만-포드]
 * ┌──────────────┬──────────────┬──────────────┐
 * │              │  다익스트라  │  벨만-포드   │
 * ├──────────────┼──────────────┼──────────────┤
 * │ 음수 간선    │      X       │      O       │
 * │ 음수 사이클  │      X       │  감지 가능   │
 * │ 시간복잡도   │ O(E log V)   │   O(V * E)   │
 * │ 방식         │  그리디+PQ   │  완전 완화   │
 * └──────────────┴──────────────┴──────────────┘
 *
 * [알고리즘 동작 원리]
 * 1. 시작 노드의 거리를 0, 나머지는 INF로 초기화
 * 2. (V-1)번 반복하며 모든 간선에 대해 완화(relaxation) 수행
 *    - relaxation: dist[v] > dist[u] + w 이면 dist[v] = dist[u] + w
 * 3. V번째 반복에서도 갱신이 발생하면 → 음수 사이클 존재
 *
 * [왜 V-1번인가?]
 * - 최단경로는 최대 V-1개의 간선을 사용 (사이클이 없을 경우)
 * - V-1번 반복하면 모든 노드에 대한 최단거리가 확정됨
 *
 * [예제 그래프]
 *
 *      2       -3
 *  1 ──── 2 ──── 4
 *  │      │      │
 *  5    -1│      │ 1
 *  │      ▼      │
 *  └───── 3 ─────┘
 *           4
 *
 *  간선 목록 (단방향):
 *  1→2: 2,  1→3: 5,  2→3: -1,  2→4: -3,  3→4: 4,  4→3: 1
 *
 *  시작 노드 1 기준 최단거리:
 *  dist[1] = 0
 *  dist[2] = 2
 *  dist[3] = 1   (1→2→3: 2+(-1)=1)
 *  dist[4] = -1  (1→2→4: 2+(-3)=-1)
 */

#include <iostream>
#include <vector>
#include <climits>
using namespace std;

const int INF = INT_MAX;

struct Edge {
    int u, v, w;
};

int n, m;
vector<Edge> edges;

// 반환값: 음수 사이클 존재 여부 (true = 음수 사이클 있음)
bool bellmanFord(int start, vector<int>& dist)
{
    dist.assign(n + 1, INF);
    dist[start] = 0;

    // V-1번 모든 간선 완화
    for (int i = 0; i < n - 1; i++)
    {
        for (const auto& e : edges)
        {
            if (dist[e.u] == INF) continue;
            if (dist[e.v] > dist[e.u] + e.w)
                dist[e.v] = dist[e.u] + e.w;
        }
    }

    // V번째 반복: 갱신 발생 시 음수 사이클 존재
    for (const auto& e : edges)
    {
        if (dist[e.u] == INF) continue;
        if (dist[e.v] > dist[e.u] + e.w)
            return true;
    }

    return false;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // 예제 그래프 직접 구성
    n = 4;
    m = 6;
    edges = {
        {1, 2,  2},
        {1, 3,  5},
        {2, 3, -1},
        {2, 4, -3},
        {3, 4,  4},
        {4, 3,  1},
    };

    vector<int> dist;
    bool hasNegCycle = bellmanFord(1, dist);

    if (hasNegCycle)
    {
        cout << "음수 사이클 존재\n";
        return 0;
    }

    for (int i = 1; i <= n; i++)
    {
        if (dist[i] == INF)
            cout << "노드 " << i << ": 도달 불가\n";
        else
            cout << "노드 " << i << ": " << dist[i] << "\n";
    }

    return 0;
}

/*
 * [출력 결과]
 * 노드 1: 0
 * 노드 2: 2
 * 노드 3: 1
 * 노드 4: -1
 *
 * [음수 사이클 감지 예시]
 * 만약 4→3 가중치가 -5이면 3→4→3→4... 무한히 줄어드는 음수 사이클 발생
 * → V번째 반복에서 갱신 감지
 *
 * [코딩테스트 활용 패턴]
 * 1. 음수 가중치 간선이 있는 최단경로 → 벨만-포드
 * 2. 음수 사이클 존재 여부 확인 → V번째 반복 체크
 * 3. 모든 쌍 최단경로 + 음수 간선 → 플로이드-워셜
 */
