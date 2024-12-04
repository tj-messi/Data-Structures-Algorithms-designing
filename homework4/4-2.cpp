#include <iostream>
#include <vector>
#include <queue>
#include <iomanip>
using namespace std;

// ���ṹ
struct Node {
    int value;
    vector<int> neighbors;
};

// ͼ�ı�ʾ
vector<Node> graph;
vector<int> visited;

// ����ͼ
void CreateGraph() {
    int vexnum, arcnum;
    cin >> vexnum >> arcnum;
    graph.resize(vexnum + 1); // �ڵ��Ŵ� 1 ��ʼ

    for (int i = 0; i < arcnum; i++) {
        int src, dst;
        cin >> src >> dst;

        // ��������ͼ���ڽӹ�ϵ
        graph[src].value = src;
        graph[dst].value = dst;
        graph[src].neighbors.push_back(dst);
        graph[dst].neighbors.push_back(src);
    }
}

// BFS ���������� 6 ���ڷ��ʵ��Ľڵ�����
int BFS(const Node& startNode, int vexnum) {
    queue<Node> q;
    visited.assign(vexnum + 1, 0); // ��ʼ������״̬
    q.push(startNode);
    visited[startNode.value] = 1;

    int count = 1; // ������ʼ�ڵ�
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

    int vexnum = graph.size() - 1; // �ڵ���
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
