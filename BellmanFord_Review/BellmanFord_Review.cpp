#include <iostream>
#include <vector>

using namespace std;

//TODO::그래프를 에지리스트로 표현하기
struct Edge
{
    int u, v, w;
};

int n,m;
vector<Edge> edges;

bool bellmanFord(int start, vector<int>& dist)
{
    dist.assign(n + 1, INT_MAX);
    dist[start] = 0;
    
    for (int i = 0; i < n - 1; i++)
    {
        for (const auto& e : edges)
        {
            if (dist[e.u] == INT_MAX) continue;
            if (dist[e.v] > dist[e.u] + e.w)
            {
                dist[e.v] = dist[e.u] + e.w;
            }
        }
    }
    
    for (const auto& e : edges)
    {
        if (dist[e.u] == INT_MAX) continue;
        if (dist[e.v] > dist[e.u] + e.w)
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
