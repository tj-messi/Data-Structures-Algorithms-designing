#include<iostream>
#include<iomanip>
#include<cstdlib> // for malloc and realloc  
#define STACK_INIT_SIZE 200    
#define STACKINCREMENT 10     
#define OVERFLOW -1  
#define MAX_LENGTH 100         
using namespace std;
 
struct Node {  
    long long data;  
};  
  
 
struct CustomQueue {  
    Node* elements;  // 动态分配存储空间  
    int head;        // 头指针  
    int tail;        // 尾指针  
    int capacity;    // 队列容量  
};  
  

bool InitializeQueue(CustomQueue& queue, int capacity) {  
    queue.elements = (Node*)malloc(capacity * sizeof(Node));  
    if (queue.elements == nullptr) return false;  
    queue.head = queue.tail = 0;  
    queue.capacity = capacity;  
    return true;  
}  
   
bool IsEmpty(const CustomQueue& queue) {  
    return queue.head == queue.tail;  
}  
  
 
bool IsFull(const CustomQueue& queue) {  
    return (queue.tail + 1) % queue.capacity == queue.head;  
}  
  
  
void PrintQueue(const CustomQueue& queue) {  
    int index = queue.head;  
    while (index != queue.tail) {  
        cout << queue.elements[index].data << " ";  
        index = (index + 1) % queue.capacity;  
    }  
    cout << endl;  
}  
  
  
bool Enqueue(CustomQueue& normalQueue, CustomQueue& maxQueue, long long value) {  
    if (IsFull(normalQueue)) {  
        cout << "Queue is Full" << endl;  
        return false;  
    }   
    normalQueue.elements[normalQueue.tail].data = value;  
    normalQueue.tail = (normalQueue.tail + 1) % normalQueue.capacity;  
  
    maxQueue.elements[maxQueue.tail].data = value;  
    maxQueue.tail = (maxQueue.tail + 1) % maxQueue.capacity;  
  
    return true;  
}  
  
bool DequeueFront(CustomQueue& normalQueue, CustomQueue& maxQueue, long long& value) {  
    if (IsEmpty(normalQueue)) {  
        cout << "Queue is Empty" << endl;  
        return false;  
    }  
    value = normalQueue.elements[normalQueue.head].data;  
    normalQueue.head = (normalQueue.head + 1) % normalQueue.capacity;  
   
    if (!IsEmpty(maxQueue) && maxQueue.elements[maxQueue.head].data == value) {  
        maxQueue.head = (maxQueue.head + 1) % maxQueue.capacity;  
    }  
    return true;  
}  
  
  
bool DequeueRear(CustomQueue& queue, long long& value) {  
    if (IsEmpty(queue)) {  
        return false;  
    }   
    queue.tail = (queue.tail - 1 + queue.capacity) % queue.capacity;  
    value = queue.elements[queue.tail].data;  
    return true;  
}  
  
 
void MaintainQueues(CustomQueue& maxQueue, CustomQueue& normalQueue, long long value) {  
    long long removedValue;  
      
    while (!IsEmpty(maxQueue) && maxQueue.elements[(maxQueue.tail - 1 + maxQueue.capacity) % maxQueue.capacity].data < value) {  
        DequeueRear(maxQueue, removedValue);  
    }  
    Enqueue(normalQueue, maxQueue, value);  
}  
  
// 获取最大值  
void GetMax(const CustomQueue& maxQueue) {  
    if (IsEmpty(maxQueue)) {  
        cout << "Queue is Empty" << endl;  
    } else {  
        cout << maxQueue.elements[maxQueue.head].data << endl;  
    }  
} 

void solve()
{
    CustomQueue normalQueue, maxQueue;  
    int capacity;  
    long long value;  
  
    cin >> capacity;  
    ++capacity;  
  
    if (!InitializeQueue(normalQueue, capacity) || !InitializeQueue(maxQueue, capacity)) {  
        cout << "Failed to initialize queues." << endl;  
        return;  
    }  
  
    string command;  
    while (cin >> command && command != "quit") {  
        if (command == "dequeue") {  
            DequeueFront(normalQueue, maxQueue, value);  
        } else if (command == "enqueue") {  
            cin >> value;  
            MaintainQueues(maxQueue, normalQueue, value);  
        } else if (command == "max") {  
            GetMax(maxQueue);  
        }  
    }  
  
    PrintQueue(normalQueue);  
    return;  
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