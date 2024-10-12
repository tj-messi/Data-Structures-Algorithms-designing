#include<iostream>
#include<iomanip>
#include<cstdlib> // for malloc and realloc  
#define STACK_INIT_SIZE 200    
#define STACKINCREMENT 10     
#define OVERFLOW -1  
#define MAX_LENGTH 100    
#define QUEUE_MAX_SIZE 1000001      
using namespace std;

static int grid[1003][1003];  
  
struct Point {  
    int x;  
    int y;  
};  
  
struct Queue {  
    Point* data;  
    int head;  
    int tail;  
};  
  
bool initializeQueue(Queue &q) {  
    q.data = (Point*)malloc(QUEUE_MAX_SIZE * sizeof(Point));  
    q.head = q.tail = 0;  
    return true;  
}  
  
bool enqueue(Queue &q, Point p) {  
    q.data[q.tail] = p;  
    q.tail++;  
    return true;  
}  
  
bool dequeue(Queue &q, Point &p) {  
    if (q.head < q.tail) {  
        p = q.data[q.head];  
        q.head++;  
        return true;  
    }  
    return false;  
}  
  
bool isEmpty(Queue &q) {  
    return q.head == q.tail;  
}  
  
void Grid(int (*grid)[1003], int &n, int &m) {  
    int k;  
    cin >> n >> m;  
    for (int i = 0; i <= n + 1; i++) {  
        for (int j = 0; j <= m + 1; j++) {  
            if (i == 0 || i == n + 1 || j == 0 || j == m + 1) {  
                grid[i][j] = -2;   
            } else {  
                cin >> k;  
                grid[i][j] = k;     
            }  
        }  
    }  
}  
  
void printGrid(int (*grid)[1003], int n, int m) {  
    for (int i = 0; i <= n + 1; i++) {  
        for (int j = 0; j <= m + 1; j++) {  
            cout << grid[i][j] << "  ";  
        }  
        cout << endl;  
    }  
}  
  
int checkPoint(int (*grid)[1003], int x, int y) {  
    if (grid[x][y] == -2) return 2; 
    if (grid[x][y] == -1 || grid[x][y] == 0) return 0;  
    if (grid[x][y] == 1) return 1;  
    return -1;  
}  
  
int searchConnectedArea(int (*grid)[1003], Queue &q, int x0, int y0) {  
    Point p;  
    int connectedCount = 1;  
    int edgeCount = 0;  
    int x, y, dx, dy;  
    int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};  
  
    p.x = x0;  
    p.y = y0;  
    grid[x0][y0] = -1;  
  
    
    if (grid[x0-1][y0] == -2 || grid[x0][y0-1] == -2 || grid[x0+1][y0] == -2 || grid[x0][y0+1] == -2) {  
        edgeCount++;  
    }  
  
    enqueue(q, p);  
  
    while (!isEmpty(q)) {  
        dequeue(q, p);  
        x = p.x;  
        y = p.y;  
  
        for (int i = 0; i < 4; i++) {  
            dx = x + directions[i][0];  
            dy = y + directions[i][1];  
  
            if (checkPoint(grid, dx, dy) == 1) {  
                p.x = dx;  
                p.y = dy;  
                enqueue(q, p);  
                grid[dx][dy] = -1;  
                connectedCount++;  
  
                
                if (grid[dx-1][dy] == -2 || grid[dx][dy-1] == -2 || grid[dx+1][dy] == -2 || grid[dx][dy+1] == -2) {  
                    edgeCount++;  
                }  
            }  
        }  
    }  
  
   
    return (connectedCount == edgeCount) ? 0 : 1;  
}  

void solve()
{
    int n, m;  
    int dAreaCount = 0;  
    Queue q;  
  
    initializeQueue(q);  
    Grid(grid, n, m);  
  
    for (int i = 1; i <= n; i++) {  
        for (int j = 1; j <= m; j++) {  
            if (grid[i][j] == 1) {  
                if (searchConnectedArea(grid, q, i, j) == 1) {  
                    dAreaCount++;  
                }  
            }  
        }  
    }  
  
    cout << dAreaCount << endl;  
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