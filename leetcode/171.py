from typing import List

class Solution:
    def titleToNumber(self, s: str) -> int:
        num = 0
        factor = 1
        for i in range(-1, -len(s)-1, -1):
            coeff = (ord(s[i])-ord('A'))+1
            num += coeff*factor
            factor *= 26
        return num

hey = Solution()
print(hey.titleToNumber("FXSHRXW"))