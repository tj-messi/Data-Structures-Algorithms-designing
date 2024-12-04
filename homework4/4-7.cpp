#include <iostream>
#include <vector>
#include <stack>

using namespace std;

const int MAX_N = 100; // 最大节点数
int n, m;              // 节点数和边数
int graph[MAX_N][MAX_N]; // 邻接矩阵存储图
vector<int> eulerPath;  // 保存欧拉路径

// 深度优先搜索寻找欧拉路径
void dfs(int u) {
    for (int v = 1; v <= n; ++v) {
        while (graph[u][v] > 0) {
            graph[u][v]--;
            graph[v][u]--; // 无向图，两边都标记为访问过
            dfs(v);
        }
    }
    eulerPath.push_back(u);
}

int main() {
    cin >> n >> m;

    // 初始化邻接矩阵
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        graph[a][b]++;
        graph[b][a]++; // 无向边
    }

    // 检查图是否存在欧拉路径
    int oddCount = 0, startNode = 1;
    for (int i = 1; i <= n; ++i) {
        int degree = 0;
        for (int j = 1; j <= n; ++j) {
            degree += graph[i][j];
        }
        if (degree % 2 != 0) {
            oddCount++;
            startNode = i; // 欧拉路径的起点是奇度点
        }
    }

    if (oddCount != 0 && oddCount != 2) {
        cout << "No Euler Path exists." << endl;
        return 0;
    }

    // 找到欧拉路径
    dfs(startNode);

    // 输出欧拉路径
    for (int i = eulerPath.size() - 1; i >= 0; --i) {
        cout << eulerPath[i];
        if (i > 0) cout << " ";
    }
    cout << endl;

    return 0;
}
