#include<iostream>
#include<iomanip>
#include<cstdlib> // for malloc and realloc  
#define STACK_INIT_SIZE 200    // 存储空间初始分配量  
#define STACKINCREMENT 10      // 存储空间分配增量   
#define OVERFLOW -1  
#define MAX_LENGTH 100         // 假设最大列车个数为100  
using namespace std;


typedef char SElemtype;  
  
typedef struct {  
    SElemtype* base;              // 栈底指针，在栈构造之前和销毁之后，base的值为NULL  
    SElemtype* top;               // 栈顶指针  
    int stacksize;                // 栈的容量,即当前已分配的存储空间  
} SqStack;  
  
int InitStack(SqStack* S) {  
    (*S).base = (SElemtype*)malloc(STACK_INIT_SIZE * sizeof(SElemtype));  
    if (!(*S).base) exit(OVERFLOW);  
    (*S).top = (*S).base;  
    (*S).stacksize = STACK_INIT_SIZE;  
    return 1;  
}  
  
int ClearStack(SqStack* S) {  
    (*S).top = (*S).base;  
    (*S).stacksize = 0; // 注意：这里不应该设置stacksize为0，因为这是栈的容量，不是元素数量  
    return 0;  
}  
  
int StackEmpty(SqStack S) {  
    return S.base == S.top;  
}  
  
int Push(SqStack& S, SElemtype e) {  
    if (S.top - S.base >= S.stacksize) {  
        S.base = (SElemtype*)realloc(S.base, (S.stacksize + STACKINCREMENT) * sizeof(SElemtype));  
        if (!S.base) exit(OVERFLOW);  
        S.top = S.base + S.stacksize;  
        S.stacksize += STACKINCREMENT;  
    }  
    *S.top++ = e;  
    return 1;  
}  
  
char Pop(SqStack& S) {  
    if (S.top == S.base) return '\0'; // 使用'\0'表示栈空，因为'0'可能是一个有效的栈元素  
    return *(--S.top);  
}  
  
SElemtype GetTop(SqStack S) {  
    if (S.top == S.base) return '\0';  
    return *(S.top - 1);  
}  
  
int Judge(SqStack &S, int length, char c[], char b[]) {  
    int n = 0;  
    ClearStack(&S);  
    for (int r = 0; r < length; r++) {  
        Push(S, b[r]);  
        while (GetTop(S) == c[n]) {  
            Pop(S);  
            n++;  
        }  
    }  
    return StackEmpty(S);  
}  

void solve()
{
     SqStack stack1;  
    InitStack(&stack1);  
      
    char b[MAX_LENGTH]; // 进站序列  
    char a[MAX_LENGTH * MAX_LENGTH]; // 存储所有待验证的出站序列  
    int n = 0; // 当前读取的字符数  
    char input;  
    int count = 0; // 待验证出栈序列的个数  
    int length = 0; // 列车个数  
      
    // 读取进站序列  
    while ((input = getchar()) != '\n') {  
        b[length++] = input;  
    }  
      
    // 读取待验证的出站序列  
    char c[MAX_LENGTH]; // 单个待验证序列  
    int seq_index = 0; // 当前序列的索引  
    while ((input = getchar()) != EOF) {  
        if (input != '\n') {  
            a[n++] = input;  
        } else {  
            count++;  
            // 如果遇到换行符，将当前序列存储到c中，并重置索引  
            for (int i = 0; i < length; i++) {  
                c[i] = a[seq_index * length + i];  
            }  
            // 调用Judge函数判断当前序列  
            if (Judge(stack1, length, c, b)) {  
                cout << "yes" << endl;  
            } else {  
                cout << "no" << endl;  
            }  
            seq_index++; // 移动到下一个序列  
        }  
    }  
      
    // 处理最后一个序列（如果没有换行符结束）  
    if (seq_index * length < n) {  
        for (int i = 0; i < length; i++) {  
            c[i] = a[seq_index * length + i];  
        }  
        if (Judge(stack1, length, c, b)) {  
            cout << "yes" << endl;  
        } else {  
            cout << "no" << endl;  
        }  
    }  
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