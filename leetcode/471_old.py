from functools import lru_cache

class Solution:
    def encode(self, s: str) -> str:
        S = len(s)
        repcnt = [[0]*((S >> 1)+1) for i in range(S)]
        for beg in range(S):
            for rsize in range(1,(S>>1)+1):
                if repcnt[beg][rsize] != 0:
                    continue

                repcnt[beg][rsize] = 1
                curpat = s[beg:beg+rsize]
                for i in range(beg+rsize, S, rsize):
                    if curpat != s[i:i+rsize]:
                        break
                    repcnt[beg][rsize] += 1

                for i in range(1,repcnt[beg][rsize]):
                    repcnt[beg+(rsize*i)][rsize] = repcnt[beg][rsize]-i

        valid_div = [[] for i in range(S+1)]
        for i in range(1,S+1):
            for j in range(1,(i>>1)+1):
                if i%j == 0:
                    valid_div[i].append(j)

        @lru_cache(maxsize=None)
        def shortest(beg, end):
            if end <= beg:
                return ''

            if end-beg < 4:
                return s[beg:end]

            sslen = end-beg
            ss = s[beg:end]
            for rsize in valid_div[sslen]:
                if repcnt[beg][rsize]*rsize >= sslen:
                    curcnt = sslen // rsize
                    curpat = shortest(beg,beg+rsize)
                    ss = min(ss,f'{curcnt}[{curpat}]', key=len)

            for m in range(beg+1,end):
                ss = min(ss, shortest(beg,m)+shortest(m,end), key=len)

            return ss

        retval = shortest(0,S)
        return retval

sol = Solution()
s = "aaaaaaaaaabbbaaaaabbb"
print(sol.encode(s))
