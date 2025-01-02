// #include <iostream>
// #include <vector>
// using namespace std;

class Solution {
private:
 
public:
    //������
    void heapSort(std::vector<int>& arr) {
        //��������
        heapInsert(arr);
        int size = arr.size();
        while (size > 1) {
            //�̶����ֵ
            swap(arr, 0, size - 1);
            size--;
            //��������
            heapify(arr, 0, size);
 
        }
 
    }
 
    //�������ѣ�ͨ���²������������
    void heapInsert(std::vector<int>& arr) {
        for (int i = 0; i < arr.size(); i++) {
            //��ǰ���������
            int currentIndex = i;
            //���������
            int fatherIndex = (currentIndex - 1) / 2;
            //�����ǰ�����ֵ�����丸����ֵ,�򽻻�ֵ�����ҽ�����ָ�򸸽��
            //Ȼ�����������ĸ����ֵ�Ƚϣ�ֱ�������ڸ���㣬���˳�ѭ��
            while (arr[currentIndex] > arr[fatherIndex]) {
                //������ǰ����븸����ֵ
                swap(arr, currentIndex, fatherIndex);
                //����ǰ����ָ������
                currentIndex = fatherIndex;
                //���¼��㵱ǰ�����ĸ�����
                fatherIndex = (currentIndex - 1) / 2;
            }
        }
    }
    //��ʣ���������ɴ���ѣ�ͨ�����˵����½���
    void heapify(std::vector<int>& arr, int index, int size) {
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        while (left < size) {
            int largestIndex;
            //�жϺ����нϴ��ֵ��������Ҫȷ���Һ�����size��Χ֮�ڣ�
            if (arr[left] < arr[right] && right < size) {
                largestIndex = right;
            }
            else {
                largestIndex = left;
            }
            //�Ƚϸ�����ֵ�뺢���нϴ��ֵ����ȷ�����ֵ������
            if (arr[index] > arr[largestIndex]) {
                largestIndex = index;
            }
            //�����������������ֵ�����������Ѿ��Ǵ�����ˣ����˳�ѭ��
            if (index == largestIndex) {
                break;
            }
            //����㲻�����ֵ���뺢���нϴ��ֵ����
            swap(arr, largestIndex, index);
            //������ָ�����нϴ��ֵ������
            index = largestIndex;
            //���¼��㽻��֮��ĺ��ӵ�����
            left = 2 * index + 1;
            right = 2 * index + 2;
        }
 
    }
    //��������������Ԫ�ص�ֵ
    void swap(std::vector<int>& arr, int i, int j) {
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
 
    std::vector<int> mySort(std::vector<int>& nums) {
        heapSort(nums);
        return nums;
    }
};

// void solve()
// {
//     Solution s;
//         std::vector<int> nums = { 5, 3, 8, 4, 2, 7, 6, 1 };
//         std::vector<int> sortedNums = s.mySort(nums);
//         for (int i = 0; i < sortedNums.size(); i++) {
//             std::cout << sortedNums[i] << " ";
//         }
//     return ;
// }

// int main() {
//     int t=1;
//     //cin>>t;
//     while(t--)
//         solve();
//     return 0;
// }