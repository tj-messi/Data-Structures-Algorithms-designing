#include <iostream>
#include<string>
#include <algorithm>  // �������ͷ�ļ���ʹ�� reverse ����
#include <vector>
#include <istream>
#include<vector>
#include<stack>
#include <string.h>

#define STACK_INIT_SIZE 200    //�洢�ռ��ʼ������
#define STACKINCREMENT 30      //�洢�ռ�������� 
#define OVERFLOW -1

using namespace std;

// �������ڵ�ṹ��
struct TreeNodeStruct {
    char value;
    int leftIndex, rightIndex;
};
 
// Ѱ�����ĸ��ڵ�
int getRootIndex(int nodeCount, const vector<TreeNodeStruct>& treeNodes) {
   vector<bool> isChildNode(nodeCount, false);
    for (const auto& node : treeNodes) {
        if (node.leftIndex != -1) isChildNode[node.leftIndex] = true;
        if (node.rightIndex != -1) isChildNode[node.rightIndex] = true;
    }
    for (int i = 0; i < nodeCount; ++i) {
        if (!isChildNode[i]) return i;
    }
    return -1;
}
 
// �����������
int computeTreeDepth(int rootNodeIndex, const vector<TreeNodeStruct>& treeNodes) {
    if (rootNodeIndex == -1) return 0;
    int leftDepth = computeTreeDepth(treeNodes[rootNodeIndex].leftIndex, treeNodes);
    int rightDepth = computeTreeDepth(treeNodes[rootNodeIndex].rightIndex, treeNodes);
    return 1 + max(leftDepth, rightDepth);
}
 
// �ж��������Ƿ�ͬ��
bool checkIsomorphism(int root1Index, int root2Index, const vector<TreeNodeStruct>& tree1, const vector<TreeNodeStruct>& tree2) {
    if (root1Index == -1 && root2Index == -1) return true;
    if ((root1Index == -1) != (root2Index == -1)) return false;
    if (tree1[root1Index].value != tree2[root2Index].value) return false;
 
    bool withoutSwapping = checkIsomorphism(tree1[root1Index].leftIndex, tree2[root2Index].leftIndex, tree1, tree2) &&
                           checkIsomorphism(tree1[root1Index].rightIndex, tree2[root2Index].rightIndex, tree1, tree2);
 
    bool withSwapping = checkIsomorphism(tree1[root1Index].leftIndex, tree2[root2Index].rightIndex, tree1, tree2) &&
                        checkIsomorphism(tree1[root1Index].rightIndex, tree2[root2Index].leftIndex, tree1, tree2);
 
    return withoutSwapping || withSwapping;
}

bool make_cmp(vector<TreeNodeStruct> t1, int node1, vector<TreeNodeStruct> t2, int node2)
{
    char n1l, n1r, n2l, n2r;

    if (t1[node1].leftIndex != -1) // �޸� leftson Ϊ leftIndex
        n1l = t1[t1[node1].leftIndex].value; // �޸� data Ϊ value
    else
        n1l = '-';

    if (t1[node1].rightIndex != -1) // �޸� rightson Ϊ rightIndex
        n1r = t1[t1[node1].rightIndex].value; // �޸� data Ϊ value
    else
        n1r = '-';

    if (t2[node2].leftIndex != -1) // �޸� leftson Ϊ leftIndex
        n2l = t2[t2[node2].leftIndex].value; // �޸� data Ϊ value
    else
        n2l = '-';

    if (t2[node2].rightIndex != -1) // �޸� rightson Ϊ rightIndex
        n2r = t2[t2[node2].rightIndex].value; // �޸� data Ϊ value
    else
        n2r = '-';

    if ((n1l == n2l && n1r == n2r) || (n1l == n2r && n1r == n2l))
    {
        // ��ʱ���㣬���µݹ�
        bool flag = true;

        if (n1l == n2l && n1r == n2r)
        {
            if (t1[node1].leftIndex != -1) // �޸� leftson Ϊ leftIndex
            {
                flag = flag && make_cmp(t1, t1[node1].leftIndex, t2, t2[node2].leftIndex); // �޸� leftson Ϊ leftIndex
            }
            if (t1[node1].rightIndex != -1) // �޸� rightson Ϊ rightIndex
            {
                flag = flag && make_cmp(t1, t1[node1].rightIndex, t2, t2[node2].rightIndex); // �޸� rightson Ϊ rightIndex
            }
        }
        if (n1l == n2r && n1r == n2l)
        {
            if (t1[node1].leftIndex != -1) // �޸� leftson Ϊ leftIndex
            {
                flag = flag && make_cmp(t1, t1[node1].leftIndex, t2, t2[node2].rightIndex); // �޸� leftson Ϊ leftIndex
            }
            if (t1[node1].rightIndex != -1) // �޸� rightson Ϊ rightIndex
            {
                flag = flag && make_cmp(t1, t1[node1].rightIndex, t2, t2[node2].leftIndex); // �޸� rightson Ϊ rightIndex
            }
        }
        return flag;
    }
    else
    {
        return false;
    }
}


void solve()
{
    int nodeCount1, nodeCount2;
    cin >> nodeCount1;
    vector<TreeNodeStruct> tree1(nodeCount1);
    for (int i = 0; i < nodeCount1; ++i) {
        string leftChild, rightChild;
        cin >> tree1[i].value >> leftChild >> rightChild;
        tree1[i].leftIndex = (leftChild == "-") ? -1 : stoi(leftChild);
        tree1[i].rightIndex = (rightChild == "-") ? -1 : stoi(rightChild);
    }
 
    cin >> nodeCount2;
    vector<TreeNodeStruct> tree2(nodeCount2);
    for (int i = 0; i < nodeCount2; ++i) {
       string leftChild, rightChild;
        cin >> tree2[i].value >> leftChild >> rightChild;
        tree2[i].leftIndex = (leftChild == "-") ? -1 : stoi(leftChild);
        tree2[i].rightIndex = (rightChild == "-") ? -1 : stoi(rightChild);
    }
 
    if (nodeCount1 == 0 && nodeCount2 == 0)
    {
        cout << "Yes\n0\n0\n";
        return;
    }
 
    int root1 = getRootIndex(nodeCount1, tree1);
    int root2 = getRootIndex(nodeCount2, tree2);
 
    bool isomorphicTrees = checkIsomorphism(root1, root2, tree1, tree2);
    cout << (isomorphicTrees ? "Yes" : "No") << "\n";
 
    int depthOfTree1 = computeTreeDepth(root1, tree1);
    int depthOfTree2 = computeTreeDepth(root2, tree2);
 
    cout << depthOfTree1 << "\n";
    cout << depthOfTree2 << "\n";
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
