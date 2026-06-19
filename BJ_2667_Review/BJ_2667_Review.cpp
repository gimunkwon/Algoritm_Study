/*
 * 백준 2667 - 단지번호붙이기 (Silver I)
 *
 * 문제:
 * 정사각형 모양의 지도가 있다. 1은 집이 있는 곳을, 0은 집이 없는 곳을 나타낸다.
 * 연결된 집들의 모임을 단지라고 정의한다.
 * 연결은 좌우, 위아래만 인정하며 대각선은 해당하지 않는다.
 * 지도를 입력하여 단지수를 출력하고, 각 단지에 속하는 집의 수를 오름차순으로 정렬하여 출력하라.
 *
 * 입력:
 * 첫 번째 줄에 지도의 크기 N (5 ≤ N ≤ 25)
 * 그 다음 N줄에 각각 N개의 자료 (0 또는 1)
 *
 * 출력:
 * 첫 번째 줄: 총 단지 수
 * 그 다음 줄부터: 각 단지 내 집의 수 (오름차순, 한 줄에 하나씩)
 *
 * 예제 입력:
 * 7
 * 0110100
 * 0110101
 * 1110101
 * 0000111
 * 0100000
 * 0111110
 * 0111000
 *
 * 예제 출력:
 * 3
 * 7
 * 8
 * 9
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

int N;
int dx[] = {0,0,1,-1}; // 행
int dy[] = {1,-1,0,0}; // 열

// TODO: DFS 함수 작성
int dfs(int col, int row, vector<vector<int>>& village, vector<vector<bool>>& visited)
{
    visited[col][row] = true;
    int count = 1;
    
    for (int k = 0; k < 4; k++)
    {
        int next_col = col + dx[k];
        int next_row = row + dy[k];
        
        // 만약 애초부터 갈수 없는 경우
        if (next_row < 0 || next_row >= N || next_col < 0 || next_col >= N) continue;
        // 해당 구역이 집인지 아닌지 체크
        if (village[next_col][next_row] == 0) continue;
        // 이미 방문을 한 경우
        if (visited[next_col][next_row]) continue;
        
        count += dfs(next_col, next_row, village, visited);
    }
    
    return count;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;

    vector<vector<int>> village(N, vector<int>(N));
    vector<vector<bool>> visited(N, vector<bool>(N, false));

    for (int i = 0; i < N; i++)
    {
        string s;
        cin >> s;
        for (int j = 0; j < (int)s.size(); j++)
            village[i][j] = s[j] - '0';
    }

    // TODO: 전체 격자 순회 + DFS 호출 + 결과 정렬 후 출력
    vector<int> result;
    
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (village[i][j] == 1 && visited[i][j] == false)
            result.push_back(dfs(i,j,village,visited));
        }
    }
    
    // 출력 : 단지 개수, 단지 내의 집 개수
    cout << (int)result.size() << "\n";
    
    for (int home : result)
    {
        cout << home << '\n';
    }
    
    return 0;
}
