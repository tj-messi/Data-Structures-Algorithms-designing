#include <iostream>
#include<cstdlib>
using namespace std;
struct ElemBox {//每个节点的元素域保存的是坐标值和父节点的索引
    long long value;
};
typedef ElemBox elem;
struct quene {
    elem* base;//初始化的动态分配存储空间
    int front;//头指针
    int rear;//尾指针
};
bool InitQuene(quene& Q,int n) {//初始化生成队列
    Q.base = (elem*)malloc(n * sizeof(elem));
    Q.front = Q.rear = 0;
    return 1;
}
 
bool Is_Empty(quene Q) {//是空返回1，不是空返回0
    if (Q.front == Q.rear) {
        return 1;
    }
    else {
        return 0;
    }
}
bool Is_Full(quene Q,int n) {//是空返回1，不是空返回0
    if (Q.front == (Q.rear+1)%n) {
        return 1;
    }
    else {
        return 0;
    }
}
void Print_Quene(quene Q, int n) {
    while (((Q.front) % n) != Q.rear) {
        cout << Q.base[Q.front].value << " ";
        Q.front = (Q.front + 1) % n;
    }
}
bool EnQuene(quene& Q,quene &P, long long e,int n,int order) {//order为1代表加入单减序列，为0代表加入正常存储序列
    if (Is_Full(P, n) == 1) {
        if(order==0){//对正常列而言
            cout << "Queue is Full"<<endl;
        }
        return 0;
    }else{
        Q.base[Q.rear].value = e;
        Q.rear = (Q.rear+1)%n;
        P.base[P.rear].value = e;
        P.rear = (P.rear + 1) % n;
        
        return 1;
    }
}
bool DeQueneFront(quene& Q, quene &P,long long &e,int n,int order) {//Q为正常序列，P为最大值单减序列
    static int empty=0;
    if (Is_Empty(Q) == 1) {
        if(order==0){      //对正常列而言
            cout << "Queue is Empty"<<endl;
        }
        return 0;
    }else{
        
        e = Q.base[Q.front].value;
        Q.front=(Q.front+1)%n;
        if (e == P.base[P.front].value) {    //出的数恰好是最大值时，记得要把最大值也出列
            P.front = (P.front + 1) % n;
        }
        cout << e << endl;
        return 1;
    }
}
bool DeQueneRear(quene& Q, long long& e,int n) {      //单减队列需要删除尾部操作
    if (Is_Empty(Q) == 1) {
        return 0;
    }
    else {
        e = Q.base[(Q.rear-1)%n].value;
        Q.rear = (Q.rear- 1 )%n;
        return 1;
    }
}
void Creat_Quene(quene &Q,quene &P,long long value,int n) {  //Q为最大值单减列，P为正常存储列
    long long e;
    if (Is_Full(P, n) != 1) {
        while (Q.base[(Q.rear - 1) % n].value < value) {//可以进列只有两种情况，要么小于等于前，要么列已经空了（自己就是最大值）
            DeQueneRear(Q, e, n);
            if (Q.rear == Q.front) {
                break;
            }
        }
    }
    EnQuene(Q,P, value,n,0);
}
void Get_Max(quene Q,quene P,int n) {
    if (Is_Empty(P) == 1) {
        cout << "Queue is Empty"<<endl;
    }else{
        cout << Q.base[Q.front].value << endl;
    }
}
int main() {
    quene Q;  //存储正常顺序的队列
    quene Q_Max;    //从大到小存储的最大值队列    
    long long n;
    long long e;
    cin >> n;
    ++n;
    InitQuene(Q,n);
    InitQuene(Q_Max,n);
    string command = " ";
    while (command != "quit") {
        cin >> command;
        if (command == "dequeue") {
            DeQueneFront(Q,Q_Max,e,n,0);
            
        }
        if (command == "enqueue") {
            cin >> e;
            Creat_Quene(Q_Max, Q, e, n);
        }
        if (command == "max") {
            Get_Max(Q_Max,Q,n);
        }
    }
    Print_Quene(Q,n);
    cout << endl;
    return 0;
}