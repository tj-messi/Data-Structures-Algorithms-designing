#include <iostream>
#include <vector>
#include <map>
#include <stack>
#include <string>
#include <sstream>
#include <algorithm>
using namespace std;

// ���ڵ��ϵ
map<string, vector<string>> children; // ÿ���ڵ���ӽڵ�
map<string, string> parent;           // ÿ���ڵ�ĸ��ڵ�

// ��������
void parseGenealogy(int n) {
    children.clear();
    parent.clear();

    vector<pair<int, string>> nodes; // �洢ÿ���ڵ�������㼶������
    string line;

    for (int i = 0; i < n; i++) {
        getline(cin, line);
        int level = 0;

        // ͳ�������ո���
        while (level < line.size() && line[level] == ' ') {
            level++;
        }

        string name = line.substr(level);
        nodes.emplace_back(level, name);
    }

    stack<pair<int, string>> ancestors; // ջ����ά����ǰ������
    for (const auto& node : nodes) {
        int level = node.first;
        string name = node.second;

        // �������бȵ�ǰ�ڵ�㼶�ߵĽڵ�
        while (!ancestors.empty() && ancestors.top().first >= level) 
        {
            ancestors.pop();
        }

        // ���ջ��Ϊ�գ���ǰ�ڵ�ĸ��ڵ����ջ��
        if (!ancestors.empty()) {
            string parentName = ancestors.top().second;
            children[parentName].push_back(name);
            parent[name] = parentName;
        }

        // ����ǰ�ڵ���ջ
        ancestors.push({level, name});
    }
}

// ��ѯ�߼�
bool checkQuery(const string& query) {
    istringstream iss(query);
    string x, is, a_or_the, relation, of, y;

    // ��ȡ��ѯ�ĸ�ʽ
    iss >> x >> is >> a_or_the >> relation >> of >> y;
    y=y.substr(0,y.size()-1); // ȥ��ĩβ�Ķ���
    //cout<<x<<" "<<y<<endl;
    //y=y.substr(0,y.size()-3); // ȥ��ĩβ�Ķ���

    if (is != "is" || (of != "of" && relation != "sibling"))
     {
        return false; // �����ʽ����ȷ��ֱ�ӷ��� False
    }
    // ���ݹ�ϵ���ʹ����ѯ
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
        cin.ignore(); // ���Ի��з�
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

        //cout << endl; // ÿ���������������

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
