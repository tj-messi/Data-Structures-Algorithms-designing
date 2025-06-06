import time
import random
import matplotlib.pyplot as plt

class BruteForceCardDistribution:
    def __init__(self, cards):
        self.cards = cards  # 卡片价值列表
        self.n = len(cards)
        self.total_sum = sum(cards)  # 所有卡片总价值

    def solve(self):
        min_diff = float('inf')  # 最小差值
        best_a_cards = None  # A 得到的最优卡片编号
        best_b_cards = None  # B 得到的最优卡片编号
        best_a_value = 0  # A 的最优总价值

        # 枚举每张卡片的分配情况 (0 表示给 B, 1 表示给 A)
        for mask in range(1 << self.n):
            a_indices = []
            b_indices = []
            # 根据 mask 分配卡片
            for i in range(self.n):
                if mask & (1 << i):
                    a_indices.append(i)  # 给 A
                else:
                    b_indices.append(i)  # 给 B

            # 计算 A 的总价值
            a_value = sum(self.cards[i] for i in a_indices)
            # B 的总价值
            b_value = self.total_sum - a_value
            # 计算差值
            diff = abs(a_value - b_value)

            # 更新最小差值和最优方案
            if diff < min_diff:
                min_diff = diff
                best_a_value = a_value
                best_a_cards = sorted([i + 1 for i in a_indices])  # 卡片编号从 1 开始
                best_b_cards = sorted([i + 1 for i in b_indices])

        return min_diff, best_a_cards, best_b_cards, best_a_value

class DynamicProgrammingCardDistribution:
    def __init__(self, cards):
        self.cards = cards  # 卡片价值列表
        self.n = len(cards)
        self.total_sum = sum(cards)  # 所有卡片总价值

    def solve(self):
        max_value = self.total_sum + 1
        # dp[j] 表示是否可以选择总价值为 j 的子集
        dp = [False] * max_value
        dp[0] = True  # 初始状态：不选卡片，价值为 0

        # 记录选择的卡片
        choice = [[] for _ in range(max_value)]

        # 动态规划
        for i in range(self.n):
            # 倒序更新，防止覆盖
            for j in range(max_value - 1, self.cards[i] - 1, -1):
                if dp[j - self.cards[i]]:
                    dp[j] = True
                    # 记录选择路径
                    new_choice = choice[j - self.cards[i]] + [i]
                    if not choice[j] or new_choice < choice[j]:
                        choice[j] = new_choice

        # 找到最接近 total_sum/2 的价值
        target = self.total_sum / 2
        min_diff = float('inf')
        best_a_value = 0
        best_a_indices = None

        # 遍历所有可能的 A 总价值
        for j in range(max_value):
            if dp[j]:
                a_value = j
                b_value = self.total_sum - a_value
                diff = abs(a_value - b_value)
                if diff < min_diff:
                    min_diff = diff
                    best_a_value = a_value
                    best_a_indices = choice[j]

        # A 和 B 的卡片编号
        best_a_cards = sorted([i + 1 for i in best_a_indices])
        all_indices = set(range(self.n))
        best_b_cards = sorted([i + 1 for i in (all_indices - set(best_a_indices))])

        return min_diff, best_a_cards, best_b_cards, best_a_value

# 测试代码
if __name__ == "__main__":
    # 设置随机种子以确保可重复性
    random.seed(42)

    # 枚举 n 从 5 到 30
    n_values = range(5, 26)
    bf_times = []
    dp_times = []

    # 打开文件保存结果
    with open("times_comparison.txt", "w") as f:
        f.write("n, Brute Force Time (s), Dynamic Programming Time (s)\n")

        for n in n_values:
            # 随机生成 n 个卡片，价值为 1 到 n
            cards = [random.randint(1, n) for _ in range(n)]
            print(f"\nTesting with n = {n}, cards: {cards}")

            # 暴力方法
            start_time_bf = time.time()
            brute_force = BruteForceCardDistribution(cards)
            min_diff_bf, a_cards_bf, b_cards_bf, a_value_bf = brute_force.solve()
            end_time_bf = time.time()
            time_bf = end_time_bf - start_time_bf

            # 动态规划方法
            start_time_dp = time.time()
            dp = DynamicProgrammingCardDistribution(cards)
            min_diff_dp, a_cards_dp, b_cards_dp, a_value_dp = dp.solve()
            end_time_dp = time.time()
            time_dp = end_time_dp - start_time_dp + 0.000001  # 避免除以零

            # 记录运行时间
            bf_times.append(time_bf)
            dp_times.append(time_dp)

            # 保存到文件
            f.write(f"{n}, {time_bf:.6f}, {time_dp:.6f}\n")

            # 输出当前 n 的结果
            print(f"暴力方法运行时间: {time_bf:.6f} 秒")
            print(f"动态规划方法运行时间: {time_dp:.6f} 秒")

    # 可视化
    plt.figure(figsize=(10, 6))
    plt.plot(n_values, bf_times, label="Brute Force", marker="o")
    plt.plot(n_values, dp_times, label="Dynamic Programming", marker="o")
    plt.xlabel("Number of Cards (n)")
    plt.ylabel("Running Time (seconds)")
    plt.title("Comparison of Brute Force vs Dynamic Programming Running Time")
    plt.legend()
    plt.grid(True)
    plt.yscale("log")  # 使用对数刻度，因为时间范围可能差异较大
    plt.savefig("time_comparison.png")
    plt.show()

    # 总结对比
    print("\n运行时间对比总结：")
    for n, bf_t, dp_t in zip(n_values, bf_times, dp_times):
        print(f"n = {n}: Brute Force = {bf_t:.6f}s, Dynamic Programming = {dp_t:.6f}s, DP is {bf_t / dp_t:.2f} times faster")
