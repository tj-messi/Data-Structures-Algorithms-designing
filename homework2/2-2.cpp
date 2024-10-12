#include<iostream> 
#include<istream>  
#include<iomanip>
#include<cstring>  
#include<string>
#include<cstdlib> // for malloc and realloc  
#define STACK_INIT_SIZE 200    
#define STACKINCREMENT 10     
#define OVERFLOW -1  
#define MAX_LENGTH 100         
using namespace std;

int dp[100005];  
  
int longestValidParentheses(string s, int &start) {  
      
    memset(dp, 0, sizeof(dp));    
    int maxValue = 0;  
    int prev;  
  
       
    for (int i = 1; i < s.size(); i++) {  
        if (s[i] == ')') {  
            prev = i - 1 - dp[i - 1];  
            if (prev >= 0 && s[prev] == '(') {  
                dp[i] = dp[i - 1] + 2;  
                if (prev - 1 >= 0)  
                    dp[i] += dp[prev - 1];  
            }  
        }  
         
        if (dp[i] > maxValue) {  
            start = i - dp[i] + 1;  
            maxValue = dp[i];  
        }  
    }  
    return maxValue;  
}  

void solve()
{
    int start = 0;  
    int ans = 0;  
    string s;  
  
    // 从标准输入读取一整行  
    getline(cin, s);  
  
    // 调用函数计算最长有效括号子串的长度和起始位置  
    ans = longestValidParentheses(s, start);  
  
    // 输出结果  
    cout << ans << " " << start << endl;  
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