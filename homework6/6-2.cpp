#include<iostream>
#define MAX_LEN 20000
using namespace std;
void Merge(int Seq[MAX_LEN], int left, int right, int &num,int temp[MAX_LEN]) {
    int mid = (left + right) / 2;
    int i = left;
    int j = mid  + 1;
    int tmp = 0;
    while (i <= mid &&j <=right) {
        if (Seq[i] <= Seq[j]) {
            temp[tmp++] = Seq[i++];
        }
        else {
            temp[tmp++] = Seq[j++];
            
            num+=mid+1-i;
        }
    }
    
    while (i <= mid) {
        temp[tmp++] = Seq[i++];
    }
    
    while (j <= right) {
        temp[tmp++] = Seq[j++];
    }
    
    for(int i=0;i<tmp;i++){
        Seq[left+i] = temp[i];
    }
 
}
void MergeSort(int Seq[MAX_LEN],int left,int right,int &num,int temp[MAX_LEN]) {
    if (left < right) {
        int mid = (left + right) / 2;
        
        MergeSort(Seq, left, mid, num, temp);
        MergeSort(Seq, mid + 1, right, num, temp);
        Merge(Seq, left, right, num, temp);
    }
    return;
}

void slove()
 {
    int n;
    int Seq[MAX_LEN];   //存储原序列
    int temp[MAX_LEN];  //存储分割后的子序列
    int num = 0;
    while (1) {
        cin >> n;
        if (n == 0)
            break;
        else {
            for (int i = 0; i < n; i++) {
                cin >> Seq[i];
            }
            num = 0;
            MergeSort(Seq, 0, n - 1, num, temp);
            cout << num << endl;
        }
    }
}

int main() {
    int t=1;
    //cin>>t;
    while(t--){ 
        slove();
    }
    return 0;
}