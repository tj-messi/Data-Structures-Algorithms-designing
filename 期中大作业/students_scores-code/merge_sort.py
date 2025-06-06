import random
import time

# 归并排序算法
def merge_sort(arr):
    if len(arr) > 1:
        mid = len(arr) // 2
        left_half = arr[:mid]
        right_half = arr[mid:]
        merge_sort(left_half)
        merge_sort(right_half)
        i = j = k = 0
        while i < len(left_half) and j < len(right_half):
            if left_half[i][1] > right_half[j][1] or (left_half[i][1] == right_half[j][1] and left_half[i][2] > right_half[j][2]) or \
               (left_half[i][1] == right_half[j][1] and left_half[i][2] == right_half[j][2] and left_half[i][3] > right_half[j][3]):
                arr[k] = left_half[i]
                i += 1
            else:
                arr[k] = right_half[j]
                j += 1
            k += 1
        while i < len(left_half):
            arr[k] = left_half[i]
            i += 1
            k += 1
        while j < len(right_half):
            arr[k] = right_half[j]
            j += 1
            k += 1

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
    merge_sort(students)  # 使用归并排序
    
    # 输出排序结果
    write_sorted_data("sorted_students_scores.txt", students)
    
    # 记录程序结束时间
    end_time = time.time()
    
    # 计算并输出运行时间
    print(f"数据已排序并保存到 sorted_students_scores.txt")
    print(f"算法运行时间: {end_time - start_time:.4f} 秒")

if __name__ == "__main__":
    main()
