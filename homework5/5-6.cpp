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
        //����ֵ�Լ�¼������Ƿ���Ҫ�½�һ����ֵ��
        if (strmap.find(val) == strmap.end()) {
            strmap.insert(pair<int, int>(val, 1));
        }
        else {
            strmap[val]++;
        }
        //����õĽ��������ջ�У�����Ƿ���Ҫ�½�һ��Ƶ��ջ
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