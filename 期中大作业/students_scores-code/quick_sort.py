import time

def quicksort(arr, low, high):
    if low < high:
        # 获取划分索引
        pi = partition(arr, low, high)
        
        # 对左右两部分进行递归排序
        quicksort(arr, low, pi - 1)
        quicksort(arr, pi + 1, high)

def partition(arr, low, high):
    # 选择最后一个元素作为枢轴
    pivot = arr[high]
    i = low - 1  # i 是小于枢轴的元素的索引
    
    # 遍历并对比每个元素
    for j in range(low, high):
        # 如果当前元素大于枢轴元素
        if arr[j][1] > pivot[1] or (arr[j][1] == pivot[1] and arr[j][2] > pivot[2]) or \
           (arr[j][1] == pivot[1] and arr[j][2] == pivot[2] and arr[j][3] > pivot[3]):
            i += 1
            arr[i], arr[j] = arr[j], arr[i]
    
    # 把枢轴放到正确的位置
    arr[i + 1], arr[high] = arr[high], arr[i + 1]
    return i + 1

def read_data(filename):
    students = []
    with open(filename, "r") as file:
        lines = file.readlines()
        for line in lines[1:]:  # 跳过第一行标题
            data = line.strip().split(",")
            student_id = int(data[0])
            total_score = int(data[1])
            chinese = int(data[2])
            math = int(data[3])
            english = int(data[4])
            students.append([student_id, total_score, chinese, math, english])
    return students

def write_sorted_data(filename, students):
    with open(filename, "w") as file:
        file.write("StudentID,TotalScore,Chinese,Math,English\n")
        for student in students:
            file.write(f"{student[0]},{student[1]},{student[2]},{student[3]},{student[4]}\n")

def main():
    # 记录程序开始时间
    start_time = time.time()
    
    # 读取数据
    students = read_data(r"C:\Users\asus\Desktop\Data-Structures-Algorithms-designing\期中大作业\students_scores-data\students_scores_1000000.txt")
    
    # 快速排序
    quicksort(students, 0, len(students) - 1)
    
    # 输出排序结果
    write_sorted_data("sorted_students_scores.txt", students)
    
    # 记录程序结束时间
    end_time = time.time()
    
    # 计算并输出运行时间
    print(f"数据已排序并保存到 sorted_students_scores.txt")
    print(f"算法运行时间: {end_time - start_time:.4f} 秒")

if __name__ == "__main__":
    main()

