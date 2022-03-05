from typing import List
import random

class Solution:
    def singleNumber(self, nums: List[int]) -> int:
        left, right = 0, len(nums)

        while left < right:
            pivot = random.randint(left,right-1)
            nums[left],nums[pivot] = nums[pivot],nums[left]
            pivotval = nums[left]
            ll = left  # point where the value is definitely less or equal to pivot value
            rr = right # point beyond from which the values are strictly greater than pivot value
            while rr - ll > 1:
                if nums[ll+1] <= pivotval:
                    ll += 1
                else:
                    nums[ll+1], nums[rr-1] = nums[rr-1], nums[ll+1]
                    rr -= 1

            if left == ll:
                return nums[ll]

            if ((rr - left) & 1):
                right = rr
            else:
                left = rr
            
        

hey = Solution()
print(hey.singleNumber([1,1,3]))