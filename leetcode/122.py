from typing import List

class Solution:
    def titleToNumber(self, s: str) -> int:
        if len(s) == 1:
        	return ord(s)-ord('A')+1
        else:
        	num = 0
        	factor = 1
        	for i in range(-1, -len(s)-1, -1):
        		num += (ord(s[i])-ord('A'))*factor
        		factor *= 26
        	return num

hey = Solution()
print(hey.titleToNumber("AA"))