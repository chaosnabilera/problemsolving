from typing import List
from copy import deepcopy
from random import randint

def findKthElement(nums: List[int], k: int) -> int:
    begin = 0
    end = len(nums)-1
    kk = k-1
    #print(nums)

    while True:
        pivot = randint(begin,end)
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

class Solution:
    def wiggleSort(self, nums: List[int]) -> None:
        """
        Do not return anything, modify nums in-place instead.
        """
        k = len(nums)//2 if (len(nums) & 1 == 0) else (len(nums)//2)+1
        #findKthElement(nums, len(nums))
        findKthElement(nums, k)
        
        # print(nums)
        
        # Reverse last bit
        begin = k
        end = len(nums)-1
        numreverse = (len(nums)-k)//2
        for i in range(numreverse):
            nums[begin+i],nums[end-i] = nums[end-i],nums[begin+i]
        
        l,r = k-2, k+1
        while r <= len(nums)-1:
            nums[l],nums[r] = nums[r],nums[l]
            l -= 2
            r += 2

for i in range(100):
    sol = Solution()
    ilist = [randint(-10,0) for i in range(randint(1,1000))]
    ilist += [randint(1,10) for i in range(len(ilist))]
    clist = deepcopy(ilist)
    sol.wiggleSort(ilist)

    if sorted(ilist) != sorted(clist):
        print('Element mismatch!',i)
        print(clist)
        print(ilist)
        print()
        continue

    for i in range(1, len(ilist)-1, 2):
        if ilist[i-1] >= ilist[i] or ilist[i+1] >= ilist[i]:
            print('Not wiggled!',i)
            print(clist)
            print(ilist)
            print()
            break