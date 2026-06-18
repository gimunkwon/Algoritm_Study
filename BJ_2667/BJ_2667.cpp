/*
 * 백준 2667 - 단지번호붙이기 (Silver I)
 *
 * 문제:
 * <그림 1>과 같이 정사각형 모양의 지도가 있다. 1은 집이 있는 곳을, 0은 집이 없는 곳을 나타낸다.
 * 철수는 이 지도를 가지고 연결된 집들의 모임인 단지를 정의하고, 단지에 번호를 붙이려고 한다.
 * 여기서 연결되었다는 것은 어떤 집이 좌우, 혹은 아래위로 다른 집이 있는 경우를 말한다.
 * 대각선상에 있는 집끼리는 연결된 것이 아니다. <그림 2>는 <그림 1>을 가지고 단지별로 번호를 붙인 것이다.
 * 지도를 입력하여 단지수를 출력하고 각 단지에 속하는 집의 수를 오름차순으로 정렬하여 출력하는 프로그램을 작성하시오.
 *
 * 입력:
 * 첫 번째 줄에는 지도의 크기 N(정사각형이므로 가로와 세로의 크기는 같으며 5≤N≤25)이 입력되고,
 * 그 다음 N줄에는 각각 N개의 자료(0혹은 1)가 입력된다.
 *
 * 출력:
 * 첫 번째 줄에는 총 단지수를 출력하시오.
 * 그리고 그 다음 줄부터 각 단지내 집의 수를 오름차순으로 정렬하여 한 줄에 하나씩 출력하시오.
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
int dx[] = { 0, 0, 1, -1 }; // 상하좌우 행 방향
int dy[] = { 1, -1, 0, 0 }; // 상하좌우 열 방향

// (row, col)에서 시작해 연결된 집을 모두 방문하고 집 개수를 반환
int dfs(int row, int col, vector<vector<int>>& village, vector<vector<bool>>& visited)
{
    visited[row][col] = true;
    int count = 1; // 현재 집 포함

    for (int i = 0; i < 4; i++)
    {
        int next_row = row + dx[i];
        int next_col = col + dy[i];

        // 범위 체크 → 집 여부 체크 → 방문 여부 체크
        if (next_row < 0 || next_row >= N || next_col < 0 || next_col >= N) continue;
        if (village[next_row][next_col] == 0) continue;
        if (visited[next_row][next_col]) continue;

        count += dfs(next_row, next_col, village, visited);
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
        {
            village[i][j] = s[j] - '0';
        }
    }

    vector<int> result;

    // 전체 격자 순회: 미방문 집(1)을 만나면 새 단지 발견
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (village[i][j] == 1 && !visited[i][j])
            {
                result.push_back(dfs(i, j, village, visited));
            }
        }
    }

    sort(result.begin(), result.end());

    cout << result.size() << "\n";
    for (int cnt : result)
        cout << cnt << "\n";

    return 0;
}
