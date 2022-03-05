from typing import List

class Solution:
    def verifyPreorder(self, preorder: List[int]) -> bool:
        if len(preorder) == 0:
            return True
        
        N = len(preorder)
        L = 0x1111
        R = 0x9999
        
        stack = [[preorder[0],L,-float('inf'),float('inf')]]
        
        for i in range(1,N):
            v = preorder[i]
            pv,pmode,pmin,pmax = stack[-1]
            
            if v < pv:    
                if pmode != L:
                    return False
                if v <= pmin:
                    return False
                
                stack[-1][1] = R
                stack.append([v,L,pmin,pv])
                
            else:
                while stack:
                    pv,pmode,pmin,pmax = stack[-1]
                    if pmode == L:
                        stack.pop()
                    elif v >= pmax:
                        stack.pop()
                    else:
                        stack.pop()
                        stack.append([v,L,pv,pmax])
                        break
                
                if not stack:
                    return False
            
        return True

idata = [5,2,1,3,6]
sol = Solution()
print(sol.verifyPreorder(idata))