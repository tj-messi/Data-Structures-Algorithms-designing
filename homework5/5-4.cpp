#include <iostream>
#include <vector>
#include <map>
#include <stack>
#include <string>
#include <sstream>
#include <algorithm>
using namespace std;

// 树节点关系
map<string, vector<string>> children; // 每个节点的子节点
map<string, string> parent;           // 每个节点的父节点

// 解析家谱
void parseGenealogy(int n) {
    children.clear();
    parent.clear();

    vector<pair<int, string>> nodes; // 存储每个节点的缩进层级和名字
    string line;

    for (int i = 0; i < n; i++) {
        getline(cin, line);
        int level = 0;

        // 统计缩进空格数
        while (level < line.size() && line[level] == ' ') {
            level++;
        }

        string name = line.substr(level);
        nodes.emplace_back(level, name);
    }

    stack<pair<int, string>> ancestors; // 栈用于维护当前祖先链
    for (const auto& node : nodes) {
        int level = node.first;
        string name = node.second;

        // 弹出所有比当前节点层级高的节点
        while (!ancestors.empty() && ancestors.top().first >= level) 
        {
            ancestors.pop();
        }

        // 如果栈不为空，当前节点的父节点就是栈顶
        if (!ancestors.empty()) {
            string parentName = ancestors.top().second;
            children[parentName].push_back(name);
            parent[name] = parentName;
        }

        // 将当前节点入栈
        ancestors.push({level, name});
    }
}

// 查询逻辑
bool checkQuery(const string& query) {
    istringstream iss(query);
    string x, is, a_or_the, relation, of, y;

    // 读取查询的格式
    iss >> x >> is >> a_or_the >> relation >> of >> y;
    y=y.substr(0,y.size()-1); // 去掉末尾的逗号
    //cout<<x<<" "<<y<<endl;
    //y=y.substr(0,y.size()-3); // 去掉末尾的逗号

    if (is != "is" || (of != "of" && relation != "sibling"))
     {
        return false; // 如果格式不正确，直接返回 False
    }
    // 根据关系类型处理查询
    if (relation == "child")
    {
        // X is a child of Y
        return (parent.find(x) != parent.end())&& parent[x] == y;
    } 
    else if (relation == "parent")
    {
        // X is the parent of Y
        return children.find(x) != children.end() &&
               find(children[x].begin(), children[x].end(), y) != children[x].end();
    } 
    else if (relation == "sibling") 
    {
        // X is a sibling of Y
        if (parent.find(x) == parent.end() || parent.find(y) == parent.end()) return false;
        return parent[x] == parent[y] ;
    } 
    else if (relation == "descendant") 
    {
        // X is a descendant of Y
        if(x==y)return true;
        string current = x;
        while (parent.find(current) != parent.end()) {
            current = parent[current];
            if (current == y) return true;
        }
        return false;
    } 
    else if (relation == "ancestor")
    {
        // X is an ancestor of Y
        if(x==y)return true;
        string current = y;
        while (parent.find(current) != parent.end()) {
            current = parent[current];
            if (current == x) return true;
        }
        return false;
    }

    return false;
}

int main() {
    while (true) {
        int n, m;
        cin >> n >> m;
        cin.ignore(); // 忽略换行符
        if (n == 0 && m == 0) {
            //cout<<endl;
            break;
        }

        

        parseGenealogy(n);

        vector<string> queries(m);
        for (int i = 0; i < m; i++) {
            getline(cin, queries[i]);
        }

        for (const auto& query : queries) {
            cout << (checkQuery(query) ? "True" : "False") << endl;
        }

        //cout << endl; // 每个测试用例后空行

        // for(auto it = children.begin(); it!= children.end(); it++)
        // {
        //     cout << it->first << "->" << it->second.size() << endl;
        //     for(auto it2 = it->second.begin(); it2!= it->second.end(); it2++)
        //     {
        //         cout << "->" << *it2 << endl;
        //     }
        // }
        // cout << endl;
        // for(auto it = parent.begin(); it!= parent.end(); it++)
        // {
        //     cout << it->first << "->" << it->second << endl;
        // }
        cout<<endl;
    }

    return 0;
}
