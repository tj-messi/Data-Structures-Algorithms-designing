import heapq
import random
import time
import sys

# 基于堆的选择算法类
class HeapSelection:
    def __init__(self, k):
        self.k = k
    
    def find_kth_smallest(self, data):
        # 使用最大堆，堆的大小为 k
        max_heap = []
        for i in range(len(data)):
            if len(max_heap) < self.k:
                heapq.heappush(max_heap, -data[i])  # 插入负值来模拟最大堆
            else:
                if data[i] < -max_heap[0]:
                    heapq.heappop(max_heap)
                    heapq.heappush(max_heap, -data[i])
        
        return -max_heap[0]  # 返回堆顶元素

    def measure_time(self, data):
        start_time = time.time()
        result = self.find_kth_smallest(data)
        end_time = time.time()
        return result, (end_time - start_time)


# 随机划分线性选择算法类
class RandomizedSelect:
    def __init__(self, k):
        self.k = k
    
    def partition(self, data, low, high):
        pivot = data[high]
        i = low - 1
        for j in range(low, high):
            if data[j] <= pivot:
                i += 1
                data[i], data[j] = data[j], data[i]
        data[i + 1], data[high] = data[high], data[i + 1]
        return i + 1

    def randomized_select(self, data, low, high, k):
        if low == high:
            return data[low]
        pivot_index = random.randint(low, high)
        data[pivot_index], data[high] = data[high], data[pivot_index]
        pivot = self.partition(data, low, high)
        rank = pivot - low + 1
        
        if k == rank:
            return data[pivot]
        elif k < rank:
            return self.randomized_select(data, low, pivot - 1, k)
        else:
            return self.randomized_select(data, pivot + 1, high, k - rank)

    def measure_time(self, data):
        start_time = time.time()
        result = self.randomized_select(data, 0, len(data) - 1, self.k)
        end_time = time.time()
        return result, (end_time - start_time)


# 中位数的线性时间选择算法类
class MedianOfMedians:
    def __init__(self, k):
        self.k = k

    def partition(self, data, low, high):
        pivot = data[high]
        i = low - 1
        for j in range(low, high):
            if data[j] <= pivot:
                i += 1
                data[i], data[j] = data[j], data[i]
        data[i + 1], data[high] = data[high], data[i + 1]
        return i + 1

    def median_of_medians(self, data, low, high):
        if high - low + 1 <= 5:
            return sorted(data[low:high + 1])[(high - low) // 2]
        medians = []
        for i in range(low, high + 1, 5):
            sublist = data[i:i + 5]
            medians.append(sorted(sublist)[len(sublist) // 2])
        return self.randomized_select(medians, 0, len(medians) - 1, len(medians) // 2)

    def randomized_select(self, data, low, high, k):
        if low == high:
            return data[low]
        pivot = self.median_of_medians(data, low, high)
        pivot_index = data.index(pivot)
        data[pivot_index], data[high] = data[high], data[pivot_index]
        pivot_index = self.partition(data, low, high)
        
        rank = pivot_index - low + 1
        if k == rank:
            return data[pivot_index]
        elif k < rank:
            return self.randomized_select(data, low, pivot_index - 1, k)
        else:
            return self.randomized_select(data, pivot_index + 1, high, k - rank)

    def measure_time(self, data):
        start_time = time.time()
        result = self.randomized_select(data, 0, len(data) - 1, self.k)
        end_time = time.time()
        return result, (end_time - start_time)


# 生成随机数据并保存到文件
def generate_data(n, k, filename="find_k-th_data.txt"):
    # 生成一个不重复的元素集合
    data = random.sample(range(1, 10 * n), n)  # 生成 n 个不重复的元素，范围从 1 到 10n
    
    # 写入文件
    with open(filename, "w") as file:
        # 输出 k 值
        file.write(f"{k}\n")
        
        # 输出 n 个元素，元素之间用空格分隔
        file.write(" ".join(map(str, data)) + "\n")
    
    print(f"数据已生成并保存到 {filename}")
    print(f"Random k: {k}")
    print("Data:", data)

# 读取数据
def read_data(filename):
    with open(filename, "r") as file:
        lines = file.readlines()
        k = int(lines[0].strip())
        data = list(map(int, lines[1].strip().split()))
    return k, data

# 写入结果到文件
def write_results_to_file(results):
    with open("results-9000.txt", "a") as file:  # 使用 'a' 模式追加数据
        for method, result, time_taken, n, k in results:
            file.write(f"n = {n}, k = {k}\n")
            file.write(f"{method}: {result}, Time Taken: {time_taken:.6f} seconds\n")
            file.write("\n")

# 测试不同算法并记录时间
def main():
    n = 9000  # 数据规模 n
    for k in range(1, n+1):  # 枚举 k 从 1 到 n
        # 生成随机数据并保存到文件
        generate_data(n, k, "find_k-th_data.txt")
        
        k, data = read_data("find_k-th_data.txt")
        
        results = []

        # 测试基于堆的选择
        heap_selection = HeapSelection(k)
        result, time_taken = heap_selection.measure_time(data.copy())
        results.append(("Heap Selection", result, time_taken, n, k))
        
        # 测试随机划分线性选择
        randomized_select = RandomizedSelect(k)
        result, time_taken = randomized_select.measure_time(data.copy())
        results.append(("Randomized Select", result, time_taken, n, k))
        
        # 测试中位数的线性选择
        median_of_medians = MedianOfMedians(k)
        result, time_taken = median_of_medians.measure_time(data.copy())
        results.append(("Median of Medians", result, time_taken, n, k))

        # 将结果写入文件
        write_results_to_file(results)
        print(f"Results for n = {n}, k = {k} have been saved to results.txt")

if __name__ == "__main__":
    main()
