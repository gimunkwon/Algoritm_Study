---
title: "벨만-포드 알고리즘 (Bellman-Ford)"
category: "코딩테스트 / 알고리즘"
tags: ["알고리즘", "최단경로", "벨만-포드", "음수 간선", "그래프"]
---

## 개요

벨만-포드(Bellman-Ford)는 **단일 출발점 최단경로** 알고리즘이다.  
다익스트라와 달리 **음수 가중치 간선**을 처리할 수 있으며, **음수 사이클** 존재 여부도 감지할 수 있다.

---

## 다익스트라 vs 벨만-포드

| 항목 | 다익스트라 | 벨만-포드 |
|---|---|---|
| 음수 간선 | 불가 | 가능 |
| 음수 사이클 | 불가 | 감지 가능 |
| 시간복잡도 | O(E log V) | O(V × E) |
| 방식 | 그리디 + 우선순위 큐 | 전체 간선 반복 완화 |

---

## 핵심 아이디어

### 완화 (Relaxation)

모든 간선 `(u → v, 가중치 w)`에 대해 아래 조건을 확인한다.

```
if dist[v] > dist[u] + w:
    dist[v] = dist[u] + w
```

이 과정을 **V-1번** 반복하면 모든 노드의 최단거리가 확정된다.

### 왜 V-1번인가?

- 사이클 없는 최단경로는 최대 **V-1개의 간선**을 사용한다.
- 1번 완화할 때마다 최소 1개의 간선을 확정할 수 있으므로, V-1번이면 모든 경로 탐색 완료.

### 음수 사이클 감지

V번째 완화에서도 갱신이 발생한다면, 사이클을 돌수록 거리가 줄어드는 **음수 사이클**이 존재한다는 뜻이다.

---

## 알고리즘 순서

```
1. dist[start] = 0, 나머지 dist[] = INF 초기화
2. V-1번 반복:
     모든 간선 (u, v, w)에 대해:
       if dist[u] ≠ INF and dist[v] > dist[u] + w:
         dist[v] = dist[u] + w
3. 한 번 더 전체 간선 순회:
     갱신 발생 → 음수 사이클 존재
```

---

## 예제

```
그래프 (단방향):
1→2: 2,  1→3: 5,  2→3: -1,  2→4: -3,  3→4: 4,  4→3: 1
```

| 반복 | dist[1] | dist[2] | dist[3] | dist[4] |
|---|---|---|---|---|
| 초기 | 0 | INF | INF | INF |
| 1회 | 0 | 2 | 1 | -1 |
| 2회 | 0 | 2 | 0 | -1 |
| 3회 (V-1=3) | 0 | 2 | 0 | -1 |

최종 결과:
- 1번 노드: 0
- 2번 노드: 2
- 3번 노드: 1 (1→2→3: 2-1=1)
- 4번 노드: -1 (1→2→4: 2-3=-1)

---

## 구현 코드 (C++)

```cpp
#include <iostream>
#include <vector>
#include <climits>
using namespace std;

const int INF = INT_MAX;

struct Edge { int u, v, w; };

// 반환값: 음수 사이클 존재 여부
bool bellmanFord(int n, int start, vector<Edge>& edges, vector<int>& dist)
{
    dist.assign(n + 1, INF);
    dist[start] = 0;

    for (int i = 0; i < n - 1; i++)
    {
        for (const auto& e : edges)
        {
            if (dist[e.u] == INF) continue;
            if (dist[e.v] > dist[e.u] + e.w)
                dist[e.v] = dist[e.u] + e.w;
        }
    }

    // 음수 사이클 감지
    for (const auto& e : edges)
    {
        if (dist[e.u] == INF) continue;
        if (dist[e.v] > dist[e.u] + e.w)
            return true;
    }

    return false;
}
```

---

## 간선 표현: struct vs tuple (C++17)

에지 리스트를 표현할 때 위 코드처럼 `struct`를 쓸 수도 있고, 책에서처럼 `tuple`을 쓸 수도 있다. 코딩테스트 환경이 C++17이라면 `tuple` + structured binding으로 아래처럼 간결하게 쓸 수 있다.

```cpp
#include <tuple>

vector<tuple<int, int, int>> edges; // {u, v, w}
edges.push_back({1, 2, 2});

// C++17 structured binding
for (const auto& [u, v, w] : edges)
{
    if (dist[u] == INF) continue;
    if (dist[v] > dist[u] + w)
        dist[v] = dist[u] + w;
}
```

| 방식 | 장점 | 단점 |
|---|---|---|
| `struct Edge { int u, v, w; }` | 필드 이름이 있어 가독성 높음, 복기 시 헷갈리지 않음 | 타입 정의 코드 필요 |
| `tuple<int,int,int>` | 정렬(`sort`)이 필요한 알고리즘(예: 크루스칼)에서 기본 비교연산이 바로 동작 | C++17 미만에서는 `get<0>(e)` 식으로 접근해야 해서 가독성 저하 |

벨만-포드는 간선을 정렬할 필요가 없으므로 `struct`가 가독성 면에서 더 적합하지만, tuple + structured binding도 C++17 환경에서는 충분히 실전적인 선택이다.

---

## 코딩테스트 활용 패턴

| 상황 | 알고리즘 |
|---|---|
| 양수 간선만, 최단경로 | 다익스트라 |
| 음수 간선 포함, 최단경로 | **벨만-포드** |
| 음수 사이클 감지 필요 | **벨만-포드** (V번째 반복 확인) |
| 모든 쌍 최단경로 | 플로이드-워셜 |

---

## 주의사항

- `dist[u] == INF`인 경우 완화를 건너뛰어야 한다. `INF + w`가 오버플로우를 일으킬 수 있기 때문.
- 간선이 입력 순서대로 정렬되어 있지 않아도 V-1번이면 항상 수렴한다.
- 음수 사이클이 있는 노드에서 도달 가능한 노드의 최단거리는 정의되지 않는다.
