#include <iostream>
#include <vector>
#include <stack>

using namespace std;

const int MAX_N = 100; // ���ڵ���
int n, m;              // �ڵ����ͱ���
int graph[MAX_N][MAX_N]; // �ڽӾ���洢ͼ
vector<int> eulerPath;  // ����ŷ��·��

// �����������Ѱ��ŷ��·��
void dfs(int u) {
    for (int v = 1; v <= n; ++v) {
        while (graph[u][v] > 0) {
            graph[u][v]--;
            graph[v][u]--; // ����ͼ�����߶����Ϊ���ʹ�
            dfs(v);
        }
    }
    eulerPath.push_back(u);
}

int main() {
    cin >> n >> m;

    // ��ʼ���ڽӾ���
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        graph[a][b]++;
        graph[b][a]++; // �����
    }

    // ���ͼ�Ƿ����ŷ��·��
    int oddCount = 0, startNode = 1;
    for (int i = 1; i <= n; ++i) {
        int degree = 0;
        for (int j = 1; j <= n; ++j) {
            degree += graph[i][j];
        }
        if (degree % 2 != 0) {
            oddCount++;
            startNode = i; // ŷ��·�����������ȵ�
        }
    }

    if (oddCount != 0 && oddCount != 2) {
        cout << "No Euler Path exists." << endl;
        return 0;
    }

    // �ҵ�ŷ��·��
    dfs(startNode);

    // ���ŷ��·��
    for (int i = eulerPath.size() - 1; i >= 0; --i) {
        cout << eulerPath[i];
        if (i > 0) cout << " ";
    }
    cout << endl;

    return 0;
}
