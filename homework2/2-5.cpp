#include <iostream>
#include<cstdlib>
using namespace std;
struct ElemBox {//ÿ���ڵ��Ԫ���򱣴��������ֵ�͸��ڵ������
    long long value;
};
typedef ElemBox elem;
struct quene {
    elem* base;//��ʼ���Ķ�̬����洢�ռ�
    int front;//ͷָ��
    int rear;//βָ��
};
bool InitQuene(quene& Q,int n) {//��ʼ�����ɶ���
    Q.base = (elem*)malloc(n * sizeof(elem));
    Q.front = Q.rear = 0;
    return 1;
}
 
bool Is_Empty(quene Q) {//�ǿշ���1�����ǿշ���0
    if (Q.front == Q.rear) {
        return 1;
    }
    else {
        return 0;
    }
}
bool Is_Full(quene Q,int n) {//�ǿշ���1�����ǿշ���0
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
bool EnQuene(quene& Q,quene &P, long long e,int n,int order) {//orderΪ1������뵥�����У�Ϊ0������������洢����
    if (Is_Full(P, n) == 1) {
        if(order==0){//�������ж���
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
bool DeQueneFront(quene& Q, quene &P,long long &e,int n,int order) {//QΪ�������У�PΪ���ֵ��������
    static int empty=0;
    if (Is_Empty(Q) == 1) {
        if(order==0){      //�������ж���
            cout << "Queue is Empty"<<endl;
        }
        return 0;
    }else{
        
        e = Q.base[Q.front].value;
        Q.front=(Q.front+1)%n;
        if (e == P.base[P.front].value) {    //������ǡ�������ֵʱ���ǵ�Ҫ�����ֵҲ����
            P.front = (P.front + 1) % n;
        }
        cout << e << endl;
        return 1;
    }
}
bool DeQueneRear(quene& Q, long long& e,int n) {      //����������Ҫɾ��β������
    if (Is_Empty(Q) == 1) {
        return 0;
    }
    else {
        e = Q.base[(Q.rear-1)%n].value;
        Q.rear = (Q.rear- 1 )%n;
        return 1;
    }
}
void Creat_Quene(quene &Q,quene &P,long long value,int n) {  //QΪ���ֵ�����У�PΪ�����洢��
    long long e;
    if (Is_Full(P, n) != 1) {
        while (Q.base[(Q.rear - 1) % n].value < value) {//���Խ���ֻ�����������ҪôС�ڵ���ǰ��Ҫô���Ѿ����ˣ��Լ��������ֵ��
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
    quene Q;  //�洢����˳��Ķ���
    quene Q_Max;    //�Ӵ�С�洢�����ֵ����    
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