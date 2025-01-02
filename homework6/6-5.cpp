#include <iostream>
#include <queue>
#define MAX_SIZE 2010
using namespace std;

// 插入排序实现
void insertionSort(int* array, int length) {
    for (int i = 1; i < length; ++i) {
        int keyValue = array[i];
        int position = i - 1;

        // 将大于 keyValue 的元素向右移动
        while (position >= 0 && array[position] > keyValue) {
            array[position + 1] = array[position];
            position--;
        }
        array[position + 1] = keyValue;
    }
}

void maintainSum(int* currentSums, int* newArray, int length) {
    priority_queue<int> minHeap;

    for (int i = 0; i < length; ++i) {
        for (int j = 0; j < length; ++j) {
            int sumValue = currentSums[i] + newArray[j];

            if (minHeap.size() < length)
                minHeap.push(sumValue);
            else if (sumValue < minHeap.top()) {
                minHeap.pop();
                minHeap.push(sumValue);
            } else {
                break;
            }
        }
    }

    for (int k = length - 1; k >= 0; k--) {
        currentSums[k] = minHeap.top();
        minHeap.pop();
    }
}

void solveTestCase() {
    int numSequences, numElements;
    int currentSums[MAX_SIZE];
    int newArray[MAX_SIZE];

    cin >> numSequences >> numElements;

    for (int i = 0; i < numElements; i++)
        cin >> currentSums[i];

    // 使用插入排序
    insertionSort(currentSums, numElements);

    for (int i = 1; i < numSequences; i++) {
        for (int j = 0; j < numElements; j++)
            cin >> newArray[j];

        // 使用插入排序
        insertionSort(newArray, numElements);
        maintainSum(currentSums, newArray, numElements);
    }

    for (int i = 0; i < numElements; ++i)
        cout << currentSums[i] << " ";

    cout << endl;
}

int main() {
    int testCases;
    cin >> testCases;
    while (testCases--) {
        solveTestCase();
    }
    return 0;
}
