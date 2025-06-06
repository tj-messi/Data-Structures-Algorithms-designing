import time
import random

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

    # 用户输入卡片数量 n
    n = 20

    # 随机生成 n 个卡片，价值为 1 到 n
    cards = [random.randint(1, n) for _ in range(n)]
    print(f"随机生成的卡片价值: {cards}")

    # 暴力方法
    start_time_bf = time.time()
    brute_force = BruteForceCardDistribution(cards)
    min_diff_bf, a_cards_bf, b_cards_bf, a_value_bf = brute_force.solve()
    end_time_bf = time.time()
    time_bf = end_time_bf - start_time_bf

    print("\n暴力方法结果：")
    print(f"最小差值: {min_diff_bf}")
    print(f"A 得到的卡片: {a_cards_bf}, 总价值: {a_value_bf}")
    print(f"B 得到的卡片: {b_cards_bf}, 总价值: {sum(cards) - a_value_bf}")
    print(f"运行时间: {time_bf:.6f} 秒\n")

    # 动态规划方法
    start_time_dp = time.time()
    dp = DynamicProgrammingCardDistribution(cards)
    min_diff_dp, a_cards_dp, b_cards_dp, a_value_dp = dp.solve()
    end_time_dp = time.time()
    time_dp = end_time_dp - start_time_dp + 0.000001  # 加上微小的误差

    print("动态规划方法结果：")
    print(f"最小差值: {min_diff_dp}")
    print(f"A 得到的卡片: {a_cards_dp}, 总价值: {a_value_dp}")
    print(f"B 得到的卡片: {b_cards_dp}, 总价值: {sum(cards) - a_value_dp}")
    print(f"运行时间: {time_dp:.6f} 秒\n")

    # 比较运行时间
    print("运行时间对比：")
    print(f"暴力方法: {time_bf:.6f} 秒")
    print(f"动态规划方法: {time_dp:.6f} 秒")
    print(f"动态规划比暴力方法快: {time_bf / time_dp:.2f} 倍")