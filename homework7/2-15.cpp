#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

int main() {
    int totalPlayers = 0;
    cout << "请输入参赛选手的总人数: ";
    cin >> totalPlayers;

    if (totalPlayers <= 0) {
        cout << "请输入一个有效的正整数！" << endl;
        return 1;
    }
    int days = (totalPlayers % 2 == 0) ? totalPlayers - 1 : totalPlayers;
    vector<vector<int>> schedule(days, vector<int>(totalPlayers, 0));
    int adjustedPlayers = (totalPlayers % 2 == 0) ? totalPlayers : totalPlayers + 1;
    for (int round = 0; round < adjustedPlayers - 1; ++round) {
        for (int i = 0; i < adjustedPlayers / 2; ++i) {
            int player1 = (round + i) % (adjustedPlayers - 1);
            int player2 = (adjustedPlayers - 1 - i + round) % (adjustedPlayers - 1);

            if (i == 0) player2 = adjustedPlayers - 1;

            if (player1 < totalPlayers && player2 < totalPlayers) {
                schedule[round][player1] = player2 + 1;  
                schedule[round][player2] = player1 + 1;
            }
        }
    }

    int maxNumWidth = 0;
    int num = totalPlayers;
    while (num != 0) {
        num /= 10;
        maxNumWidth++;
    }
    int columnWidth = (maxNumWidth > 4) ? maxNumWidth + 1 : 5;

    cout << "\n比赛安排：\n";
    cout << left << setw(10) << "天数\\选手";
    for (int i = 1; i <= totalPlayers; ++i) {
        cout << right << setw(columnWidth) << i;
    }
    cout << endl;
    cout << setfill('-') << setw(10 + totalPlayers * columnWidth) << "" << setfill(' ') << endl;

    for (int day = 0; day < schedule.size(); ++day) {
        cout << left << "第 " << setw(2) << day + 1 << " 天 " << right;
        for (int player = 0; player < totalPlayers; ++player) {
            if (schedule[day][player] == 0) {
                cout << setw(columnWidth) << "\\";
            } else {
                cout << setw(columnWidth) << schedule[day][player];
            }
        }
        cout << endl;
    }

    return 0;
}
