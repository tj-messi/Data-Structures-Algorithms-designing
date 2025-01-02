// #include <iostream>
// #include <vector>
// #include <string>
// using namespace std;

class Solution {
public:
    string largestNumber(vector<int>& nums) {
        // ������ת��Ϊ�ַ���
        vector<string> numStrs;
        for (int num : nums) {
            numStrs.push_back(to_string(num));
        }

        // �Զ�����������ð������
        bubbleSort(numStrs);

        // ƴ�ӽ��
        string result;
        for (const string &s : numStrs) {
            result += s;
        }

        // ������������������� "000...0"���򷵻� "0"
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
                // �Ƚ� a + b �� b + a
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
