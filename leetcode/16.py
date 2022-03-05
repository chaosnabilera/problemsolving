from typing import List
import collections

def updateAnswer(closestsum, absdiff, target, sum2, n):
	sum3 = sum2+n
	curabsdiff = abs(target-sum3)
	if curabsdiff < absdiff:
		closestsum = sum3
		absdiff = curabsdiff
	return closestsum, absdiff

class Solution:
	def threeSumClosest(self, nums: List[int], target: int) -> int:
		sum2dict = {}
		for i in range(len(nums)-1):
			for j in range(i+1, len(nums)):
				sum2 = nums[i] + nums[j]
				if sum2 not in sum2dict:
					sum2dict[sum2] = (i,j)
				elif sum2dict[sum2] != True:
					if len(sum2dict[sum2]) == 2:
						a,b = sum2dict[sum2]
						if a != i and a != j and b != i and b != j:
							sum2dict[sum2] = True
						else:
							if a == i or a == j:
								sum2dict[sum2] = (a,)
							else:
								sum2dict[sum2] = (b,)
					else:
						#print('>',i,j,sum2dict[sum2])
						a, = sum2dict[sum2]
						if a != i and a != j:
							sum2dict[sum2] = True
						#print('>>',i,j,sum2dict)
				#print(i,j,sum2dict)

		closestsum = nums[0]+nums[1]+nums[2]
		absdiff = abs(target-closestsum)

		for sum2 in sum2dict:
			if sum2dict[sum2] == True:
				for i in range(len(nums)):
					closestsum, absdiff = updateAnswer(closestsum, absdiff, target, sum2, nums[i])
			elif len(sum2dict[sum2]) == 2:
				a,b = sum2dict[sum2]
				for i in range(len(nums)):
					if i != a and i != b:
						closestsum, absdiff = updateAnswer(closestsum, absdiff, target, sum2, nums[i])
			else:
				a, = sum2dict[sum2]
				for i in range(len(nums)):
					if i != a:
						closestsum, absdiff = updateAnswer(closestsum, absdiff, target, sum2, nums[i])

		return closestsum

ilist = [-16,-2,17,-16,3,-7,-13,20,-4,12,5,13,-7,0,5,4,-17,-16,9,1,8,-6,0,-8,16,10,-6,9,-4,12,16,5,19,2,-9,-17,-8,-17,7,-10,2,20,-18,-20,-14,-6,6,17,-10,-8,18,-15,7,-9,13,13,-13,3,18,10,12,16,-6,-19,-6,-13,8,-5,16,5,8,-3,-9,-9,-5,14,14,-13,-18,13,15,-3,9,14,18,-14,-14,1,20,-4,-6,0,3,15,20,20,9,13,-8,-1,-2,6]
itarget = -58

sol = Solution()
print(sol.threeSumClosest(ilist, itarget))

