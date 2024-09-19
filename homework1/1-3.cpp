#include <iostream>  
#include <cstdio>  
#include <iomanip>  
#include <cstring>  
  
using namespace std;  
  
// 获取数组k的非零长度  
int GetLen_k(int k[], int len_all) {  
    int len_k = 0;  
    while (len_k < len_all && k[len_all - len_k - 1] == 0) {  
        ++len_k;  
    }  
    return len_all - len_k;  
}  
  
int main() {  
    int N;  
    string s_A;  
    cin >> N >> s_A;  
  
    // 确保数组A有足够的空间，并初始化为0  
    int A[10002] = {0};  
    int len_A = s_A.size();  
    for (int h = 0; h < len_A; h++) {  
        A[h] = s_A[len_A - h - 1] - '0';  
    }  
  
    // 初始化其他数组  
    int k[10002] = {0};  
    int sum[10002] = {0};  
    int middle[10002] = {0};  
    int carry = 0;  
  
    // 对第i项  
    for (int i = 1; i <= N; i++) {  
        // 初始化k为1（表示A的i次方）  
        k[0] = 1;  
        int len_k = 1;  
  
        // 计算A的i次方  
        for (int u = 1; u < i; u++) {  
            memset(middle, 0, sizeof(middle));  
            int new_len_k = 0;  
            for (int e = 0; e < len_k; e++) {  
                for (int j = 0; j < len_A; j++) {  
                    middle[e + j] += k[e] * A[j];  
                }  
            }  
            int len_all = len_A + len_k;  
            for (int jinwei = 0; jinwei < len_all; jinwei++) {  
                middle[jinwei + 1] += middle[jinwei] / 10;  
                middle[jinwei] %= 10;  
            }  
            while (len_all > 0 && middle[len_all - 1] == 0) {  
                len_all--;  
            }  
            len_k = len_all;  
            memcpy(k, middle, sizeof(int) * len_k);  
        }  
  
        // 计算i * A^i  
        int len_i_shuzu = (i > 999) ? 3 : (i > 99) ? 2 : 1;  
        int i_shuzu[3] = {0};  
        i_shuzu[0] = i % 10;  
        if (len_i_shuzu > 1) {  
            i_shuzu[1] = (i / 10) % 10;  
        }  
        if (len_i_shuzu > 2) {  
            i_shuzu[2] = i / 100;  
        }  
  
        memset(middle, 0, sizeof(middle));  
        int new_len_k = 0;  
        for (int e = 0; e < len_k; e++) {  
            for (int j = 0; j < len_i_shuzu; j++) {  
                middle[e + j] += k[e] * i_shuzu[j];  
            }  
        }  
        int len_all = len_k + len_i_shuzu;  
        for (int jinwei = 0; jinwei < len_all; jinwei++) {  
            middle[jinwei + 1] += middle[jinwei] / 10;  
            middle[jinwei] %= 10;  
        }  
        while (len_all > 0 && middle[len_all - 1] == 0) {  
            len_all--;  
        }  
        len_k = len_all;  
  
        // 累加到sum中  
        for (int r = 0; r < len_k; r++) {  
            sum[r] += middle[r] + carry;  
            carry = sum[r] / 10;  
            sum[r] %= 10;  
        }  
        if (carry > 0) {  
            sum[len_k] = carry;  
            len_k++;  
        }  
    }  
  
    // 输出结果  
    int len_sum = GetLen_k(sum, len_A);  
    for (int o = len_sum - 1; o >= 0; o--) {  
        cout << sum[o];  
    }  
    cout << endl;  
  
    return 0;  
}