#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <algorithm>
using namespace std;

#define MAX_VERTEX_NUM 1000

// 邻接矩阵表示图
static vector<vector<int>> AdjMatrix(MAX_VERTEX_NUM, vector<int>(MAX_VERTEX_NUM, 0));
static vector<int> visited(MAX_VERTEX_NUM, 0);
static int vexnum = 0, arcnum = 0;

// 判断节点是否已创建
bool is_Create(const vector<vector<int>>& matrix, int node) {
    for (int t = 0; t < vexnum; t++) {
        if (matrix[node][t] != 0 || matrix[t][node] != 0) {
            return true;
        }
    }
    return false;
}

// 创建无向图
void Creat_DG() {
    int src_node, dst_node;
    cin >> vexnum >> arcnum;

    for (int i = 0; i < arcnum; i++) {
        cin >> src_node >> dst_node;
        AdjMatrix[src_node][dst_node] = 1;
        AdjMatrix[dst_node][src_node] = 1; // 无向图
    }
}

// BFS 遍历
void BFS(int src_node, vector<int>& result) {
    queue<int> q;
    q.push(src_node);
    visited[src_node] = 1;

    while (!q.empty()) {
        int tmp_node = q.front();
        q.pop();
        result.push_back(tmp_node);

        for (int i = 0; i < vexnum; i++) {
            if (AdjMatrix[tmp_node][i] && !visited[i]) {
                q.push(i);
                visited[i] = 1;
            }
        }
    }
}

// DFS 遍历
void DFS(int src_node, vector<int>& result) {
    visited[src_node] = 1;
    result.push_back(src_node);

    for (int i = 0; i < vexnum; i++) {
        if (AdjMatrix[src_node][i] && !visited[i]) {
            DFS(i, result);
        }
    }
}

// 判断是否遍历完所有节点
bool Search_Over() {
    return all_of(visited.begin(), visited.begin() + vexnum, [](int v) { return v == 1; });
}

void solve()
{
    Creat_DG();

    vector<vector<int>> BFS_Result;
    vector<vector<int>> DFS_Result;

    // BFS 遍历
    fill(visited.begin(), visited.begin() + vexnum, 0);
    for (int i = 0; i < vexnum; i++) {
        if (!visited[i]) {
            vector<int> result;
            BFS(i, result);
            BFS_Result.push_back(result);
        }
    }

    // DFS 遍历
    fill(visited.begin(), visited.begin() + vexnum, 0);
    for (int i = 0; i < vexnum; i++) {
        if (!visited[i]) {
            vector<int> result;
            DFS(i, result);
            DFS_Result.push_back(result);
        }
    }

    // 输出 DFS 结果
    for (const auto& component : DFS_Result) {
        cout << "{";
        for (size_t i = 0; i < component.size(); i++) {
            cout << component[i];
            if (i != component.size() - 1) cout << " ";
        }
        cout << "}";
    }
    cout << endl;

    // 输出 BFS 结果
    for (const auto& component : BFS_Result) {
        cout << "{";
        for (size_t i = 0; i < component.size(); i++) {
            cout << component[i];
            if (i != component.size() - 1) cout << " ";
        }
        cout << "}";
    }
    cout << endl;

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
