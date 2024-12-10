#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

static int cnt = 0;

struct TreeNode {
    int data;
    TreeNode* left;
    TreeNode* right;
};

typedef TreeNode* Node;
struct BinaryTree {
    Node root = NULL;
};

typedef BinaryTree BSTree;

class BST {
public:
    // 创建新节点
    Node CreateNode(int value) {
        Node newNode = (Node)malloc(sizeof(TreeNode));
        newNode->data = value;
        newNode->left = NULL;
        newNode->right = NULL;
        return newNode;
    }

    // 插入新节点
    void Insert(BSTree& tree, int value) {
        Node newNode = CreateNode(value);
        Node current = NULL, parent = NULL;

        if (!tree.root) {
            tree.root = newNode;
        } else {
            current = tree.root;
            // 找到插入位置
            while (current) {
                parent = current;
                if (value <= current->data) {
                    current = current->left;
                } else {
                    current = current->right;
                }
            }

            if (value <= parent->data) {
                parent->left = newNode;
            } else {
                parent->right = newNode;
            }
        }
    }

    // 查找节点
    Node Search(BSTree tree, int value) {
        Node current = NULL;
        if (!tree.root) {
            return NULL;
        } else {
            current = tree.root;
            while (current) {
                if (current->data == value) {
                    return current;
                }
                if (value <= current->data) {
                    current = current->left;
                } else {
                    current = current->right;
                }
            }
            return NULL;
        }
    }

    // 查找父节点
    Node SearchParent(BSTree tree, int value) {
        Node current = NULL, parent = NULL;
        if (!tree.root) {
            return NULL;
        } else {
            current = tree.root;
            while (current) {
                if (current->data == value) {
                    return parent;
                }
                parent = current;
                if (value <= current->data) {
                    current = current->left;
                } else {
                    current = current->right;
                }
            }
            return NULL;
        }
    }

    // 获取最小值节点
    int GetMin(Node root) {
        Node current = NULL;
        if (!root) {
            return -1;
        } else {
            current = root;
            while (current->left) {
                current = current->left;
            }
            return current->data;
        }
    }

    // 查找某个值出现的次数
    int SearchAll(BSTree tree, int value) {
        Node current;
        if (Search(tree, value) == NULL) { // 如果节点不存在
            return 0;
        } else {
            current = tree.root;
            while (current != NULL) {
                if (current->data == value) {
                    ++cnt;
                    tree.root = current->left;
                    SearchAll(tree, value);
                    return 1;
                }
                if (value <= current->data) {
                    current = current->left;
                } else {
                    current = current->right;
                }
            }
        }
        return 0;
    }

    // 查找前驱节点
    int SearchPre(BSTree& tree, int value) {
        Node current = NULL, parent = NULL;
        if (!tree.root) {
            return -1;
        }
        if (GetMin(tree.root) >= value) {
            return -1;
        } else {
            current = tree.root;
            while (current != NULL) {
                parent = current;
                if (value <= current->data) {
                    current = current->left;
                    if (current->data < value && (!current->right || GetMin(current->right) >= value))
                        return current->data;
                } else {
                    current = current->right;
                    if (!current)
                        return parent->data;
                    else if (current->data >= value && (!current->left || GetMin(current) >= value))
                        return parent->data;
                }
            }
        }
        return -1;
    }

    // 删除节点
    int Delete(BSTree& tree, int value) {
        Node current = NULL, parent = NULL, temp = NULL;
        if (Search(tree, value) == NULL) { // 如果节点不存在
            return 0;
        } else {
            current = Search(tree, value);
            if (!current->left && !current->right) {  // 叶子节点
                parent = SearchParent(tree, value);
                if (parent->right == current) parent->right = NULL;
                if (parent->left == current) parent->left = NULL;
                free(current);
            } else if (current->right && !current->left) {  // 只有右子树
                temp = current->right;
                current->data = temp->data;
                current->right = temp->right;
                current->left = temp->left;
                free(temp);
            } else if (current->left && !current->right) {  // 只有左子树
                temp = current->left;
                current->data = temp->data;
                current->left = temp->left;
                current->right = temp->right;
                free(temp);
            } else {  // 左右子树都有
                temp = current;
                parent = current->left;
                // 找到左子树最右侧的节点
                while (parent->right) {
                    temp = parent;
                    parent = parent->right;
                }
                current->data = parent->data;  // 替换值
                if (temp != current) {  // 左子树有右子树
                    temp->right = parent->left;
                } else {  // 左子树无右子树
                    temp->left = parent->left;
                    free(parent);
                    parent = NULL;
                }
            }
            return 1;
        }
    }
};

static BST BinarySearchTree;

void solve() {
    BSTree tree;
    int n, operation, value;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> operation;
        if (operation != 4) cin >> value;
        
        if (operation == 1) {
            BinarySearchTree.Insert(tree, value);
        } else if (operation == 2) {
            if (BinarySearchTree.Delete(tree, value) == 0) {
                cout << "None" << endl;
            }
        } else if (operation == 3) {
            cnt = 0;
            BinarySearchTree.SearchAll(tree, value);
            cout << cnt << endl;
        } else if (operation == 4) {
            cout << BinarySearchTree.GetMin(tree.root) << endl;
        } else if (operation == 5) {
            int pre = BinarySearchTree.SearchPre(tree, value);
            if (pre == -1) {
                cout << "None" << endl;
            } else {
                cout << pre << endl;
            }
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