class Solution:
    def  judgePoint24(self, cards):
        nums = [float(card) for card in cards]
        return self._dfs(nums)

    def _dfs(self, nums):
        if len(nums) == 1:
            return abs(nums[0] - 24) <= 1e-6
        for i in range(len(nums)):
            for j in range(len(nums)):
                if i == j:
                    continue  

                a = nums[i]
                b = nums[j]
                remaining_nums = [nums[k] for k in range(len(nums)) if k != i and k != j]


                results = [
                    a + b,
                    a - b,
                    a * b,
                    a / b if b != 0 else float('inf')  
                ]
                for result in results:
                    remaining_nums.append(result)
                    if self._dfs(remaining_nums):
                        return True
                    remaining_nums.pop()  # 回溯

        return False
