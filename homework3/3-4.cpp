#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include<string>
#include <istream>
#include<stack>
#include<queue>
#include<vector>
#define STACK_INIT_SIZE 200    //�洢�ռ��ʼ������
#define STACKINCREMENT 30      //�洢�ռ�������� 
#define OVERFLOW -1
#define MAXSIZE_QUEUE 5000
using namespace std;
//���ݽṹ�ࣺ������
struct TreeNode {//���������Ľṹ
    int data;
    TreeNode *children[100];  //childrenΪ���飬��Ÿ����ӽڵ�ĵ�ַ
    TreeNode* rchild=nullptr;
    int vec_len = 0;
};    //�����TreeNode��ָ��Node������ĵ�ַ
typedef TreeNode Elem;
 
 
void Print_Tree_BFS(Elem tree[]) {  //����BFS�Ĵ�ӡ��
    queue<Elem> queue;
    Elem tmp_node;//�洢�½�����ַ����ʱ����node
    //���ù�����������ķ�ʽ������
    tmp_node = (tree)[0];
    queue.push(tmp_node);
    cout << (tmp_node).data << " ";//���ڵ���Ӳ����
    cout << endl;
    while (queue.empty() != 1) {
        tmp_node = queue.front();
        queue.pop();
        for (int i = 0; i < (tmp_node).vec_len; i++) {
            queue.push(*(tmp_node).children[i]);
            cout << (tmp_node).children[i]->data << " ";
        }
        if ((&tmp_node)->rchild != nullptr) {
            queue.push(*(tmp_node).rchild);
            cout << (tmp_node).rchild->data << " ";
        }
        cout << endl;
    }
}

int Creat_Tree_DFS(Elem tree[], int in) {  //����DFS��˳�򹹽�һ����,�������������
    int deep_tmp = 0;
    int deep_max = 0;
    stack<Elem>st;
    int i = 0;
    Elem tmp_node;//�洢�½�����ַ����ʱ����node
    int tmp1;
    int tmp2;
    tmp_node.data=i;//���½�����tmp_node
    tree[i] = tmp_node;
    st.push(tree[i]);//�½��(ֱ�Ӵ洢��㼴��)�浽ջ��
    ++i;
 
    int input = in;
    if (input == 'd') {
        tmp_node.data = i;
        tree[i] = tmp_node;
        st.push(tree[i]);//�½��(ֱ�Ӵ洢��㼴��)�浽ջ��
        ++i;//ÿ�ζ�һ����i��1
        ++deep_tmp;
    }
    
    while (1) {
        input = getchar();
        if (input == '\n') {
            break;
        }
        if (input != 'd' && input != 'u') {
            continue;
        }
        if (input == 'd') {
            tmp_node.data = i;
            tree[i] = tmp_node;
            st.push(tree[i]);//�½��(ֱ�Ӵ洢��㼴��)�浽ջ��
            ++i;//ÿ�ζ�һ����i��1
            ++deep_tmp;
        }
        deep_max = deep_max > deep_tmp ? deep_max : deep_tmp;
        if (input == 'u') {
            tmp1 = st.top().data;
            st.pop();
            tmp2 = st.top().data;
            tree[tmp2].children[tree[tmp2].vec_len++]=&tree[tmp1];
            //��ջ�������ӹ�ϵ
            --deep_tmp;
        }
    }
    //���ڵ��ջ
    st.pop();
    return deep_max;
}
 
void ReCreat_Tree_BFS(Elem tree[]) {   //�ù�����������ķ�ʽ����+�ع�
    Elem tmp_node;
    int tmp;
    queue<Elem> queue;
    //q.InitQueue(queue);
    queue.push(tree[0]);//���ڵ����
    while (queue.empty() != 1) {
        tmp_node = queue.front();
        queue.pop();
        
        //�����ӽڵ�
        tmp = tmp_node.data;
        
        if (tmp_node.vec_len >= 1) {
            //�����ӽڵ����
            for (int i = 0; i < tree[tmp].vec_len; i++) {
                queue.push(*tree[tmp].children[i]);
            }
            for (int i = 0; i < tree[tmp].vec_len; i++) {
                if (i == 0) {   //�Ե�һ���ӽ�㣬ֻ��Ҫ���µ���֦����������ڵ��ֵܽ�㼴��
                    if (i != tree[tmp].vec_len-1) {   //����Ҫ��֤�ӽڵ����ֵܽ��
                        tree[tmp].children[i]->rchild = tree[tmp].children[i + 1];
                    }
                }
                else {        //��������㣬������Ҫ�ø��ӽڵ����ӽ����ֵܽڵ��⣬����Ҫ���ڵ��Լ�����ӽڵ�Ͽ�����
                    if (i != tree[tmp].vec_len - 1) {   //����Ҫ��֤�ӽڵ����ֵܽ��                      
                        tree[tmp].children[i]->rchild = tree[tmp].children[i + 1];
                        for (int j = i; j <= tree[tmp].vec_len - 2; j++) {
                            tree[tmp].children[j] = tree[tmp].children[j + 1];
                        }
                    }   
                    --tree[tmp].vec_len;//�Ͽ����ӣ��ӽڵ�������1
                    --i;
                }
            }
        }
    }
    
}
 
int Calculate_Tree_Deep(Elem tree[]) {  //�����������
    queue<Elem> queue;
   // q.InitQueue(queue);
    Elem tmp_node;//�洢�½�����ַ����ʱ����node
    int tmp = 0;
    //���ù�����������ķ�ʽ���������
    queue.push(tree[0]);
    int deep = -1;
    int c = 1;
    int c_tmp = 0;
    while (queue.empty() != 1) {
        for (int i = 1; i <= c; i++) {
            tmp_node = queue.front();
            queue.pop();
            tmp = tmp_node.data;
           
            for (int i = 0; i < tree[tmp].vec_len; i++) {
                queue.push(*tree[tmp].children[i]);
                ++c_tmp;
            }
            if (tree[tmp].rchild != nullptr) {
                queue.push(*tree[tmp].rchild);
                ++c_tmp;
            }
        }
        c = c_tmp;
        c_tmp = 0;
        ++deep;
    }
    return deep;
}
static Elem tree[10000];

void solve() 
{
    int deep_before=0, deep_after=0;
    int input;
    int num = 1;
    while ((input = getchar()) != '#') {
        if (input != 'd'&&input!='u') {
            continue;
        }
        deep_before = Creat_Tree_DFS(tree, input);
       // Print_Tree_BFS(tree);
        ReCreat_Tree_BFS(tree);
        //Print_Tree_BFS(tree);
        deep_after = Calculate_Tree_Deep(tree);
        cout << "Tree " << num << ": " << deep_before << " => " << deep_after << endl;
        ++num;
    }
    return;
}

int main()
{
    int t=1;
    //cin>>t;
    while(t--)
    {
        solve();
    }
}
