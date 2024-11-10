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
    Node * root = NULL;  //���ĳ�ʼ��
    if(pre.length() > 0)
    {
        root = new Node;  //Ϊ���������ṹ������Ҫ���ڴ�
        root->data = pre[0]; //�������еĵ�һ��Ԫ��Ϊ�����
        int index = in.find(root->data);  //�������������еĸ����λ��
        // �ж��Ƿ��ܹ���ȷ������������
        if (index == string::npos || index >= pre.length()) {
            //cout << "Error" << endl;
            //exit(0);
            vis = false;
            return nullptr;
        }
        root->lchild = CreateTree(pre.substr(1, index), in.substr(0, index));  //�ݹ鴴��������
        root->rchild = CreateTree(pre.substr(index + 1), in.substr(index + 1)); //�ݹ鴴��������
    }
    return root;
}
 
void PostOrder(Node * root)  //�ݹ�������
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