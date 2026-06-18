#include <iostream>
#include <vector>
#include <stack>
using namespace std;

// -------------------------------------------------------
// DFS (Depth-First Search) - 깊이 우선 탐색
//
// 시작 노드에서 출발해 한 방향으로 최대한 깊이 탐색한 뒤,
// 더 이상 갈 곳이 없으면 직전 노드로 되돌아가는 방식.
//
// 시간복잡도: O(V + E)  (인접 리스트 기준)
//             O(V²)     (인접 행렬 기준)
// 공간복잡도: O(V)      (재귀 스택 또는 명시적 스택)
//
// 사용 상황
//   - 경로 존재 여부 탐색
//   - 연결 요소(Connected Component) 개수 파악
//   - 사이클 감지
//   - 위상 정렬 (역방향 DFS)
//   - 백트래킹 (순열/조합/미로)
// -------------------------------------------------------

// -------------------------------------------------------
// [방법 1] 재귀(Recursive) DFS
//
// 동작 원리:
//   1. 현재 노드를 방문 표시
//   2. 인접 노드 중 미방문 노드를 재귀 호출
//   3. 호출 스택이 자동으로 되돌아가는 역할을 함
//
// 주의: 그래프가 매우 깊으면 스택 오버플로 발생 가능
// -------------------------------------------------------
void dfs_recursive(int node, vector<vector<int>>& graph, vector<bool>& visited)
{
    visited[node] = true;
    cout << node << " ";

    for (int next : graph[node])
    {
        if (!visited[next])
            dfs_recursive(next, graph, visited);
    }
}

// -------------------------------------------------------
// [방법 2] 스택(Stack) DFS
//
// 동작 원리:
//   1. 시작 노드를 스택에 push
//   2. 스택이 빌 때까지:
//      a. top을 꺼내 방문 처리
//      b. 인접 미방문 노드를 스택에 push
//
// 재귀 DFS와 탐색 순서가 다를 수 있음
// (스택에 넣는 순서 역방향 → 인접 리스트 순방향 탐색과 동일하게 맞추려면 역순 push)
// -------------------------------------------------------
void dfs_stack(int start, vector<vector<int>>& graph, vector<bool>& visited)
{
    stack<int> st;
    st.push(start);

    while (!st.empty())
    {
        int node = st.top();
        st.pop();

        if (visited[node]) continue;
        visited[node] = true;
        cout << node << " ";

        // 인접 리스트 순서와 동일하게 탐색하려면 역순으로 push
        for (int i = (int)graph[node].size() - 1; i >= 0; i--)
        {
            if (!visited[graph[node][i]])
                st.push(graph[node][i]);
        }
    }
}

int main()
{
    // 예시 그래프 (무방향, 노드 6개)
    //
    //   1 - 2 - 4
    //   |   |
    //   3   5 - 6
    //
    // 간선: 1-2, 1-3, 2-4, 2-5, 5-6

    int n = 6;
    vector<vector<int>> graph(n + 1);

    // 무방향 간선: graph[u].push_back(v), graph[v].push_back(u)
    graph[1].push_back(2); graph[2].push_back(1);
    graph[1].push_back(3); graph[3].push_back(1);
    graph[2].push_back(4); graph[4].push_back(2);
    graph[2].push_back(5); graph[5].push_back(2);
    graph[5].push_back(6); graph[6].push_back(5);

    cout << "[재귀 DFS] 시작 노드 1: ";
    vector<bool> visited1(n + 1, false);
    dfs_recursive(1, graph, visited1);
    cout << "\n";

    cout << "[스택 DFS] 시작 노드 1: ";
    vector<bool> visited2(n + 1, false);
    dfs_stack(1, graph, visited2);
    cout << "\n";

    return 0;
}

// -------------------------------------------------------
// 기대 출력:
//   [재귀 DFS] 시작 노드 1: 1 2 4 5 6 3
//   [스택 DFS] 시작 노드 1: 1 2 4 5 6 3
// -------------------------------------------------------
