import matplotlib.pyplot as plt

# 数据
n_values = [10, 12, 15, 20]
brute_force_times = [11662, 48281, 411472, 14560463]  # 暴力法用时（微秒）
dp_times = [555, 718, 1000, 1830]  # 动态规划用时（微秒）

# 计算速度提升（动态规划时间 / 暴力法时间）
speed_up = [brute / dp for brute, dp in zip(brute_force_times, dp_times)]

# 创建图形
fig, ax1 = plt.subplots(figsize=(10, 6))

# 绘制暴力法和动态规划的用时
ax1.plot(n_values, brute_force_times, label="Brute Force Time", color="blue", marker="o", linestyle='-', linewidth=2)
ax1.plot(n_values, dp_times, label="Dynamic Programming Time", color="green", marker="s", linestyle='-', linewidth=2)

# 设置主坐标轴标签
ax1.set_xlabel('n (Problem Size)', fontsize=14)
ax1.set_ylabel('Time (Microseconds)', fontsize=14)
ax1.set_title('Brute Force vs Dynamic Programming Time Complexity', fontsize=16)

# 创建第二坐标轴，用于绘制速度提升
ax2 = ax1.twinx()
ax2.plot(n_values, speed_up, label="Speed Up", color="red", marker="^", linestyle='--', linewidth=2)

# 设置第二坐标轴标签
ax2.set_ylabel('Speed Up (DP/Brute Force)', fontsize=14)

# 添加图例
ax1.legend(loc='upper left', fontsize=12)
ax2.legend(loc='upper right', fontsize=12)

# 显示图表
plt.show()
