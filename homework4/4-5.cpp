#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>
using namespace std;

struct Node {
    int value;                  // 节点编号
    int length;                 // 当前节点任务耗时
    vector<int> predecessors;   // 入度的节点
    vector<int> successors;     // 出度的节点
};

vector<Node> graph;             // 图的存储结构
vector<int> ve, vl, slack;      // 最早开始时间，最晚完成时间，每个任务的余量
vector<int> inDegree, outDegree; // 入度和出度
int nodeCount;                  // 节点数量

void createGraph() {
    cin >> nodeCount;

    graph.resize(nodeCount);
    ve.resize(nodeCount, 0);
    vl.resize(nodeCount, 0);
    slack.resize(nodeCount, 0);
    inDegree.resize(nodeCount, 0);
    outDegree.resize(nodeCount, 0);

    for (int i = 0; i < nodeCount; i++) {
        Node node;
        node.value = i + 1;
        cin >> node.length;

        int inDegreeCount;
        cin >> inDegreeCount;

        inDegree[i] = inDegreeCount;

        for (int j = 0; j < inDegreeCount; j++) {
            int predecessor;
            cin >> predecessor;
            node.predecessors.push_back(predecessor - 1);  // 存储为 0 索引
            outDegree[predecessor - 1]++;
        }

        graph[i] = node;
    }

    // 更新每个节点的出度
    for (int i = 0; i < nodeCount; i++) {
        for (int predecessor : graph[i].predecessors) {
            graph[predecessor].successors.push_back(i);
        }
    }
}

// 计算节点的最早开始时间
void calculateVe() {
    queue<int> q;

    for (int i = 0; i < nodeCount; i++) {
        if (inDegree[i] == 0) q.push(i);
    }

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int successor : graph[u].successors) {
            ve[successor] = max(ve[successor], ve[u] + graph[u].length);
            if (--inDegree[successor] == 0) q.push(successor);
        }
    }
}

// 计算节点的最晚完成时间
void calculateVl() {
    int maxGraduationTime = *max_element(ve.begin(), ve.end());

    for (int i = 0; i < nodeCount; i++) {
        vl[i] = maxGraduationTime;
    }

    queue<int> q;
    for (int i = 0; i < nodeCount; i++) {
        if (outDegree[i] == 0) q.push(i);
    }

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int predecessor : graph[u].predecessors) {
            vl[predecessor] = min(vl[predecessor], vl[u] - graph[predecessor].length);
            if (--outDegree[predecessor] == 0) q.push(predecessor);
        }
    }
}

int main() {
    createGraph();
    calculateVe();
    calculateVl();

    for (int i = 0; i < nodeCount; i++) {
        slack[i] = vl[i] - ve[i];
    }

    for (int i = 0; i < nodeCount; i++) {
        cout << ve[i] + graph[i].length << " ";
        cout << (slack[i] == 0 ? 1 : 0) << endl;
    }

    return 0;
}
