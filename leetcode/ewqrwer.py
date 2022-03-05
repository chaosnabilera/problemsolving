from functools import lru_cache

class Solution:
    def encode(self, s: str) -> str:
        @lru_cache(maxsize=None)
        def code(s):
            if s == "":
                return ""

            res = [s]
            for i in range(1, len(s)):
                res.append(s[:i] + code(s[i:]))
                
            for i in range(1, len(s) + 1):
                pre = s[:i]
                occr = 1
                j = i
                while s.find(pre, j) == j:
                    occr += 1
                    j += len(pre)
                    thisres = "%d[%s]%s" % (occr, code(pre), code(s[j:]))
                    res.append(thisres)
            return min(res, key=len)
        return code(s)