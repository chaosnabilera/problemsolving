from typing import *

class Solution:
    def maxArea(self, height: List[int]) -> int:
        height = [(height[i],i) for i in range(len(height))]
        height.sort(key=lambda t:(-t[0],t[1]))

        if height[0][1] < height[1][1]:
            lh,li = height[0]
            rh,ri = height[1]
        else:
            lh,li = height[1]
            rh,ri = height[0]
            
        maxarea = min(lh,rh) * (ri-li)
            
        for si in range(2,len(height)):
            h,i = height[si]
            li = min(i,li)
            ri = max(i,ri)
            maxarea = max((ri-li)*h, maxarea)
        
        return maxarea
                

hey = Solution()
print(hey.maxArea([76,155,15,188,180,154,84,34,187,142,22,5,27,183,111,128,50,58,2,112,179,2,100,111,115,76,134,120,118,103,31,146,58,198,134,38,104,170,25,92,112,199,49,140,135,160,20,185,171,23,98,150,177,198,61,92,26,147,164,144,51,196,42,109,194,177,100,99,99,125,143,12,76,192,152,11,152,124,197,123,147,95,73,124,45,86,168,24,34,133,120,85,81,163,146,75,92,198,126,191]))