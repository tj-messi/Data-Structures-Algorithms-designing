#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

// 定义边
struct Edge {
    int to;
    int weight;
};

// Dijkstra 算法计算单源最短路径
vector<int> dijkstra(int start, int n, const vector<vector<Edge>>& graph) {
    vector<int> dist(n + 1, INT_MAX);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    dist[start] = 0;
    pq.push(make_pair(0, start));

    while (!pq.empty()) {
        pair<int, int> top = pq.top();
        int currentDist = top.first;
        int u = top.second;
        pq.pop();

        if (currentDist > dist[u]) {
            continue;
        }

        for (size_t i = 0; i < graph[u].size(); i++) {
            int v = graph[u][i].to;
            int weight = graph[u][i].weight;
            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.push(make_pair(dist[v], v));
            }
        }
    }

    return dist;
}

void solve() {
    int n, m;
    cin >> n >> m;

    vector<vector<Edge>> graph(n + 1);

    for (int i = 0; i < m; ++i) {
        int x, y, w;
        cin >> x >> y >> w;
        Edge edge1 = {y, w};
        Edge edge2 = {x, w};
        graph[x].push_back(edge1);
        graph[y].push_back(edge2);
    }

    int h, r;
    cin >> h >> r;

    vector<int> grassPoints(h);
    for (int i = 0; i < h; ++i) {
        cin >> grassPoints[i];
    }

    vector<pair<int, int>> horses(r);
    for (int i = 0; i < r; ++i) {
        cin >> horses[i].first >> horses[i].second;
    }

    // 计算所有牧草点到所有点的最短距离
    vector<int> grassDist(n + 1, INT_MAX);
    for (size_t i = 0; i < grassPoints.size(); i++) {
        vector<int> dist = dijkstra(grassPoints[i], n, graph);
        for (int j = 1; j <= n; ++j) {
            if (dist[j] < grassDist[j]) {
                grassDist[j] = dist[j];
            }
        }
    }

    // 输出每匹小马的最短路径
    for (size_t i = 0; i < horses.size(); i++) {
        int start = horses[i].first;
        int end = horses[i].second;

        vector<int> distFromStart = dijkstra(start, n, graph);
        vector<int> distFromEnd = dijkstra(end, n, graph);

        int minDist = INT_MAX;
        for (size_t j = 0; j < grassPoints.size(); j++) {
            int grass = grassPoints[j];
            int totalDist = distFromStart[grass] + distFromEnd[grass];
            if (totalDist < minDist) {
                minDist = totalDist;
            }
        }

        cout << minDist << endl;
    }

    return;
}

int main()
{
    int t =1;
    //cin >> t;
    while(t--)
    {
        solve();
    }
    return 0;
}