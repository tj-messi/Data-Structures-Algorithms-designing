#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// �ߵĽṹ��
struct Edge {
    int src, dst, weight;
};

class UnionFind {
    vector<int> parent, rank;

public:
    UnionFind(int n) {
        parent.resize(n + 1);
        rank.resize(n + 1, 0);
        for (int i = 1; i <= n; ++i) parent[i] = i;
    }

    int find(int x) {
        if (parent[x] != x) parent[x] = find(parent[x]);
        return parent[x];
    }

    void unite(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        if (rootX != rootY) {
            if (rank[rootX] > rank[rootY]) {
                parent[rootY] = rootX;
            } else if (rank[rootX] < rank[rootY]) {
                parent[rootX] = rootY;
            } else {
                parent[rootY] = rootX;
                rank[rootX]++;
            }
        }
    }

    bool connected(int x, int y) {
        return find(x) == find(y);
    }
};

int kruskal(int n, vector<Edge>& edges, UnionFind& uf) {
    // ����Ȩֵ����
    sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) {
        return a.weight < b.weight;
    });

    int totalWeight = 0;
    int edgeCount = 0;

    for (const auto& edge : edges) {
        if (!uf.connected(edge.src, edge.dst)) {
            uf.unite(edge.src, edge.dst);
            totalWeight += edge.weight;
            edgeCount++;

            // �������ﵽ (������ - 1) ʱ���������
            if (edgeCount == n - 1) {
                break;
            }
        }
    }

    return totalWeight;
}

void solve() 
{
    int n;
    cin >> n;

    vector<Edge> edges;

    // ��ȡȨֵ����
    vector<vector<int>> weightMatrix(n + 1, vector<int>(n + 1));
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            cin >> weightMatrix[i][j];
        }
    }

    // ��ȡ�����ӱ�
    int m;
    cin >> m;
    UnionFind uf(n);
    for (int i = 0; i < m; ++i) {
        int src, dst;
        cin >> src >> dst;
        uf.unite(src, dst); // ���Ϊ�����ӣ�������Ȩֵ
    }

    // �������δ���ӵı�
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j < i; ++j) {
            if (weightMatrix[i][j] > 0) {
                edges.push_back({i, j, weightMatrix[i][j]});
            }
        }
    }

    // ������С��������Ȩֵ��
    cout << kruskal(n, edges, uf) << endl;

    return;
}

int main()
{
    int t;
    t=1;
    //cin>>t;
    while(t--)
    {
        solve();
    }
    return 0;
}

