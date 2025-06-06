#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <functional>

using namespace std;

int main() {
    vector<string> steps;

    auto same_color = [](int x, int y) -> bool {
        return (x % 2) == (y % 2);
    };

    auto int_to_str = [](int n) -> string {
        ostringstream oss;
        oss << n;
        return oss.str();
    };

    std::function<void(int, char, char, char, int)> hanoi;
    hanoi = [&](int n, char A, char B, char C, int last) -> void {
        if (n == 0) return;

        hanoi(n - 1, A, C, B, n);

        if (last == -1 || !same_color(n, last)) {
            string move = int_to_str(n) + A + B;
            steps.push_back(move);
            hanoi(n - 1, C, B, A, n);
        }
        else {
            hanoi(n - 1, A, B, C, last);
            string move = int_to_str(n) + A + B;
            steps.push_back(move);
        }
    };

    int n;
    cout << "请输入盘子数: ";
    cin >> n;

    hanoi(n, 'A', 'B', 'C', -1);

    cout << "步骤：" << endl;
    for (const auto& step : steps) {
        cout << step << endl;
    }

    return 0;
}

