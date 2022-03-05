class Solution:
    def divide(self, dividend: int, divisor: int) -> int:
        if ((dividend > 0) and (divisor < 0)) or ((dividend < 0) and (divisor > 0)):
            sign = -1
        else:
            sign = 1
            
        dividend = abs(dividend)
        divisor = abs(divisor)
        
        if dividend < divisor:
            return 0
        
        numleft = dividend
        res = 0
        
        while numleft > 0:
            factor = 1
            factornum = divisor
            while (factornum << 1) < numleft:
                factor <<= 1
                factornum <<= 1
            
            #print(factor,factornum,numleft)
            numleft -= factornum
            res += factor
            
            if numleft < divisor:
                break
        
        res = sign*res
        
        if res > 0:
            return min(res,2**31-1)
        else:
            return max(res,-2**31)

sol = Solution()
print(sol.divide(10,-3))