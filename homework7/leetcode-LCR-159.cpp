class Solution {
    public:
        vector<int> inventoryManagement(vector<int>& stock, int cnt) {
            if (cnt >= stock.size())
                return stock;
            else
                return quicksort(stock,cnt,0,stock.size()-1);
        }
    private:
        vector<int> quicksort(vector<int>& nowstock,int cnt,int l,int r)
        {
            int i=l;
            int j=r;
            while(i<j)
            {
                while(i<j&&nowstock[j]>=nowstock[l])j--;
                while(i<j&&nowstock[i]<=nowstock[l])i++;
                swap(nowstock[i],nowstock[j]);
            }
            swap(nowstock[i],nowstock[l]);
            if (i > cnt) return quicksort(nowstock, cnt, l, i - 1);
            if (i < cnt) return quicksort(nowstock, cnt, i + 1, r);
            vector<int> res;
            res.assign(nowstock.begin(), nowstock.begin() + cnt);
            return res;
        }
    
    };