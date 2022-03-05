from typing import List

def product(nums, beg, end):
	p = 1
	for i in range(beg,end+1):
		p *= nums[i]
	return p

def solve(nums, beg, end, numneg, negbeg, negend):
	if numneg & 1 == 0:
		return product(nums, beg, end)
	else:
		if (negbeg+1 <= end) and (beg <= negend-1):
			after_negbeg = product(nums, negbeg+1, end)
			before_negend = product(nums, beg, negend-1)
			return max(after_negbeg, before_negend)
		elif negbeg+1 <= end:
			return product(nums, negbeg+1, end)
		elif beg <= negend-1:
			return product(nums, beg, negend-1)
		else:
			return nums[negbeg]

class Solution:
	def maxProduct(self, nums: List[int]) -> int:
		i = 0
		beg, end = None, None
		numneg = 0
		negbeg, negend = None, None
		maxproduct = None

		while True:
			if i == len(nums):
				if beg != None:
					ans = solve(nums, beg, end, numneg, negbeg, negend)
					maxproduct = max(maxproduct,ans) if maxproduct != None else ans
				break

			if nums[i] == 0:
				maxproduct = max(maxproduct, 0) if maxproduct != None else 0
				if beg != None:
					ans = max(0, solve(nums, beg, end, numneg, negbeg, negend))
					maxproduct = max(maxproduct,ans)
					beg, end, numneg, negbeg, negend = None, None, 0, None, None
			else:
				beg = beg if beg != None else i
				end = i
				if nums[i] < 0:
					negbeg = negbeg if negbeg != None else i
					negend = i
					numneg += 1

			i += 1

		return maxproduct

inums = [0,0,0,0,0,0,0,1,0,0,0,0,7,8,0,0,99]
sol = Solution()
print(sol.maxProduct(inums))