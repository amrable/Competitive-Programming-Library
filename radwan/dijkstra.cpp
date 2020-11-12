//DIJKSTRA
#include<bits/stdc++.h>
using namespace std;

#define int long long
int n, m;
const int INF = 1e18;
vector<vector<pair<int, int>>> g(n, vector<pair<int, int>>());

vector<int> dijkstra(int source) {

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    vector<int> dist(n, INF);
    vector<int> processed(n, 0);

    dist[source] = 0;
    pq.push({0, source});

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        if (processed[u]++) continue;

        for (auto &p: g[u]) {
            auto[w, v] = p;
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }

    }
    return dist;
}

