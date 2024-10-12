#include<iostream>
#include<iomanip>
#include<cstdlib> // for malloc and realloc         
using namespace std;
#define STACK_INIT_SIZE 200    
#define STACKINCREMENT 10      
#define OVERFLOW -1

struct Elem {
    char fuhao;
    int priority;
    int L_R;
};
typedef struct
{
    Elem* base;              
    Elem* top;               
    int stacksize;                
}SqStack;
typedef struct
{
    char* base;              
    char* top;              
    int stacksize;               
}SqStack2;
int InitStack(SqStack* S)
{
    (*S).base = (Elem*)malloc(STACK_INIT_SIZE * sizeof(Elem));    
    if (!(*S).base) exit(OVERFLOW);                 
    (*S).top = (*S).base;                             
    (*S).stacksize = STACK_INIT_SIZE;               
    return 1;
}
int ClearStack(SqStack* S)
{
    (*S).top = (*S).base;                            
    (*S).stacksize = 0;
    return 0;
}
int StackEmpty(SqStack S)
{
    if (S.base == S.top)                        
        return 1;
    else
        return 0;
}
int Push(SqStack& S, Elem e)
{
    if (S.top - S.base >= S.stacksize)          
    {
        S.base = (Elem*)realloc(S.base, (S.stacksize + STACKINCREMENT) * sizeof(Elem));
        if (!S.base) exit(OVERFLOW);             
        S.top = S.base + S.stacksize;
        S.stacksize += STACKINCREMENT;
    }
    *S.top++ = e;                                  
    return 1;
}
Elem Pop(SqStack& S)
{
    return *(--S.top);                                
}
Elem GetTop(SqStack S)
{
    return *(S.top - 1);               
}
int InitStack2(SqStack2* S)
{
    (*S).base = (char*)malloc(STACK_INIT_SIZE * sizeof(char));   
    if (!(*S).base) exit(OVERFLOW);                
    (*S).top = (*S).base;                            
    (*S).stacksize = STACK_INIT_SIZE;              
    return 1;
}
int ClearStack2(SqStack2* S)
{
    (*S).top = (*S).base;                            
    (*S).stacksize = 0;
    return 0;
}
int StackEmpty2(SqStack2 S)
{
    if (S.base == S.top)                        
        return 1;
    else
        return 0;
}
int Push2(SqStack2& S, char e)
{
    if (S.top - S.base >= S.stacksize)           
    {
        S.base = (char*)realloc(S.base, (S.stacksize + STACKINCREMENT) * sizeof(char));
        if (!S.base) exit(OVERFLOW);             
        S.top = S.base + S.stacksize;
        S.stacksize += STACKINCREMENT;
    }
    *S.top++ = e;                                  
    return 1;
}
char Pop2(SqStack2& S)
{
    return *(--S.top);     
}                           
char GetTop2(SqStack2 S)
{
    return *(S.top - 1);  
}             
void Change_Top_Priority(SqStack &S,int e) {
    (*(S.top-1)).priority = e;
}
void calculate_and(SqStack2* VF_stack) {
    char VF1 = GetTop2(*VF_stack);
    Pop2(*VF_stack);
    char VF2 = GetTop2(*VF_stack);
    Pop2(*VF_stack);
    char VF;
    if (VF1 == 'V' && VF2 == 'V') {
        VF = 'V';
    }
    else {
        VF = 'F';
    }
    Push2(*VF_stack,VF);
}
void calculate_not(SqStack2* VF_stack) {
    char VF = GetTop2(*VF_stack);
    Pop2(*VF_stack);
    if (VF == 'V')
        VF = 'F';
    else
        VF = 'V';
    Push2(*VF_stack, VF);
 
}
void calculate_or(SqStack2* VF_stack) {
    char VF1 = GetTop2(*VF_stack);
    Pop2(*VF_stack);
    char VF2 = GetTop2(*VF_stack);
    Pop2(*VF_stack);
    char VF;
    if (VF1 == 'F' && VF2 == 'F') {
        VF = 'F';
    }
    else {
        VF = 'V';
    }
    Push2(*VF_stack, VF);
}

void solve()
{
     Elem elem;
    SqStack2 VF_stack;
    InitStack2(&VF_stack);
    SqStack fuhao_stack;
    InitStack(&fuhao_stack);
    char input;
    int count = 0;
        while (1) {
            input = getchar();
            if (input == EOF)
                break;
            if (input == '\n')
                ++count;
                if (input != 32) {
                    if (input == 'V' || input == 'F') {
                        Push2(VF_stack, input);
                    }
                    if (input == '!' || input == '&' || input == '|' || input == '(' || input == ')' || input == '\n' || input == EOF) {
                        if (input == '!') {
                            elem.fuhao = '!';
                            elem.priority = 2;
                            elem.L_R = 0;
                        }
                        if (input == '(') {
                            elem.fuhao = '(';
                            elem.priority = 1;
                            elem.L_R = 1;
                        }
                        if (input == ')') {
                            elem.fuhao = ')';
                            elem.priority = 5;
                            elem.L_R = 1;
                        }
                        if (input == '&') {
                            elem.fuhao = '&';
                            elem.priority = 3;
                            elem.L_R = 1;
                        }
                        if (input == '|') {
                            elem.fuhao = '|';
                            elem.priority = 4;
                            elem.L_R = 1;
                        }
                        if (input == '\n'||input==EOF) {
                            elem.fuhao = '\n';
                            elem.priority = 6;
                            elem.L_R = 2;
                            elem.L_R = 2;
                        }
                        if (StackEmpty(fuhao_stack) == true) {
                            Push(fuhao_stack,elem);
                        }
                        else {
                            while (elem.priority > GetTop(fuhao_stack).priority || (elem.priority == GetTop(fuhao_stack).priority && (elem.L_R == 1 || elem.L_R == 2)))
                            {
                                if (StackEmpty(fuhao_stack) == true) {
                                    break;
                                }
                                if (GetTop(fuhao_stack).fuhao == '!') {
                                    calculate_not(&VF_stack);
                                    Pop(fuhao_stack);
                                    if (StackEmpty(fuhao_stack)) {
                                        break;
                                    }
                                    continue;
                                }
                                if (GetTop(fuhao_stack).fuhao == '&') {
                                    calculate_and(&VF_stack);
                                    Pop(fuhao_stack);
                                    if (StackEmpty(fuhao_stack)) {
                                        break;
                                    }
                                    continue;
 
                                }
                                if (GetTop(fuhao_stack).fuhao == '|') {
                                    calculate_or(&VF_stack);
                                    Pop(fuhao_stack);
                                    if (StackEmpty(fuhao_stack)) {
                                        break;
                                    }
                                    continue;
                                }
                                if (GetTop(fuhao_stack).fuhao == '(') {
                                    if (elem.fuhao == ')') {
                                
                                        Pop(fuhao_stack);
                                        break;
                                    }
                                    else {
                                        break;
                                    }
                                }
                              
                            }
                            Push(fuhao_stack, elem);
 
                            if (GetTop(fuhao_stack).fuhao == '(') {
                                Change_Top_Priority(fuhao_stack, 5);
                            }
                            if (GetTop(fuhao_stack).fuhao == ')') {
                                Pop(fuhao_stack);
                            }
                        }
 
 
                    }
                }
 
            if (!StackEmpty(fuhao_stack)) {
                if (GetTop(fuhao_stack).fuhao == '\n'|| GetTop(fuhao_stack).fuhao == EOF) {
                    cout << "Expression " <<count<< ":" << " " << GetTop2(VF_stack) << endl;
                    ClearStack(&fuhao_stack);
                }
            }
        }
        cout << endl;
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