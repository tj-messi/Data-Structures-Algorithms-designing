class Solution:
    def partition(self, s: str):
        result = []
        palindrome_parts = self.find_palindromes(s)
        palindrome_parts.sort(key=lambda p: p[0])

        for i in range(len(palindrome_parts)):
            if palindrome_parts[i][0] == 0:
                self.backtrack(palindrome_parts, i, s, [], result)
        
        return result
    
    def find_palindromes(self, s: str):
        palindrome_list = []
        n = len(s)

        for i in range(n):

            palindrome_list.append([i, i + 1])  # 单个字符是回文
            
            j = 1
            while i - j >= 0 and i + j < n:
                if s[i - j] == s[i + j]:
                    palindrome_list.append([i - j, i + j + 1])
                    j += 1
                else:
                    break

            if i < n - 1 and s[i] == s[i + 1]:
                palindrome_list.append([i, i + 2])
                j = 1
                while i - j >= 0 and i + 1 + j < n:
                    if s[i - j] == s[i + 1 + j]:
                        palindrome_list.append([i - j, i + j + 2])
                        j += 1
                    else:
                        break
        
        return palindrome_list

    def backtrack(self, parts, index, s, current_partition, result):

        if not current_partition:
            current_partition.append(s[parts[index][0]:parts[index][1]])
 
        if parts[index][1] == len(s):
            result.append(list(current_partition))  
            return
    
        for i in range(index + 1, len(parts)):
            if parts[i][0] == parts[index][1]: 
                current_partition.append(s[parts[i][0]:parts[i][1]])  
                self.backtrack(parts, i, s, current_partition, result)  
                current_partition.pop()  # 回溯
