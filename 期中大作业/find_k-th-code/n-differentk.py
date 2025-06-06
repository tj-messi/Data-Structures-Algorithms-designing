import matplotlib.pyplot as plt
import pandas as pd
import re

def read_data(filename):
    # 初始化数据结构
    data = {'k': [], 'Heap Selection': [], 'Randomized Select': [], 'Median of Medians': []}
    
    with open(filename, 'r') as f:
        lines = f.readlines()
        current_k = None
        heap_time = random_time = median_time = None
        
        for line in lines:
            # 匹配n 和 k 的值
            n_match = re.match(r'n = (\d+), k = (\d+)', line.strip())
            if n_match:
                current_k = int(n_match.group(2))
                continue

            # 解析每种算法的数据
            heap_match = re.match(r'Heap Selection: (\d+), Time Taken: (\d+\.\d+)', line.strip())
            if heap_match:
                heap_time = float(heap_match.group(2))
                continue
            
            random_match = re.match(r'Randomized Select: (\d+), Time Taken: (\d+\.\d+)', line.strip())
            if random_match:
                random_time = float(random_match.group(2))
                continue
            
            median_match = re.match(r'Median of Medians: (\d+), Time Taken: (\d+\.\d+)', line.strip())
            if median_match:
                median_time = float(median_match.group(2))
                # 保存数据
                data['k'].append(current_k)
                data['Heap Selection'].append(heap_time)
                data['Randomized Select'].append(random_time)
                data['Median of Medians'].append(median_time)
    
    return pd.DataFrame(data)

def plot_data(df, n):
    # 只选择 k 的每 50 个值可视化
    k_values = df['k']
    k_selected = k_values[::50]  # 每隔 50 步选择一个 k
    heap_times_selected = df['Heap Selection'][::50]
    random_times_selected = df['Randomized Select'][::50]
    median_times_selected = df['Median of Medians'][::50]
    
    # 创建图表
    plt.figure(figsize=(10, 6))
    
    # 绘制三种算法的时间曲线
    plt.plot(k_selected, heap_times_selected, label='Median of Medians', color='blue', marker='o')
    plt.plot(k_selected, random_times_selected, label='Randomized Select', color='green', marker='s')
    plt.plot(k_selected, median_times_selected, label='Heap Selection', color='red', marker='^')
    
    # 添加图表标题和标签
    plt.title(f"Algorithm Execution Time for n={n}")
    plt.xlabel('k')
    plt.ylabel('Time (seconds)')
    
    # 添加图例
    plt.legend()
    
    # 显示图表
    plt.show()

def main():
    # 输入文件名（假设txt文件已经存储在该路径下）
    filename = r'C:\Users\asus\Desktop\Data-Structures-Algorithms-designing\期中大作业\find_k-th-ans\results-100000.txt'  # 你可以替换为文件的实际路径
    
    # 读取数据并整理
    df = read_data(filename)
    
    # 提取 n 值（假设 n 是固定的）
    n = 1000  # 根据你的数据调整 n
    
    # 绘制图表
    plot_data(df, n)

if __name__ == "__main__":
    main()
