from typing import List

def searchPivot(nums):
	left = 0
	right = len(nums)-1
	while True:
		if right == left+1:
			return right
		else:
			p = (left+right)//2
			if nums[left] < nums[p]:
				left = p
			else:
				right = p

def binarySearch(nums, left, right, target):
	# if target < nums[left] or target > nums[right]:
	# 	return -1

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
	def search(self, nums: List[int], target: int) -> int:
		if len(nums) == 1:
			return 0 if (target == nums[0]) else -1
		
		if nums[0] > nums[-1]:
			pivot = searchPivot(nums)
			if target == nums[0]:
				return 0
			elif target > nums[0]:
				return binarySearch(nums, 0, pivot-1, target)
			else:
				return binarySearch(nums, pivot, len(nums)-1, target)
		else:
			return binarySearch(nums, 0, len(nums)-1, target)

		

#print(searchPivot([11,12,13,14,15,16,17,18,19,20,0,1,2,4,5,6,7]))

sol = Solution()
print(sol.search([5,1,3],0))

