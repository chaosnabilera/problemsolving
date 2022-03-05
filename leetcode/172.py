class Solution:
	def trailingZeroes(self, n: int) -> int:
		count = 0
		factor = 5
		while n//factor > 0:
			count += n//factor
			factor *= 5
		return count


sol = Solution()
print(sol.trailingZeroes(10000))