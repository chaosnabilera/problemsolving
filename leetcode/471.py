from functools import lru_cache

class Solution:
    def encode(self, s: str) -> str:
        @lru_cache(maxsize=None)
        def shorten(s):
            if len(s) <= 4:
                return s

            res = [s]
            for beg in range(1,len(s)):
                res.append(s[:beg] + shorten(s[beg:]))

            for patlen in range(1,(len(s)>>1)+1):
                pat = s[:patlen]
                cnt = 1
                end = patlen
                while s.find(pat,end) == end:
                    cnt += 1
                    end += patlen
                    res.append(f'{cnt}[{shorten(s[:end])}]{shorten(s[end:])}')

            return min(res, key=len)

        return shorten(s)


sol = Solution()
s = "aaaaaaaaaabbbaaaaabbb"
print(sol.encode(s))
