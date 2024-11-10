#include <iostream>
#include<string>
#include <istream>
#include<vector>
#include<stack>
#include<queue>


#define STACK_INIT_SIZE 200    //存储空间初始分配量
#define STACKINCREMENT 30      //存储空间分配增量 
#define OVERFLOW -1

using namespace std;



typedef pair<int, int> pi;
const int N = 1e5 + 10;
vector<int> g[N];
int res = 0;
int n, start;
bool visited[N] = {false};
 
void bfs(int start) {
    visited[start] = true;
    queue<pi> q;
    q.push({start, 0});
 
    while (!q.empty()) {
        pi current = q.front();
        q.pop();
        int node = current.first;
        int distance = current.second;
 
        for (int neighbor : g[node]) {
            if (!visited[neighbor]) {
                q.push({neighbor, distance + 1});
                res = max(res, distance + 1);
                visited[neighbor] = true;
            }
        }
    }
}

void solve()
{
    cin >> n >> start;
 
    for (int i = 0; i < n; ++i) {
        int l, r;
        cin >> l >> r;
        if (l != -1) {
            g[i].push_back(l);
            g[l].push_back(i);
        }
        if (r != -1) {
            g[i].push_back(r);
            g[r].push_back(i);
        }
    }
 
    bfs(start);
    cout << res << endl;
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