import random

def generate_data(n, filename="find_k-th_data-100000000.txt"):
    # 随机生成 k 值（1 <= k <= n）
    k = random.randint(1, n)
    
    # 生成一个不重复的元素集合
    # 使用 set 保证集合中的元素唯一
    data = random.sample(range(1, 10*n), n)  # 生成 n 个不重复的元素，范围从 1 到 100
    
    # 写入文件
    with open(filename, "w") as file:
        # 输出 k 值
        file.write(f"Random k: {k}\n")
        
        # 输出 n 个元素，元素之间用空格分隔
        file.write(" ".join(map(str, data)) + "\n")
    
    print(f"数据已生成并保存到 {filename}")
    print(f"Random k: {k}")
    print("Data:", data)

# 控制生成数据的条数
n = 100000000  # 生成 10 个不重复的元素
generate_data(n)
