class Solution:
	def threeSumClosest(self, nums: List[int], target: int) -> int:
		nums.sort()
		
		closestsum = nums[0]+nums[1]+nums[2]
		absdiff = abs(target-closestsum)
		foundexact = False
		
		for i in range(len(nums)-2):
			cur = i
			lo = cur + 1
			hi = len(nums)-1
			
			while lo < hi:
				sum3 = nums[cur]+nums[lo]+nums[hi]
				curabsdiff = abs(target-sum3)
				if sum3 == target:
					return target
				
				if curabsdiff < absdiff:
					closestsum = sum3
					absdiff = curabsdiff
				
				if sum3 > target:
					hi -= 1
				else:
					lo += 1
					
		return closestsum