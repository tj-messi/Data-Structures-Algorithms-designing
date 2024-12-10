#include<iostream>
#include<vector>
using namespace std;

#define NUMS_LEN 1000
#define QUERIES_LEN 1000

// 快速排序的划分函数
int Partition(int nums[], int low, int high) {
    int pivot = nums[high];  // 选择最后一个元素作为基准
    int i = low - 1;  // i 是小于基准的元素的最右边的索引

    for (int j = low; j < high; j++) {
        if (nums[j] <= pivot) {  // 如果当前元素小于等于基准
            i++;
            swap(nums[i], nums[j]);  // 交换小于等于基准的元素到左侧
        }
    }
    swap(nums[i + 1], nums[high]);  // 将基准元素放到正确位置
    return i + 1;  // 返回基准元素的索引
}

// 快速排序函数
void QuickSort(int nums[], int low, int high) {
    if (low < high) {
        int pivotIndex = Partition(nums, low, high);  // 获取基准元素的索引
        QuickSort(nums, low, pivotIndex - 1);  // 对左侧子数组排序
        QuickSort(nums, pivotIndex + 1, high);  // 对右侧子数组排序
    }
}

// 二分查找：返回不超过目标值 dst 的最大位置
int BinarySearch(int dst, int nums[], int low, int high) {
    int result = -1;  // 用于记录符合条件的最大位置
    while (low <= high) {
        int mid = low + (high - low) / 2;
        
        if (nums[mid] <= dst) {  // 目标值大于等于 mid 位置的值，符合条件
            result = mid;  // 更新result
            low = mid + 1;  // 继续查找右半部分
        } else {
            high = mid - 1;    // 查找左半部分
        }
    }
    return result + 1;  // 返回的是位置，所以需要加1
}

void solve() {
    int n, m;
    cin >> n >> m;
    
    vector<int> nums(n), queries(m);
    
    // 输入数组 nums
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }
    
    // 输入查询数组 queries
    for (int i = 0; i < m; i++) {
        cin >> queries[i];
    }
    
    // 对 nums 进行快速排序
    QuickSort(nums.data(), 0, n - 1);
    
    // 计算nums的前缀和
    vector<int> prefix_sum(n);
    prefix_sum[0] = nums[0];
    for (int i = 1; i < n; i++) {
        prefix_sum[i] = prefix_sum[i - 1] + nums[i];
    }

    // 对每个查询进行处理
    for (int q = 0; q < m; q++) {
        int query = queries[q];
        
        // 二分查找：找最大的prefix_sum[i] <= query
        int result = BinarySearch(query, prefix_sum.data(), 0, n - 1);
        
        // 输出结果
        cout << result << " ";
    }
    
    cout << endl;
    
    return;
}

int main()
{
    int t=1;
    //cin>>t;
    while(t--)
    {
        solve();
    }
    return 0;
}