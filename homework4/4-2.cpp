#include <iostream>
#include <vector>
#include <queue>
#include <iomanip>
using namespace std;

// 结点结构
struct Node {
    int value;
    vector<int> neighbors;
};

// 图的表示
vector<Node> graph;
vector<int> visited;

// 创建图
void CreateGraph() {
    int vexnum, arcnum;
    cin >> vexnum >> arcnum;
    graph.resize(vexnum + 1); // 节点编号从 1 开始

    for (int i = 0; i < arcnum; i++) {
        int src, dst;
        cin >> src >> dst;

        // 建立无向图的邻接关系
        graph[src].value = src;
        graph[dst].value = dst;
        graph[src].neighbors.push_back(dst);
        graph[dst].neighbors.push_back(src);
    }
}

// BFS 遍历，返回 6 层内访问到的节点数量
int BFS(const Node& startNode, int vexnum) {
    queue<Node> q;
    visited.assign(vexnum + 1, 0); // 初始化访问状态
    q.push(startNode);
    visited[startNode.value] = 1;

    int count = 1; // 包括起始节点
    int layerCount = 1, currentLayer = 0;

    while (!q.empty() && currentLayer < 6) {
        int nodesInLayer = q.size();
        for (int i = 0; i < nodesInLayer; i++) {
            Node current = q.front();
            q.pop();

            for (int neighbor : current.neighbors) {
                if (!visited[neighbor]) {
                    visited[neighbor] = 1;
                    q.push(graph[neighbor]);
                    count++;
                }
            }
        }
        currentLayer++;
    }
    return count;
}

void solve()
 {
    CreateGraph();

    int vexnum = graph.size() - 1; // 节点数
    vector<float> ratios(vexnum + 1);

    for (int i = 1; i <= vexnum; i++) {
        int reachableNodes = BFS(graph[i], vexnum);
        ratios[i] = 100.0f * (float)reachableNodes / vexnum;
    }

    for (int i = 1; i <= vexnum; i++) {
        cout << i << ": " << fixed << setprecision(2) << ratios[i] << "%" << endl;
    }

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
