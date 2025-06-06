#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n;
    cout << "请输入元素个数: ";
    cin >> n;

    auto factorial = [](int n) -> int {
        int res = 1;
        for (int i = 2; i <= n; i++)
            res *= i;
        return res;
    };

    auto cantorRank = [&](int n, const vector<int>& perm) -> int {
        int rank = 0;
        vector<bool> used(n + 1, false);

        for (int i = 0; i < n; i++) {
            int count = 0;
            for (int j = 1; j < perm[i]; j++) {
                if (!used[j])
                    count++;
            }
            rank += count * factorial(n - i - 1);
            used[perm[i]] = true; 
        }
        return rank;
    };
    auto cantorUnrank = [&](int n, int rank) -> vector<int> {
        vector<int> perm(n);             
        vector<bool> used(n + 1, false);

        for (int i = 0; i < n; i++) {
            int f = factorial(n - i - 1); 
            int count = rank / f;         
            rank %= f;                    
            for (int j = 1; j <= n; j++) {
                if (!used[j]) {
                    if (count == 0) {
                        perm[i] = j;
                        used[j] = true;
                        break;
                    }
                    count--;
                }
            }
        }
        return perm;
    };

    vector<int> perm(n);
    cout << "排列: ";
    for (int i = 0; i < n; i++)
        cin >> perm[i];  

    int rank = cantorRank(n, perm);
    cout << "字典序序号: " << rank << endl; 

    vector<int> result = cantorUnrank(n, rank);
    cout << "反推出的排列: ";
    for (int i = 0; i < n; i++)
        cout << result[i] << " "; 
    cout << endl;

    return 0;
}
