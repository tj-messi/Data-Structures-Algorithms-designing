import random
import time
# 堆排序算法
def heapify(arr, n, i):
    largest = i
    left = 2 * i + 1
    right = 2 * i + 2
    if left < n and (arr[left][1] > arr[largest][1] or (arr[left][1] == arr[largest][1] and arr[left][2] > arr[largest][2]) or \
                      (arr[left][1] == arr[largest][1] and arr[left][2] == arr[largest][2] and arr[left][3] > arr[largest][3])):
        largest = left
    if right < n and (arr[right][1] > arr[largest][1] or (arr[right][1] == arr[largest][1] and arr[right][2] > arr[largest][2]) or \
                       (arr[right][1] == arr[largest][1] and arr[right][2] == arr[largest][2] and arr[right][3] > arr[largest][3])):
        largest = right
    if largest != i:
        arr[i], arr[largest] = arr[largest], arr[i]
        heapify(arr, n, largest)
def heap_sort(arr):
    n = len(arr)
    for i in range(n // 2 - 1, -1, -1):
        heapify(arr, n, i)
    for i in range(n-1, 0, -1):
        arr[i], arr[0] = arr[0], arr[i]
        heapify(arr, i, 0)

# 读取数据
def read_data(filename):
    students = []
    with open(filename, "r") as file:
        lines = file.readlines()
        for line in lines[1:]:
            data = line.strip().split(",")
            student_id = int(data[0])
            total_score = int(data[1])
            chinese = int(data[2])
            math = int(data[3])
            english = int(data[4])
            students.append([student_id, total_score, chinese, math, english])
    return students

# 写入排序后的数据
def write_sorted_data(filename, students):
    with open(filename, "w") as file:
        file.write("StudentID,TotalScore,Chinese,Math,English\n")
        for student in students:
            file.write(f"{student[0]},{student[1]},{student[2]},{student[3]},{student[4]}\n")

def main():
    # 记录程序开始时间
    start_time = time.time()
    
    # 读取数据
    students = read_data(r"C:\Users\asus\Desktop\Data-Structures-Algorithms-designing\期中大作业\students_scores-data\students_scores_10000.txt")
    
    # 选择排序算法
    heap_sort(students)  # 使用堆排序
    
    # 输出排序结果
    write_sorted_data("sorted_students_scores.txt", students)
    
    # 记录程序结束时间
    end_time = time.time()
    
    # 计算并输出运行时间
    print(f"数据已排序并保存到 sorted_students_scores.txt")
    print(f"算法运行时间: {end_time - start_time:.4f} 秒")

if __name__ == "__main__":
    main()
