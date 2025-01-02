// #include <iostream>
// #include <vector>
// #include <string>
// using namespace std;

class Solution {
public:
    string largestNumber(vector<int>& nums) {
        // 将数字转换为字符串
        vector<string> numStrs;
        for (int num : nums) {
            numStrs.push_back(to_string(num));
        }

        // 自定义排序规则的冒泡排序
        bubbleSort(numStrs);

        // 拼接结果
        string result;
        for (const string &s : numStrs) {
            result += s;
        }

        // 特殊情况处理：如果结果是 "000...0"，则返回 "0"
        if (result[0] == '0') {
            return "0";
        }

        return result;
    }

private:
    void bubbleSort(vector<string>& numStrs) {
        int n = numStrs.size();
        for (int i = 0; i < n - 1; ++i) {
            for (int j = 0; j < n - i - 1; ++j) {
                // 比较 a + b 和 b + a
                if (numStrs[j] + numStrs[j + 1] < numStrs[j + 1] + numStrs[j]) {
                    swap(numStrs[j], numStrs[j + 1]);
                }
            }
        }
    }
};

// void slove() {
//     Solution s;
//     vector<int> nums = {3, 30, 34, 5, 9};
//     string result = s.largestNumber(nums);
//     cout << result << endl;
// }

// int main() {
//     int t = 1;
//     // cin >> t;
//     while (t--) { 
//         slove();
//     }
//     return 0;
// }
