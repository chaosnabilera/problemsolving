import random
import copy

from typing import List

class Solution:
    def findKthLargest(self, nums: List[int], k: int) -> int:
        begin = 0
        end = len(nums)-1
        kk = len(nums)-k
        #print(nums)
        
        while True:
            pivot = random.randint(begin,end)
            # print('nums[begin={}]={}  nums[end={}]={}  nums[pivot={}]={}'.format(
            #    begin, nums[begin], end, nums[end], pivot, nums[pivot]))
            pivot_val = nums[pivot]
            nums[begin], nums[pivot] = nums[pivot], nums[begin]
            l = begin+1
            r = end
            
            while l <= end and nums[l] < pivot_val:
                l += 1
            
            #print('nums[l={}]={}  nums[r={}]={}'.format(l,nums[l],r,nums[r]))

            while r >= l:
                if nums[l] < pivot_val:
                    l += 1
                    continue
                elif nums[r] < pivot_val:
                    nums[l],nums[r] = nums[r],nums[l]
                    l += 1
                r -= 1
            
            pivot = l-1
            nums[begin],nums[pivot] = nums[pivot],nums[begin]
            
            if pivot == kk:
                break
            elif pivot > kk:
                end = pivot-1
            else:
                begin = pivot+1
            
            #print(nums)
        
        return nums[kk]

ilist = [3,2,3,1,2,4,5,5,6]
k = 4

sol = Solution()
clist = copy.deepcopy(ilist)
clist.sort()
print(sol.findKthLargest(ilist,k))
print(clist[len(ilist)-k])