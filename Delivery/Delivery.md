---
title: "배달 (프로그래머스 Lv.2)"
category: "코딩테스트 / 알고리즘"
tags: ["알고리즘", "그래프", "최단경로", "다익스트라", "프로그래머스"]
---

# 배달 (프로그래머스 Lv.2)

문제 링크: https://school.programmers.co.kr/learn/courses/30/lessons/12978

## 문제 요약

N개의 마을과 마을을 잇는 도로 정보가 주어진다.  
1번 마을에서 출발해 **배달 가능 시간 K 이하**로 도달할 수 있는 마을의 수를 구한다.

- 도로는 **양방향**, 같은 두 마을 사이에 여러 도로 존재 가능
- 항상 1번 마을에서 모든 마을로 이동 가능한 경로 존재

## 풀이 접근

1번 마을을 출발점으로 **다익스트라**를 수행해 모든 마을까지의 최단 거리를 구한다.  
이후 최단 거리가 K 이하인 마을의 수를 카운트한다.

## 핵심 포인트

**출발 노드 거리 초기화를 반드시 해야 한다.**

```cpp
vector<int> visited(N + 1, INT_MAX);
visited[1] = 0;  // 누락 시 1번 마을이 카운트에서 빠질 수 있음
```

`visited[1] = 0`을 설정하지 않으면, Dijkstra가 돌면서 이웃 노드를 거쳐 1번으로 돌아오는  
루프 경로 비용이 `visited[1]`에 기록된다. 이 값이 K를 초과하면 1번 마을이 카운트에서 누락된다.

## 풀이 코드

소스코드: `Delivery.cpp`

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

using pil = pair<int, int>;

int solution(int N, vector<vector<int>> road, int K)
{
    vector<vector<pil>> v_graph(N + 1);

    for (int i = 0; i < (int)road.size(); i++)
    {
        v_graph[road[i][0]].push_back({road[i][2], road[i][1]});
        v_graph[road[i][1]].push_back({road[i][2], road[i][0]});
    }

    vector<int> visited(N + 1, INT_MAX);
    visited[1] = 0;

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
                pq.push({visited[linked_node], linked_node});
            }
        }
    }

    int count = 0;
    for (int i = 1; i <= N; i++)
    {
        if (visited[i] <= K) count++;
    }

    return count;
}
```

## 실수 포인트 정리

| 실수 | 원인 | 해결 |
|------|------|------|
| 정확도 87.5점 | `visited[1] = 0` 누락 | 출발 노드 거리 명시적으로 0 초기화 |