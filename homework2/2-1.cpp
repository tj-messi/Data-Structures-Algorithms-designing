#include<iostream>
#include<iomanip>
#include<cstdlib> // for malloc and realloc  
#define STACK_INIT_SIZE 200    // �洢�ռ��ʼ������  
#define STACKINCREMENT 10      // �洢�ռ��������   
#define OVERFLOW -1  
#define MAX_LENGTH 100         // ��������г�����Ϊ100  
using namespace std;


typedef char SElemtype;  
  
typedef struct {  
    SElemtype* base;              // ջ��ָ�룬��ջ����֮ǰ������֮��base��ֵΪNULL  
    SElemtype* top;               // ջ��ָ��  
    int stacksize;                // ջ������,����ǰ�ѷ���Ĵ洢�ռ�  
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
    (*S).stacksize = 0; // ע�⣺���ﲻӦ������stacksizeΪ0����Ϊ����ջ������������Ԫ������  
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
    if (S.top == S.base) return '\0'; // ʹ��'\0'��ʾջ�գ���Ϊ'0'������һ����Ч��ջԪ��  
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
      
    char b[MAX_LENGTH]; // ��վ����  
    char a[MAX_LENGTH * MAX_LENGTH]; // �洢���д���֤�ĳ�վ����  
    int n = 0; // ��ǰ��ȡ���ַ���  
    char input;  
    int count = 0; // ����֤��ջ���еĸ���  
    int length = 0; // �г�����  
      
    // ��ȡ��վ����  
    while ((input = getchar()) != '\n') {  
        b[length++] = input;  
    }  
      
    // ��ȡ����֤�ĳ�վ����  
    char c[MAX_LENGTH]; // ��������֤����  
    int seq_index = 0; // ��ǰ���е�����  
    while ((input = getchar()) != EOF) {  
        if (input != '\n') {  
            a[n++] = input;  
        } else {  
            count++;  
            // ����������з�������ǰ���д洢��c�У�����������  
            for (int i = 0; i < length; i++) {  
                c[i] = a[seq_index * length + i];  
            }  
            // ����Judge�����жϵ�ǰ����  
            if (Judge(stack1, length, c, b)) {  
                cout << "yes" << endl;  
            } else {  
                cout << "no" << endl;  
            }  
            seq_index++; // �ƶ�����һ������  
        }  
    }  
      
    // �������һ�����У����û�л��з�������  
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