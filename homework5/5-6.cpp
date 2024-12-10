class FreqStack {
private:
    map<int, int>strmap;
    vector<stack<int>>frestack;
    int maxfre;
public:
    FreqStack() {
        maxfre = 0;
    }
    void push(int val) {
        stack<int> S;
        //将键值对记录，检测是否需要新建一个键值对
        if (strmap.find(val) == strmap.end()) {
            strmap.insert(pair<int, int>(val, 1));
        }
        else {
            strmap[val]++;
        }
        //将获得的结果放入新栈中，检测是否需要新建一个频率栈
        if (strmap[val] > maxfre) {
            maxfre = strmap[val];
            frestack.push_back(S);
            frestack[maxfre - 1].push(val);
        }
        else {
            frestack[strmap[val] - 1].push(val);
        }
    }
 
    int pop() {
        int ret = frestack[maxfre - 1].top();
        frestack[maxfre - 1].pop();
        strmap[ret]--;
        if (frestack[maxfre - 1].empty()) {
            maxfre--;
 
            frestack.pop_back();
        }
        return ret;
    }
};