from collections import defaultdict
from collections import deque

class Solution:
    def canConvert(self, str1: str, str2: str) -> bool:
        if str1 == str2:
            return True

        N = len(str1)
        mapping = defaultdict(set)
        alphabet1 = set([])
        alphabet2 = set([])

        for i in range(N):
            c1,c2 = str1[i],str2[i]
            alphabet1.add(c1)
            alphabet2.add(c2)

            mapping[c1].add(c2)
            if len(mapping[c1]) > 2:
                return False

        return (len(alphabet1) < 26) or (len(alphabet2)<26)


sol = Solution()
# str1 = "abcdefghijklmnopqrstuvwxyz"
# str2 = "bcadefghijklmnopqrstuvwxzz"

str1 = "abcdefghijklmnopqrstuvwxyz"
str2 = "bcdefghijklmnopqrstuvwxyzq"

print(sol.canConvert(str1,str2))