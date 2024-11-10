#include <iostream>
#include<string>
#include <algorithm>  // 包含这个头文件来使用 reverse 函数
#include <vector>
#include <istream>
#include<vector>
#include<stack>

#define STACK_INIT_SIZE 200    //存储空间初始分配量
#define STACKINCREMENT 30      //存储空间分配增量 
#define OVERFLOW -1

using namespace std;

typedef struct TreeNode {//定义树结点的结构
    char data;
    struct TreeNode* lchild;
    struct TreeNode* rchild;
}*Node, Elem;    //结点是TreeNode，指针Node保存结点的地址
typedef struct {//定义树的结构
    Node root;
}Tree;
class BinaryTree {
public:
    int InitTree(Tree* t) {//初始化二叉树
        if (t == NULL)
            return -1;
        Node node = (Node)malloc(sizeof(struct TreeNode));//为结点初始化内存空间
        //定义根节点
        t->root = node;
        //左右指针指向空
        (t->root)->lchild = NULL;   
        (t->root)->rchild = NULL;
 
        return 1;
    }
    int Makenode(vector<Node> &temp_r,char e,int j) {   //创建新结点，其地址为*node，结点值为e
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
//功能函数：根据出入栈操作获取中序遍历的序列,返回值为
void Get_Midorder_Preorder(int n, vector<char>& midorder, vector<char>& preorder) {
    stack<Elem> st;
    int N = 2 * n;
    string command;
    Elem temp;
    for (int i = 1; i <= N;i++) {
        cin >> command;
        if (command == "push") { //如果是压栈操作
            cin >> temp.data;
            st.push( temp);//把结点放到栈里面
            (preorder).push_back(temp.data);
        }
        if (command == "pop") {     //如果是出栈操作
            temp = st.top();
            st.pop();    //结点出栈
            (midorder).push_back(temp.data);//出的元素放到线性表里
        }
    }
}
static vector<Node> temp_r(200);//存放待连接的右结点
static vector<Node> temp_l(200);//存放待连接的右结点
//功能函数：根据前序和中序序列用迭代法创建树
void CreatTree(Tree& tree, vector<char>preorder, vector<char>midorder) {
    stack<Node>st;
    int i =0;//遍历先序序列的计数结点
    int j = 0;//遍历中序序列的计数结点
    int k;
    char root_elem = preorder[i];
    ((&tree)->root)->data = root_elem;//填入根节点的元素
    st.push((&tree)->root);//把结点的地址入栈保存：这样做的目的有两个，第一保存构建信息，第二保存结点地址方便直接访问结点并进行连接
    ++i;
    Node tmp_linked= ((&tree)->root);//被连接的父节点
    while (i <= preorder.size() - 1) {
        //在中序序列中，比较当前遍历位置与栈顶（即上一个先序遍历元素的关系)
        if (midorder[j] == st.top()->data) {
            t.Makenode(temp_r, preorder[i], i);//新建待连接的右节点，由于会新建很多右节点，可以开一个链表来单独存放他们的信息
            k = j;//保护一下j，因为后面还要用到
            while (1) {  //在树中从下向上，寻找该右结点应当连接的父节点
                if (!st.empty()&&midorder[k] == st.top()->data){
                    tmp_linked = st.top();//tmp_linked存放了最后出栈结点
                    st.pop();
                }
                else
                    break;
                ++k;
            }
            (tmp_linked)->rchild = temp_r[i];//连接到右节点上
            st.push(temp_r[i]);//不要忘了每遍历一个就要入一个的栈，这里是将遍历得到的新连接右节点入栈
            j = k;
        }
        else if (midorder[j] != st.top()->data) {
            t.Makenode(temp_l, preorder[i], i);//新建待连接的左节点，存放元素是先序序列当前指向的元素，同样也会新建很多左节点，故要用链表来分别存放
            tmp_linked = st.top();
            (tmp_linked)->lchild = temp_l[i];//左节点直接连到上一个元素
            st.push(temp_l[i]);
        }
        else;
        ++i;
    }
}
void PostTraverse(Tree tree, stack<Elem> st, vector<char>& postorder) {
    Elem postorder_elem;
 
    st.push(*((&tree)->root));//将首节点存到栈中
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
    Get_Midorder_Preorder(n, midorder, preorder);//模拟进出栈过程，获取中序遍历的结果
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