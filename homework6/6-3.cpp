#include <iostream>
#include <vector>
#define MAX_SIZE 3000
using namespace std;

static vector<int> results;

void QuickSort(int arr[MAX_SIZE], int low, int high);
int Partition(int arr[MAX_SIZE], int low, int high);
void SaveTriple(int x, int y, int z);
void FindTriplets(int arr[MAX_SIZE], int left, int right);

void QuickSort(int arr[MAX_SIZE], int low, int high) {
    if (low < high) {
        int pivotIndex = Partition(arr, low, high);
        QuickSort(arr, low, pivotIndex - 1);
        QuickSort(arr, pivotIndex + 1, high);
    }
}

int Partition(int arr[MAX_SIZE], int low, int high) {
    int pivotValue = arr[high];
    int i = low - 1;
    
    for (int j = low; j < high; j++) {
        if (arr[j] <= pivotValue) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void SaveTriple(int x, int y, int z) {
    results.push_back(x);
    results.push_back(y);
    results.push_back(z);
}

void FindTriplets(int arr[MAX_SIZE], int left, int right) {
    int pivot = left;
    int i = pivot;
    int j = right;
    
    while (pivot < right) {
        if (pivot > 0) {
            while (pivot > left && arr[pivot] == arr[pivot - 1]) {
                pivot++;
            }
        }

        j = right;
        i = pivot + 1;

        while (i < j) {
            int sum = arr[pivot] + arr[i] + arr[j];
            if (sum == 0) {
                SaveTriple(arr[pivot], arr[i], arr[j]);
                j--;
                while (j < right && arr[j] == arr[j + 1]) {
                    j--;
                }
            } else if (sum > 0) {
                j--;
            } else {
                i++;
            }
        }
        pivot++;
    }
}

void solve()
{
    int n, arr[MAX_SIZE];
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    
    QuickSort(arr, 0, n - 1);
    FindTriplets(arr, 0, n - 1);

    for (size_t i = 0; i < results.size(); i++) {
        cout << results[i] << " ";
        if ((i + 1) % 3 == 0) {
            cout << endl;
        }
    }
    cout << endl;
    return;
}

int main()
{
    int t=1;
    //cin >> t;
    while(t--)
    {
        solve();
    }
    return 0;
}
