from typing import List

def binarySearch(nums, left, right, target):
	while True:
		p = (left+right)//2
		if nums[p] == target:
			return p
		if left == right:
			break
		if nums[p] < target:
			left = min(p+1,right)
		else:
			right = max(p-1,left)
	return -1

class Solution:
	def searchRange(self, nums: List[int], target: int) -> List[int]:
		if len(nums) == 0:
			return [-1,-1]
		if len(nums) == 1:
			return [0,0] if nums[0] == target else [-1,-1]

		p = binarySearch(nums,0,len(nums)-1,target)
		if p == -1:
			return [-1,-1]

		ll, rr = p,p
		while ll-1 >= 0 and nums[ll-1] == target:
			ll -= 1
		while rr+1 < len(nums) and nums[rr+1] == target:
			rr += 1
		return [ll,rr]

sol = Solution()
print(sol.searchRange([5,7,7,8,8,10],10))