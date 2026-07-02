#include <iostream>
#include <vector>
#include <tuple>

using namespace std;

// C++17 스타일: 에지리스트를 tuple<u, v, w>로 표현
int n, m;
vector<tuple<int, int, int>> edges;

bool bellmanFord(int start, vector<int>& dist)
{
    dist.assign(n + 1, INT_MAX);
    dist[start] = 0;

    for (int i = 0; i < n - 1; i++)
    {
        for (const auto& [u, v, w] : edges) // structured binding (C++17)
        {
            if (dist[u] == INT_MAX) continue;
            if (dist[v] > dist[u] + w)
            {
                dist[v] = dist[u] + w;
            }
        }
    }

    for (const auto& [u, v, w] : edges)
    {
        if (dist[u] == INT_MAX) continue;
        if (dist[v] > dist[u] + w)
        {
            return true;
        }
    }

    return false;
}

int main(int argc, char* argv[])
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    
    n = 4;
    m = 6;
    
    edges = {
        {1,2,2},
        {1,3,5,},
        {2,3,-1},
        {2,4,-3},
        {3,4,4},
        {4,3,1},
    };
    
    vector<int> dist;
    bool bhasNegCycle = bellmanFord(1,dist);
    
    if (bhasNegCycle)
    {
        cout << "음수 사이클 존재" << '\n';
        return 0;
    }
    
    for (int i = 1; i <= n; i++)
    {
        if (dist[i] == INT_MAX)
        {
            cout << "노드" << i << "도달불가" <<"\n";
        }
        else
        {
            cout << "노드" << i << ": " << dist[i] << "\n";
        }
    }
    
    return 0;
}
