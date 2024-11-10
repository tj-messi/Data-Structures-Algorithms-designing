#include<iostream>
#include<cstdio>
#include<string>
using namespace std;
 
struct Node
{
    char data;
    Node * lchild;
    Node * rchild;
};
bool vis = true;
Node* CreateTree(string pre, string in)
{
    Node * root = NULL;  //树的初始化
    if(pre.length() > 0)
    {
        root = new Node;  //为根结点申请结构体所需要的内存
        root->data = pre[0]; //先序序列的第一个元素为根结点
        int index = in.find(root->data);  //查找中序序列中的根结点位置
        // 判断是否能够正确构建左右子树
        if (index == string::npos || index >= pre.length()) {
            //cout << "Error" << endl;
            //exit(0);
            vis = false;
            return nullptr;
        }
        root->lchild = CreateTree(pre.substr(1, index), in.substr(0, index));  //递归创建左子树
        root->rchild = CreateTree(pre.substr(index + 1), in.substr(index + 1)); //递归创建右子树
    }
    return root;
}
 
void PostOrder(Node * root)  //递归后序遍历
{ 
    if(root != NULL)
    {
        PostOrder(root->lchild);
        PostOrder(root->rchild);
        cout << root->data;
    }
}
 
void solve()
{
    string pre_str, in_str;
    Node *root;
    while(cin >> pre_str >> in_str)
    {
        vis = true;
        root = CreateTree(pre_str, in_str);
        if (vis) 
        {
            PostOrder(root);
            cout << endl;
        }
        else
        {
            cout << "Error" <<endl;
        }
    }
    return;
}

int main()
{
    int t=1;
    //cin >> t;
    while(t--)
    {
        solve();
    }
    return 0;
}