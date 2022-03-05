class Solution:
    def bruteforce(self, beg, end):
        next_x = [1,6,None,None,None,None,8,None,9,0]
        palin  = [0,1,None,None,None,None,9,None,8,6]

        D = len(beg)-1
        cnt = 0
        # print('>',beg)

        while beg <= end:
            is_confusing = 0

            bi = 0
            ei = len(beg)-1
            while bi<ei and beg[bi] == 0:
                bi += 1

            if ((ei-bi+1) & 1) and beg[(ei+bi)>>1] in [6,9]:
                is_confusing = 1

            while not is_confusing and bi <= ei:
                if beg[bi] != palin[beg[ei]]:
                    is_confusing = 1
                bi += 1
                ei -= 1
            
            cnt += is_confusing
            # if not is_confusing:
            #     print(D,beg)

            di = len(beg)-1
            while True:
                beg[di] = next_x[beg[di]]
                if beg[di] != 0:
                    break
                beg[di] = 0
                di -= 1
        
        # print('>',end)
        return cnt


    def confusingNumberII(self, N: int) -> int:
        digits = [int(c) for c in str(N)]

        cn_digit = [0]*len(digits)
        
        cn_digit[1] = 2
        for d in range(2,len(digits)):
            cn_digit[d] = 4 * (5**(d-1))
            if d & 1 == 0:
                cn_digit[d] -= 4 * (5 ** ((d>>1)-1))
            else:
                cn_digit[d] -= 4 * (5 ** ((d>>1)-1)) * 3
                
        cum_digit = [0]*len(digits)
        for d in range(1,len(digits)):
            cum_digit[d] = cum_digit[d-1] + cn_digit[d]

        cnt = cum_digit[-1]

        d = len(digits)
        for cd in [1,6,8,9]:
            if cd >= digits[0]:
                break

            cnt += (5**(d-1))
            if d & 1 == 0:
                cnt -= (5 ** ((d>>1)-1))
            else:
                cnt -= (5 ** ((d>>1)-1)) * 3

        if cd > digits[0]:
            return cnt

        beg = [0] * (len(digits)+1)
        beg[1] = digits[0]
        end = [0] + digits

        cnt += self.bruteforce(beg, end)
        return cnt


sol = Solution()
print(sol.confusingNumberII(660000))
#print(sol.bruteforce([0,0,0,0,0,0,0],[0,6,6,0,0,0,0]))

#print(sol.confusingNumberII(66120))