#include<iostream>
#include<iomanip>
#include<cstdlib> // for malloc and realloc  
#define STACK_INIT_SIZE 200    
#define STACKINCREMENT 10     
#define OVERFLOW -1  
#define MAX_LENGTH 100         
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
    if (S.top == S.base) return '\0'; 
    return *(--S.top);  
}  
  
SElemtype GetTop(SqStack S) {  
    if (S.top == S.base) return '\0';  
    return *(S.top - 1);  
}  
  
int Judge(SqStack &S, int length, char c[], char b[]) {  
    int n = 0;  
    
      
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
      
    char b[MAX_LENGTH]; 
    char a[MAX_LENGTH * MAX_LENGTH]; 
    int n = 0;   
    char input;  
    int count = 0;
    int length = 0; 
      
    
    while ((input = getchar()) != '\n') {  
        b[length++] = input;  
    }  
      

    char c[MAX_LENGTH]; 
    int seq_index = 0;   
    while ((input = getchar()) != EOF) {  
        if (input != '\n') {  
            a[n++] = input;  
        } else {  
            count++;    
            for (int i = 0; i < length; i++) {  
                c[i] = a[seq_index * length + i];  
            }  
            if (Judge(stack1, length, c, b)) {  
                cout << "yes" << endl;  
            } else {  
                cout << "no" << endl;  
            }  
            seq_index++;
        }  
    }  
       
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