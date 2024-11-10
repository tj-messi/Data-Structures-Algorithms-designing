#include <iostream>
#include <vector>
using namespace std;

struct TreeNode {
    int data;
    int parent = -1;
    int back_a = -1;
    int back_b = -1;
};

struct Question {
    int a;
    int b;
};

int CreateTree(TreeNode Tree[], int N) {
    int a, b;
    int root = 0;
    for (int i = 0; i < N - 1; ++i) {
        cin >> a >> b;
        Tree[a].data = a;
        Tree[b].data = b;
        Tree[b].parent = a;
    }
    for (int i = 1; i <= N; i++) {
        if (Tree[i].parent == -1)
            root = i;
    }
    return root;
}

void GetQuestions(Question Q[], int M) {
    for (int i = 0; i < M; i++) {
        cin >> Q[i].a >> Q[i].b;
    }
}

int FindCommonAncestor(TreeNode Tree[], int root, int a, int b) {
    int p = a;
    int q = b;
    if (p == q) {
        return p;
    } else {
        while (true) {
            if (p != root)
                p = Tree[p].parent;
            else
                p = Tree[p].back_a;
            if (q != root)
                q = Tree[q].parent;
            else
                q = Tree[q].back_b;
            if (p == q)
                break;
        }
    }
    return p;
}

void FindAncestors(TreeNode Tree[], Question Q[], int root, int M) {
    for (int i = 0; i < M; i++) {
        Tree[root].back_a = Q[i].b;
        Tree[root].back_b = Q[i].a;
        cout << FindCommonAncestor(Tree, root, Q[i].a, Q[i].b) << endl;
    }
}

static TreeNode Tree[100][1000]; // 100 trees with 1000 nodes each
static Question Q[100][1000];    // 100 sets of questions

void solve() 
{
    int n;
    cin >> n;
    int N[100], M[100];
    int root[100];
    for (int i = 0; i < n; i++) {
        cin >> N[i] >> M[i];
        root[i] = CreateTree(Tree[i], N[i]);
        GetQuestions(Q[i], M[i]);
        FindAncestors(Tree[i], Q[i], root[i], M[i]);
    }
    return;
}

int main()
{
    int t = 1;
    //cin >> t;
    while (t--)
    {
        solve();
    }
}