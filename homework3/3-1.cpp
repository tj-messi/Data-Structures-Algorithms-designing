#include <iostream>
#include<string>
#include <algorithm>  // �������ͷ�ļ���ʹ�� reverse ����
#include <vector>
#include <istream>
#include<vector>
#include<stack>

#define STACK_INIT_SIZE 200    //�洢�ռ��ʼ������
#define STACKINCREMENT 30      //�洢�ռ�������� 
#define OVERFLOW -1

using namespace std;

typedef struct TreeNode {//���������Ľṹ
    char data;
    struct TreeNode* lchild;
    struct TreeNode* rchild;
}*Node, Elem;    //�����TreeNode��ָ��Node������ĵ�ַ
typedef struct {//�������Ľṹ
    Node root;
}Tree;
class BinaryTree {
public:
    int InitTree(Tree* t) {//��ʼ��������
        if (t == NULL)
            return -1;
        Node node = (Node)malloc(sizeof(struct TreeNode));//Ϊ����ʼ���ڴ�ռ�
        //������ڵ�
        t->root = node;
        //����ָ��ָ���
        (t->root)->lchild = NULL;   
        (t->root)->rchild = NULL;
 
        return 1;
    }
    int Makenode(vector<Node> &temp_r,char e,int j) {   //�����½�㣬���ַΪ*node�����ֵΪe
        if (&temp_r[j] == NULL) {
            return -1;
        }
        if (((temp_r[j]) = (Node)malloc(sizeof(struct TreeNode))) == NULL) {
            return -1;
        }
        (temp_r[j])->lchild = NULL;
        (temp_r[j])->rchild = NULL;
        (temp_r[j])->data = e;
        return 1;
    }
};
 
static stack<Elem> s;
static BinaryTree t;
//���ܺ��������ݳ���ջ������ȡ�������������,����ֵΪ
void Get_Midorder_Preorder(int n, vector<char>& midorder, vector<char>& preorder) {
    stack<Elem> st;
    int N = 2 * n;
    string command;
    Elem temp;
    for (int i = 1; i <= N;i++) {
        cin >> command;
        if (command == "push") { //�����ѹջ����
            cin >> temp.data;
            st.push( temp);//�ѽ��ŵ�ջ����
            (preorder).push_back(temp.data);
        }
        if (command == "pop") {     //����ǳ�ջ����
            temp = st.top();
            st.pop();    //����ջ
            (midorder).push_back(temp.data);//����Ԫ�طŵ����Ա���
        }
    }
}
static vector<Node> temp_r(200);//��Ŵ����ӵ��ҽ��
static vector<Node> temp_l(200);//��Ŵ����ӵ��ҽ��
//���ܺ���������ǰ������������õ�����������
void CreatTree(Tree& tree, vector<char>preorder, vector<char>midorder) {
    stack<Node>st;
    int i =0;//�����������еļ������
    int j = 0;//�����������еļ������
    int k;
    char root_elem = preorder[i];
    ((&tree)->root)->data = root_elem;//������ڵ��Ԫ��
    st.push((&tree)->root);//�ѽ��ĵ�ַ��ջ���棺��������Ŀ������������һ���湹����Ϣ���ڶ��������ַ����ֱ�ӷ��ʽ�㲢��������
    ++i;
    Node tmp_linked= ((&tree)->root);//�����ӵĸ��ڵ�
    while (i <= preorder.size() - 1) {
        //�����������У��Ƚϵ�ǰ����λ����ջ��������һ���������Ԫ�صĹ�ϵ)
        if (midorder[j] == st.top()->data) {
            t.Makenode(temp_r, preorder[i], i);//�½������ӵ��ҽڵ㣬���ڻ��½��ܶ��ҽڵ㣬���Կ�һ������������������ǵ���Ϣ
            k = j;//����һ��j����Ϊ���滹Ҫ�õ�
            while (1) {  //�����д������ϣ�Ѱ�Ҹ��ҽ��Ӧ�����ӵĸ��ڵ�
                if (!st.empty()&&midorder[k] == st.top()->data){
                    tmp_linked = st.top();//tmp_linked���������ջ���
                    st.pop();
                }
                else
                    break;
                ++k;
            }
            (tmp_linked)->rchild = temp_r[i];//���ӵ��ҽڵ���
            st.push(temp_r[i]);//��Ҫ����ÿ����һ����Ҫ��һ����ջ�������ǽ������õ����������ҽڵ���ջ
            j = k;
        }
        else if (midorder[j] != st.top()->data) {
            t.Makenode(temp_l, preorder[i], i);//�½������ӵ���ڵ㣬���Ԫ�����������е�ǰָ���Ԫ�أ�ͬ��Ҳ���½��ܶ���ڵ㣬��Ҫ���������ֱ���
            tmp_linked = st.top();
            (tmp_linked)->lchild = temp_l[i];//��ڵ�ֱ��������һ��Ԫ��
            st.push(temp_l[i]);
        }
        else;
        ++i;
    }
}
void PostTraverse(Tree tree, stack<Elem> st, vector<char>& postorder) {
    Elem postorder_elem;
 
    st.push(*((&tree)->root));//���׽ڵ�浽ջ��
    while (st.empty() != 1) {
        postorder_elem = st.top();
        st.pop();
        postorder.push_back(postorder_elem.data);
        if (postorder_elem.lchild != NULL) {
            st.push( *(postorder_elem.lchild));
        }
        if (postorder_elem.rchild != NULL) {
            st.push( *(postorder_elem.rchild));
        }
    }
}

void solve()
{
    stack<Elem> s;
    Tree tree;
    t.InitTree(&tree);
    vector<char>midorder;
    vector<char>preorder;
    vector<char>postorder;
    int n;
    cin >> n;
    Get_Midorder_Preorder(n, midorder, preorder);//ģ�����ջ���̣���ȡ��������Ľ��
    CreatTree(tree, preorder, midorder);
    PostTraverse(tree, s, postorder);
    for (int k = postorder.size() - 1; k >= 0; k--) {
        cout << postorder[k];
    }
    cout << endl;
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