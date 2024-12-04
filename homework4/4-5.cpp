#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>
using namespace std;

struct Node {
    int value;                  // �ڵ���
    int length;                 // ��ǰ�ڵ������ʱ
    vector<int> predecessors;   // ��ȵĽڵ�
    vector<int> successors;     // ���ȵĽڵ�
};

vector<Node> graph;             // ͼ�Ĵ洢�ṹ
vector<int> ve, vl, slack;      // ���翪ʼʱ�䣬�������ʱ�䣬ÿ�����������
vector<int> inDegree, outDegree; // ��Ⱥͳ���
int nodeCount;                  // �ڵ�����

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
            node.predecessors.push_back(predecessor - 1);  // �洢Ϊ 0 ����
            outDegree[predecessor - 1]++;
        }

        graph[i] = node;
    }

    // ����ÿ���ڵ�ĳ���
    for (int i = 0; i < nodeCount; i++) {
        for (int predecessor : graph[i].predecessors) {
            graph[predecessor].successors.push_back(i);
        }
    }
}

// ����ڵ�����翪ʼʱ��
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

// ����ڵ���������ʱ��
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
