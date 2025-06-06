class Solution:
    def numSquares(self, n: int) -> int:
        # 创建一个数组，记录每个数的最小平方数个数
        dp = [0] * (n + 1)
        
        # 从 1 到 n 遍历每个数
        for i in range(1, n + 1):
            # 初始化当前最小值为正无穷
            min_squares = float('inf')
            
            # 遍历所有小于等于当前数 i 的平方数
            j = 1
            while j * j <= i:
                # 更新最小平方数个数
                min_squares = min(min_squares, dp[i - j * j])
                j += 1
                
            # 更新当前数 i 的最小平方数个数
            dp[i] = min_squares + 1
            
        return dp[n]