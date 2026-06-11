---
title: "다익스트라(Dijkstra) 알고리즘"
category: "코딩테스트 / 알고리즘"
tags: ["알고리즘", "그래프", "최단경로", "다익스트라", "우선순위큐"]
---

# 다익스트라(Dijkstra) 알고리즘

## 개념

하나의 출발 노드에서 **다른 모든 노드까지의 최단 거리**를 구하는 그리디 기반 알고리즘.  
**음수 가중치가 없는** 가중치 그래프에서 사용한다.

### 핵심 아이디어

매 단계마다 미확정 노드 중 **거리가 가장 짧은 노드를 선택해 확정**하고, 해당 노드의 인접 노드 거리를 갱신(Relaxation)한다.  
음수 가중치가 없으므로, 한 번 확정된 노드는 절대 더 짧은 경로가 생기지 않는다 — 이것이 그리디가 성립하는 이유다.

### 동작 과정 (예시)

```
간선: 1→2(2), 1→3(3), 2→3(1), 2→4(5), 3→4(1), 4→5(2)
출발: 1번 노드
```

| 단계 | 선택 노드 | 1 | 2 | 3 | 4 | 5 |
|------|---------|---|---|---|---|---|
| 초기 | - | **0** | ∞ | ∞ | ∞ | ∞ |
| 1 | 1 확정 | 0 | 2 | 3 | ∞ | ∞ |
| 2 | 2 확정 | 0 | 2 | **3**(2+1) | 7(2+5) | ∞ |
| 3 | 3 확정 | 0 | 2 | 3 | **4**(3+1) | ∞ |
| 4 | 4 확정 | 0 | 2 | 3 | 4 | **6**(4+2) |

최단거리: 1→5 = **6** (1→2→3→4→5)

### 시간 복잡도

| 구현 방식 | 시간 복잡도 |
|---|---|
| 인접 행렬 + 선형 탐색 | O(V²) |
| 인접 리스트 + 우선순위 큐 | O((V+E) log V) |

코딩테스트에서는 **인접 리스트 + 우선순위 큐** 방식을 사용한다.

---

## 구현 (C++)

소스코드: `Dijkstra_01.cpp`

```cpp
#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

typedef pair<int, int> pii; // {가중치, 도착노드}

vector<int> dijkstra(int start, int n, vector<vector<pii>>& graph)
{
    vector<int> dist(n + 1, INT_MAX);
    priority_queue<pii, vector<pii>, greater<pii>> pq; // Min-Heap

    dist[start] = 0;
    pq.push({ 0, start });

    while (!pq.empty())
    {
        auto top = pq.top();
        int cost = top.first, u = top.second;
        pq.pop();

        // 이미 더 짧은 경로로 처리된 노드는 스킵
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
```

### 포인트

- `priority_queue`에 `greater<pii>` 를 넣어 **Min-Heap** 으로 만든다
- 큐에서 꺼낸 `cost > dist[u]` 이면 이미 더 짧은 경로로 확정된 노드이므로 스킵
- 같은 노드가 큐에 여러 번 들어갈 수 있지만, 스킵 덕분에 중복 처리되지 않는다

---

## 타 알고리즘과 비교

| | 다익스트라 | 벨만-포드 | 플로이드-워셜 |
|---|---|---|---|
| 출발점 | 단일 | 단일 | 모든 쌍 |
| 음수 가중치 | 불가 | 가능 | 가능 |
| 시간복잡도 | O((V+E)logV) | O(VE) | O(V³) |
| 코테 빈도 | 매우 높음 | 낮음 | 중간 |

---

## 관련 문제

- 백준 1753 - 최단경로
- 백준 1916 - 최소비용 구하기
- 백준 4485 - 녹색 옷 입은 애가 젤다지?