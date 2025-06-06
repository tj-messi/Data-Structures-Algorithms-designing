import random

def generate_data(num_lines, filename="cards_data.txt"):
    with open(filename, "w") as file:
        for _ in range(num_lines):
            # 随机设定卡片数量 n，范围是 10 到 10000
            n = random.randint(10, 10000)
            
            # 生成一个长度为 n 的数组，数组的元素值小于等于 n
            array = [random.randint(1, n) for _ in range(n)]
            
            # 写入文件：先写入 n，然后是由逗号分隔的数组元素
            file.write(f"{n}," + ",".join(map(str, array)) + "\n")
    
    print(f"数据已成功生成并保存到 {filename}")

# 控制生成数据的行数
num_lines = 1000  # 生成 10 行数据
generate_data(num_lines)
