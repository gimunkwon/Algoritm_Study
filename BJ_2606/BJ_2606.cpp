/*
 * 백준 2606 - 바이러스 (Silver 3)
 * https://www.acmicpc.net/problem/2606
 *
 * [문제 요약]
 * - 컴퓨터 N대가 네트워크로 연결되어 있음
 * - 1번 컴퓨터가 바이러스에 감염되면 연결된 컴퓨터도 감염됨
 * - 1번 컴퓨터로 인해 감염되는 컴퓨터 수를 출력 (1번 제외)
 *
 * [입력]
 * - 첫째 줄: 컴퓨터 수 N (1 ≤ N ≤ 100)
 * - 둘째 줄: 연결 쌍의 수 M
 * - 이후 M줄: 연결된 컴퓨터 번호 쌍 (a, b)
 *
 * [출력]
 * - 1번 컴퓨터가 바이러스에 걸렸을 때 감염되는 컴퓨터 수 (1번 제외)
 *
 * [입력 예시]
 * 7
 * 6
 * 1 2
 * 2 3
 * 1 5
 * 5 2
 * 5 6
 * 4 7
 *
 * [출력 예시]
 * 4
 *
 * [풀이 접근]
 * TODO
 */

#include <iostream>
#include <vector>
using namespace std;

int N, M;
vector<int> graph[101];
bool visited[101];

void dfs(int node)
{
    // TODO
    visited[node] = true;
    
    for (int i : graph[node])
    {
        if (!visited[i])
        {
            dfs(i);
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M;

    for (int i = 0; i < M; i++)
    {
        int a, b;
        cin >> a >> b;
        // TODO: 그래프 연결 정보 저장
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    // TODO: 1번 노드에서 DFS 시작
    dfs(1);

    // TODO: 감염된 컴퓨터 수 출력 (1번 제외)
    int count = 0;
    
    for (int i = 2; i < (int)size(visited); i++)
    {
        if (visited[i])
        {
            count++;
        }
    }
    
    cout << count;
    
    

    return 0;
}