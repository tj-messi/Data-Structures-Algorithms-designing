class Solution {
public:
    vector<string>Old;
    vector<string>New;
    map<string, int>oldmap;
    map<string, int>newmap;
    int Checked[50000];
    void Creatchart(int n, int m, std::vector<vector<std::string>> old_chart, std::vector<std::vector<std::string>> new_chart) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                Old.push_back(old_chart[i][j]);
            }
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                New.push_back(new_chart[i][j]);
            }
        }
    }
    void Creatmap(int n, int m) {
        //创建old的hashmap
        for (int i = 0; i < Old.size(); i++) {
            oldmap.insert(pair<string, int>(Old[i], i));
        }
        //创建new的hashmap
        for (int i = 0; i < New.size(); i++) {
            newmap.insert(pair<string, int>(New[i], i));
        }
    }
    int FindStrKey(int state, string str) {
        map<string, int>::iterator iter;
        if (state == 1) {
            return oldmap.find(str)->second;
        }
        if (state == 2) {
            return newmap.find(str)->second;
        }
    }
    void swap(int i, int j, string oldstr, string newstr) {
        string tmp;
        int temp;
        //更新数组
        tmp = Old[i];
        Old[i] = Old[j];
        Old[j] = tmp;
        //更新oldmap
        temp = oldmap[oldstr];
        oldmap[oldstr] = oldmap[newstr];
        oldmap[newstr] = temp;
    }
 
    int Calculate_Circle() {
        int cnt = 0;
        int j;   //标记指针
        string j_tmp;
        //遍历记录数组Checked归0
        for (int i = 0; i < 50000; i++) {
            Checked[i] = 0;
        }
        for (int i = 0; i < Old.size(); i++) {
            j = i;
            while (Checked[i] != 1) {
                j_tmp = Old[j];
                if (Old[j] == New[j]) {
                    Checked[j] = 1;
                    cnt++;
                    break;
                }
                else {
                    swap(j, FindStrKey(1, New[j]), Old[j], New[j]);
                    j = FindStrKey(1, j_tmp);
                    Checked[j] = 1;
                }
            }
        }
        return cnt;
    }
    int solve(std::vector<vector<std::string>>& old_chart, std::vector<std::vector<std::string>>& new_chart) {
        static int n = old_chart.size();
        static int m = old_chart[0].size();
        Creatchart(n, m, old_chart, new_chart);
        Creatmap(n, m);
        return n * m - Calculate_Circle();
    }
 
};