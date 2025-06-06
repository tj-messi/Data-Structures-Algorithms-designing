import random

def generate_data(num_records, filename="students_scores_1000.txt"):
    # 设置正态分布的均值和标准差
    mean = 75   # 平均值
    std_dev = 20  # 标准差

    with open(filename, "w") as file:
        # 写入标题
        file.write("StudentID,TotalScore,Chinese,Math,English\n")
        
        for _ in range(num_records):
            # 随机生成七位学号
            student_id = random.randint(1000000, 9999999)
            
            # 使用正态分布生成语文、数学、英语成绩
            chinese = int(random.gauss(mean, std_dev))
            math = int(random.gauss(mean, std_dev))
            english = int(random.gauss(mean, std_dev))
            
            # 确保分数在 0 到 150 之间
            chinese = max(0, min(chinese, 150))
            math = max(0, min(math, 150))
            english = max(0, min(english, 150))
            
            # 计算总分
            total_score = chinese + math + english
            
            # 写入到文件，每个数据项之间用英文逗号隔开
            file.write(f"{student_id},{total_score},{chinese},{math},{english}\n")

    print(f"数据已成功生成并保存到 {filename}")

# 控制生成数据的条数
num_records = 1000  # 例如生成 10 条数据
generate_data(num_records)

