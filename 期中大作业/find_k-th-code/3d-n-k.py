import matplotlib.pyplot as plt
import pandas as pd
import re
from mpl_toolkits.mplot3d import Axes3D

def read_data(filename):
    # 初始化数据结构
    data = {'n': [], 'k': [], 'Heap Selection': [], 'Randomized Select': [], 'Median of Medians': []}
    
    with open(filename, 'r') as f:
        lines = f.readlines()
        current_n, current_k = None, None
        heap_time = random_time = median_time = None
        
        for line in lines:
            # 匹配n 和 k 的值
            n_match = re.match(r'n = (\d+), k = (\d+)', line.strip())
            if n_match:
                current_n = int(n_match.group(1))
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
                print(f"n = {current_n}, k = {current_k}, Heap Selection: {heap_time}, Randomized Select: {random_time}, Median of Medians: {median_time}")
                data['n'].append(current_n)
                data['k'].append(current_k)
                data['Heap Selection'].append(heap_time)
                data['Randomized Select'].append(random_time)
                data['Median of Medians'].append(median_time)
    
    return pd.DataFrame(data)

def plot_3d_data(df):
    # 只选择 n 和 k 每 10 步的值来稀疏化数据
    sparse_df = df[(df['n'] % 100 == 0) & (df['k'] % 100 == 0)]
    
    # 提取 n, k, 各种算法的时间
    x = sparse_df['k']
    y = sparse_df['n']
    z_heap = sparse_df['Heap Selection']
    z_random = sparse_df['Randomized Select']
    z_median = sparse_df['Median of Medians']
    
    # 创建三维图
    fig = plt.figure(figsize=(10, 8))
    ax = fig.add_subplot(111, projection='3d')
    
    # 绘制三维散点图
    ax.scatter(x, y, z_heap, label='Median of Medians', color='blue', marker='o')
    ax.scatter(x, y, z_random, label='Randomized Select', color='green', marker='s')
    ax.scatter(x, y, z_median, label='Heap Selection', color='red', marker='^')

    # 设置标题和轴标签
    ax.set_title("Algorithm Execution Time Comparison (Sparse Data)")
    ax.set_xlabel('k')
    ax.set_ylabel('n')
    ax.set_zlabel('Time (seconds)')
    
    # 添加图例
    ax.legend()
    
    # 显示图表
    plt.show()

def main():
    # 输入文件名（假设txt文件已经存储在该路径下）
    filenames = [
        r'C:\Users\asus\Desktop\Data-Structures-Algorithms-designing\期中大作业\find_k-th-ans\results-1000.txt',
        r'C:\Users\asus\Desktop\Data-Structures-Algorithms-designing\期中大作业\find_k-th-ans\results-2000.txt',
        r'C:\Users\asus\Desktop\Data-Structures-Algorithms-designing\期中大作业\find_k-th-ans\results-3000.txt',
        r'C:\Users\asus\Desktop\Data-Structures-Algorithms-designing\期中大作业\find_k-th-ans\results-4000.txt',
        r'C:\Users\asus\Desktop\Data-Structures-Algorithms-designing\期中大作业\find_k-th-ans\results-5000.txt',
        r'C:\Users\asus\Desktop\Data-Structures-Algorithms-designing\期中大作业\find_k-th-ans\results-6000.txt',
        r'C:\Users\asus\Desktop\Data-Structures-Algorithms-designing\期中大作业\find_k-th-ans\results-7000.txt',
        r'C:\Users\asus\Desktop\Data-Structures-Algorithms-designing\期中大作业\find_k-th-ans\results-8000.txt',
        r'C:\Users\asus\Desktop\Data-Structures-Algorithms-designing\期中大作业\find_k-th-ans\results-9000.txt',
        r'C:\Users\asus\Desktop\Data-Structures-Algorithms-designing\期中大作业\find_k-th-ans\results-10000.txt',
        # 添加更多的文件路径
    ]
    
    # 汇总所有数据
    all_data = []
    for filename in filenames:
        df = read_data(filename)
        all_data.append(df)
    
    # 合并所有数据
    combined_df = pd.concat(all_data, ignore_index=True)
    
    # 绘制三维图
    plot_3d_data(combined_df)

if __name__ == "__main__":
    main()
