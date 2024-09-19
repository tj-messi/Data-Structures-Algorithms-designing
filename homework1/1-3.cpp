#include <iostream>  
#include <vector>  
#include <string>  
#include <algorithm>  
  
using namespace std;  
  
// 计算大数的有效长度  
int GetLen(const vector<int>& nums) {  
    int len = nums.size();  
    while (len > 0 && nums[len - 1] == 0) len--;  
    return len;  
}  
  
// 大数乘法  
vector<int> multiply(const vector<int>& nums1, int num2) {  
    vector<int> result(nums1.size() + 1, 0);  
    int carry = 0;  
    for (int i = 0; i < nums1.size(); i++) {  
        int product = nums1[i] * num2 + carry;  
        result[i] = product % 10;  
        carry = product / 10;  
    }  
    if (carry > 0) result.back() = carry;  
    return result;  
}  
  
// 大数加法  
vector<int> add(const vector<int>& nums1, const vector<int>& nums2) {  
    int len1 = GetLen(nums1), len2 = GetLen(nums2);  
    vector<int> result(max(len1, len2) + 1, 0);  
    int carry = 0;  
    for (int i = 0; i < result.size(); i++) {  
        int sum = carry;  
        if (i < len1) sum += nums1[len1 - i - 1];  
        if (i < len2) sum += nums2[len2 - i - 1];  
        result[result.size() - i - 1] = sum % 10;  
        carry = sum / 10;  
    }  
    if (carry > 0) result.insert(result.begin(), carry);  
    return result;  
}  
  
int main() {  
    int N;  
    string s_A;  
    cin >> N >> s_A;  
  
    vector<int> A(s_A.size());  
    for (int i = 0; i < s_A.size(); i++) {  
        A[i] = s_A[s_A.size() - i - 1] - '0';  
    }  
  
    vector<int> sum(10002, 0);  
    vector<int> k = {1};  // k 初始化为 1  
  
    for (int i = 1; i <= N; i++) {  
        // 计算 A^i  
        vector<int> A_i = A;  
        for (int j = 1; j < i; j++) {  
            A_i = multiply(A_i, 10);  
            for (int m = 0; m < A.size(); m++) {  
                A_i[m] += A[m];  
                if (A_i[m] >= 10) {  
                    A_i[m + 1]++;  
                    A_i[m] %= 10;  
                }  
            }  
            while (A_i.size() > 1 && A_i.back() == 0) A_i.pop_back();  
        }  
  
        // 计算 i * A^i  
        vector<int> i_A_i = multiply(A_i, i);  
  
        // 累加到 sum  
        sum = add(sum, i_A_i);  
    }  
  
    int len_sum = GetLen(sum);  
    for (int i = len_sum - 1; i >= 0; i--) {  
        cout << sum[i];  
    }  
    cout << endl;  
  
    return 0;  
}