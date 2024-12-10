#include<iostream>
#include<vector>
using namespace std;

#define NUMS_LEN 1000
#define QUERIES_LEN 1000

// ��������Ļ��ֺ���
int Partition(int nums[], int low, int high) {
    int pivot = nums[high];  // ѡ�����һ��Ԫ����Ϊ��׼
    int i = low - 1;  // i ��С�ڻ�׼��Ԫ�ص����ұߵ�����

    for (int j = low; j < high; j++) {
        if (nums[j] <= pivot) {  // �����ǰԪ��С�ڵ��ڻ�׼
            i++;
            swap(nums[i], nums[j]);  // ����С�ڵ��ڻ�׼��Ԫ�ص����
        }
    }
    swap(nums[i + 1], nums[high]);  // ����׼Ԫ�طŵ���ȷλ��
    return i + 1;  // ���ػ�׼Ԫ�ص�����
}

// ����������
void QuickSort(int nums[], int low, int high) {
    if (low < high) {
        int pivotIndex = Partition(nums, low, high);  // ��ȡ��׼Ԫ�ص�����
        QuickSort(nums, low, pivotIndex - 1);  // ���������������
        QuickSort(nums, pivotIndex + 1, high);  // ���Ҳ�����������
    }
}

// ���ֲ��ң����ز�����Ŀ��ֵ dst �����λ��
int BinarySearch(int dst, int nums[], int low, int high) {
    int result = -1;  // ���ڼ�¼�������������λ��
    while (low <= high) {
        int mid = low + (high - low) / 2;
        
        if (nums[mid] <= dst) {  // Ŀ��ֵ���ڵ��� mid λ�õ�ֵ����������
            result = mid;  // ����result
            low = mid + 1;  // ���������Ұ벿��
        } else {
            high = mid - 1;    // ������벿��
        }
    }
    return result + 1;  // ���ص���λ�ã�������Ҫ��1
}

void solve() {
    int n, m;
    cin >> n >> m;
    
    vector<int> nums(n), queries(m);
    
    // �������� nums
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }
    
    // �����ѯ���� queries
    for (int i = 0; i < m; i++) {
        cin >> queries[i];
    }
    
    // �� nums ���п�������
    QuickSort(nums.data(), 0, n - 1);
    
    // ����nums��ǰ׺��
    vector<int> prefix_sum(n);
    prefix_sum[0] = nums[0];
    for (int i = 1; i < n; i++) {
        prefix_sum[i] = prefix_sum[i - 1] + nums[i];
    }

    // ��ÿ����ѯ���д���
    for (int q = 0; q < m; q++) {
        int query = queries[q];
        
        // ���ֲ��ң�������prefix_sum[i] <= query
        int result = BinarySearch(query, prefix_sum.data(), 0, n - 1);
        
        // ������
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