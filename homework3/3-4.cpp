#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include<string>
#include <istream>
#include<stack>
#include<queue>
#include<vector>
#define STACK_INIT_SIZE 200    //存储空间初始分配量
#define STACKINCREMENT 30      //存储空间分配增量 
#define OVERFLOW -1
#define MAXSIZE_QUEUE 5000
using namespace std;
//数据结构类：二叉树
struct TreeNode {//定义树结点的结构
    int data;
    TreeNode *children[100];  //children为数组，存放各个子节点的地址
    TreeNode* rchild=nullptr;
    int vec_len = 0;
};    //结点是TreeNode，指针Node保存结点的地址
typedef TreeNode Elem;
 
 
void Print_Tree_BFS(Elem tree[]) {  //根据BFS的打印树
    queue<Elem> queue;
    Elem tmp_node;//存储新建结点地址的临时变量node
    //利用广度优先搜索的方式遍历树
    tmp_node = (tree)[0];
    queue.push(tmp_node);
    cout << (tmp_node).data << " ";//根节点入队并输出
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

int Creat_Tree_DFS(Elem tree[], int in) {  //根据DFS的顺序构建一棵树,并返回树的深度
    int deep_tmp = 0;
    int deep_max = 0;
    stack<Elem>st;
    int i = 0;
    Elem tmp_node;//存储新建结点地址的临时变量node
    int tmp1;
    int tmp2;
    tmp_node.data=i;//将新建结点给tmp_node
    tree[i] = tmp_node;
    st.push(tree[i]);//新结点(直接存储结点即可)存到栈中
    ++i;
 
    int input = in;
    if (input == 'd') {
        tmp_node.data = i;
        tree[i] = tmp_node;
        st.push(tree[i]);//新结点(直接存储结点即可)存到栈中
        ++i;//每次读一个数i加1
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
            st.push(tree[i]);//新结点(直接存储结点即可)存到栈中
            ++i;//每次读一个数i加1
            ++deep_tmp;
        }
        deep_max = deep_max > deep_tmp ? deep_max : deep_tmp;
        if (input == 'u') {
            tmp1 = st.top().data;
            st.pop();
            tmp2 = st.top().data;
            tree[tmp2].children[tree[tmp2].vec_len++]=&tree[tmp1];
            //出栈后建立连接关系
            --deep_tmp;
        }
    }
    //根节点出栈
    st.pop();
    return deep_max;
}
 
void ReCreat_Tree_BFS(Elem tree[]) {   //用广度优先搜索的方式遍历+重构
    Elem tmp_node;
    int tmp;
    queue<Elem> queue;
    //q.InitQueue(queue);
    queue.push(tree[0]);//根节点入队
    while (queue.empty() != 1) {
        tmp_node = queue.front();
        queue.pop();
        
        //遍历子节点
        tmp = tmp_node.data;
        
        if (tmp_node.vec_len >= 1) {
            //先让子节点入队
            for (int i = 0; i < tree[tmp].vec_len; i++) {
                queue.push(*tree[tmp].children[i]);
            }
            for (int i = 0; i < tree[tmp].vec_len; i++) {
                if (i == 0) {   //对第一个子结点，只需要在新的右枝上连接其近邻的兄弟结点即可
                    if (i != tree[tmp].vec_len-1) {   //首先要保证子节点有兄弟结点
                        tree[tmp].children[i]->rchild = tree[tmp].children[i + 1];
                    }
                }
                else {        //对其他结点，除了需要让该子节点连接近邻兄弟节点外，还需要父节点自己与该子节点断开连接
                    if (i != tree[tmp].vec_len - 1) {   //首先要保证子节点有兄弟结点                      
                        tree[tmp].children[i]->rchild = tree[tmp].children[i + 1];
                        for (int j = i; j <= tree[tmp].vec_len - 2; j++) {
                            tree[tmp].children[j] = tree[tmp].children[j + 1];
                        }
                    }   
                    --tree[tmp].vec_len;//断开连接，子节点数量少1
                    --i;
                }
            }
        }
    }
    
}
 
int Calculate_Tree_Deep(Elem tree[]) {  //计算树的深度
    queue<Elem> queue;
   // q.InitQueue(queue);
    Elem tmp_node;//存储新建结点地址的临时变量node
    int tmp = 0;
    //利用广度优先搜索的方式层序遍历树
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
