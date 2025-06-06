import heapq

# 自定义最小堆
class MinHeap:
    def __init__(self, k):
        self.k = k  # 堆的最大容量
        self.heap = []

    def insert(self, student):
        # 转换为元组，负值用于保留最大的 k 个元素
        heap_item = (student[1], student[2], student[3], student[4], student[0])
        heapq.heappush(self.heap, heap_item)
        
        # 如果堆大小超过 k，弹出最小元素
        if len(self.heap) > self.k:
            heapq.heappop(self.heap)

    def get_heap(self):
        # 将堆中的元素转换回原始格式并按升序排序
        result = []
        for item in self.heap:
            # 还原为 [student_id, total_score, chinese, math, english]
            student = [item[4], item[0], item[1], item[2], item[3]]
            result.append(student)
        # 按总分、语文、数学、英语升序排序
        result.sort(key=lambda x: (x[1], x[2], x[3], x[4]))
        return result

# 读取数据
def read_data(filename):
    students = []
    try:
        with open(filename, "r") as file:
            lines = file.readlines()
            for line in lines[1:]:  # 跳过第一行标题
                try:
                    data = line.strip().split(",")
                    student_id = int(data[0])
                    total_score = int(data[1])
                    chinese = int(data[2])
                    math = int(data[3])
                    english = int(data[4])
                    students.append([student_id, total_score, chinese, math, english])
                except (IndexError, ValueError):
                    print(f"Invalid data in line: {line}")
            return students
    except FileNotFoundError:
        print(f"File {filename} not found")
        return []

def main():
    # 读取数据
    filename = r"C:\Users\asus\Desktop\Data-Structures-Algorithms-designing\期中大作业\students_scores-data\students_scores_1000.txt"
    students = read_data(filename)
    
    # 使用最小堆找出前 10 名学生
    min_heap = MinHeap(k=10)
    for student in students:
        min_heap.insert(student)
    
    # 获取并输出前 10 名学生
    top_10_students = min_heap.get_heap()
    
    print("前 10 名学生（按总分、语文、数学、英语升序排序）:")
    for student in top_10_students:
        print(f"学号: {student[0]}, 总分: {student[1]}, 语文: {student[2]}, 数学: {student[3]}, 英语: {student[4]}")

    # 写入结果到 txt 文件
    output_filename = r"C:\Users\asus\Desktop\Data-Structures-Algorithms-designing\期中大作业\top_10_students.txt"
    try:
        with open(output_filename, "w", encoding="utf-8") as file:
            file.write("前 10 名学生（按总分、语文、数学、英语升序排序）:\n")
            file.write("ID,Total,Chinese,Math,English\n")
            for student in top_10_students:
                file.write(f"{student[0]},{student[1]},{student[2]},{student[3]},{student[4]}\n")
        print(f"结果已成功写入到 {output_filename}")
    except IOError:
        print(f"写入文件 {output_filename} 失败")
    

if __name__ == "__main__":
    main()