#include <iostream>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

struct Node {
    char val;
    Node* l;
    Node* r;

    Node(char v) : val(v), l(nullptr), r(nullptr) {}
};

int getPrec(char op) {
    switch (op) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        default:
            return 0;
    }
}

bool isOp(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

string inToPost(const string& infix) {
    stack<char> opStack;
    string postfix;
    for (char c : infix) {
        if (isalpha(c)) {
            postfix += c;
        } else if (c == '(') {
            opStack.push(c);
        } else if (c == ')') {
            while (!opStack.empty() && opStack.top() != '(') {
                postfix += opStack.top();
                opStack.pop();
            }
            opStack.pop(); // pop '('
        } else if (isOp(c)) {
            while (!opStack.empty() && getPrec(opStack.top()) >= getPrec(c)) {
                postfix += opStack.top();
                opStack.pop();
            }
            opStack.push(c);
        }
    }
    while (!opStack.empty()) {
        postfix += opStack.top();
        opStack.pop();
    }
    return postfix;
}

Node* buildTree(const string& postfix) {
    stack<Node*> nodeStack;
    for (char c : postfix) {
        Node* newNode = new Node(c);
        if (isOp(c)) {
            newNode->r = nodeStack.top(); nodeStack.pop();
            newNode->l = nodeStack.top(); nodeStack.pop();
        }
        nodeStack.push(newNode);
    }
    return nodeStack.top();
}

void postOrder(Node* node) {
    if (!node) return;
    postOrder(node->l);
    postOrder(node->r);
    cout << node->val;
}

int getHeight(Node* node) {
    if (!node) return 0;
    return 1 + max(getHeight(node->l), getHeight(node->r));
}

int evalTree(Node* node, const unordered_map<char, int>& vars) {
    if (!node) return 0;
    if (isalpha(node->val)) {
        if (vars.find(node->val) != vars.end()) {
            return vars.at(node->val);
        } else {
            //cerr << "Error: Undefined variable '" << node->val << "'" << endl;
            return 0; // Handle undefined variable error
        }
    }
    int left = evalTree(node->l, vars);
    int right = evalTree(node->r, vars);
    switch (node->val) {
        case '+': return left + right;
        case '-': return left - right;
        case '*': return left * right;
        case '/': 
            if (right != 0) {
                return left / right;
            } else {
                //cerr << "Error: Division by zero" << endl;
                return 0; 
            }
    }
    return 0;
}

void printTree(Node* root, int lvl, int pos, int maxHt, vector<string>& out) {
    if (!root || lvl >= 2 * maxHt - 1) return;
    out[lvl][pos] = root->val;
    if (root->l) {
        out[lvl + 1][pos - 1] = '/';
        printTree(root->l, lvl + 2, pos - (1 << (maxHt - lvl / 2 - 2)), maxHt, out);
    }
    if (root->r) {
        out[lvl + 1][pos + 1] = '\\';
        printTree(root->r, lvl + 2, pos + (1 << (maxHt - lvl / 2 - 2)), maxHt, out);
    }
}

void delTree(Node* node) {
    if (!node) return;
    delTree(node->l);
    delTree(node->r);
    delete node;
}

void solve()
{
    string infx;
    cin >> infx;

    int n;
    cin >> n;
    unordered_map<char, int> vars;
    for (int i = 0; i < n; ++i) {
        char v;
        int val;
        cin >> v >> val;
        vars[v] = val;
    }

    string postfx = inToPost(infx);
    Node* root = buildTree(postfx);
    int ht = getHeight(root);

    cout << postfx << endl;

    int wdth = (1 << (ht - 1)) * 2 - 1;
    vector<string> out(2 * ht - 1, string(wdth, ' '));

    printTree(root, 0, wdth / 2, ht, out);
    for (const string& line : out) {
        cout << line.substr(0, line.find_last_not_of(' ') + 1) << endl;
    }

    int res = evalTree(root, vars);
    cout << res << endl;

    delTree(root);

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
}
