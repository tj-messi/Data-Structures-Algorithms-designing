#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class Graph {
public:
    int k, n, m;
    vector<vector<int>> AdjMatrix_row, AdjMatrix_col, Matrix;
    vector<int> DI_row, DI_col, Order_row, Order_col;
    vector<vector<int>> row_links, col_links;

    Graph() : k(0), n(0), m(0) {}

    void createGraph() {
        cin >> k >> n >> m;
        AdjMatrix_row.assign(k + 1, vector<int>(k + 1, 0));
        AdjMatrix_col.assign(k + 1, vector<int>(k + 1, 0));
        Matrix.assign(k + 1, vector<int>(k + 1, 0));
        DI_row.assign(k + 1, 0);
        DI_col.assign(k + 1, 0);
        row_links.assign(k + 1, vector<int>());
        col_links.assign(k + 1, vector<int>());
        Order_row.assign(k + 1, 0);
        Order_col.assign(k + 1, 0);

        for (int i = 0; i < n; ++i) {
            int src, dst;
            cin >> src >> dst;
            AdjMatrix_row[src][dst] = 1;
            DI_row[dst]++;
            row_links[src].push_back(dst);
        }

        for (int i = 0; i < m; ++i) {
            int src, dst;
            cin >> src >> dst;
            AdjMatrix_col[src][dst] = 1;
            DI_col[dst]++;
            col_links[src].push_back(dst);
        }
    }

    bool detectCycle(const vector<vector<int>>& matrix) {
        vector<int> in_degree(k + 1, 0), visited(k + 1, 0);
        queue<int> Q;

        for (int i = 1; i <= k; ++i)
            for (int j = 1; j <= k; ++j)
                if (matrix[j][i]) in_degree[i]++;

        for (int i = 1; i <= k; ++i)
            if (in_degree[i] == 0) Q.push(i);

        int visited_count = 0;
        while (!Q.empty()) {
            int u = Q.front();
            Q.pop();
            visited_count++;
            for (int v = 1; v <= k; ++v) {
                if (matrix[u][v] && --in_degree[v] == 0)
                    Q.push(v);
            }
        }
        return visited_count != k;
    }

    void createOrder(vector<int>& DI, vector<int>& Order, const vector<vector<int>>& links) {
        int count = 1;
        while (count <= k) {
            for (int i = 1; i <= k; ++i) {
                if (DI[i] == 0) {
                    Order[count++] = i;
                    DI[i] = -1;
                    for (int v : links[i]) DI[v]--;
                    break;
                }
            }
        }
    }

    void createMatrix() {
        for (int i = 1; i <= k; ++i)
            for (int j = 1; j <= k; ++j)
                Matrix[i][j] = (Order_row[i] == Order_col[j]) ? Order_row[i] : 0;
    }

    void printMatrix() {
        for (int i = 1; i <= k; ++i) {
            for (int j = 1; j <= k; ++j) {
                cout << Matrix[i][j];
                if (j < k) cout << " ";
            }
            cout << endl;
        }
    }
};

void solve()
 {
    Graph graph;
    graph.createGraph();
    if (!graph.detectCycle(graph.AdjMatrix_row) && !graph.detectCycle(graph.AdjMatrix_col)) {
        graph.createOrder(graph.DI_row, graph.Order_row, graph.row_links);
        graph.createOrder(graph.DI_col, graph.Order_col, graph.col_links);
        graph.createMatrix();
        graph.printMatrix();
    } else {
        cout << "-1" << endl;
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