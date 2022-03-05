from typing import List

class Solution:
	def numDecodings(self, s: str) -> int:
		if s[0] == '0':
			return 0
		
		if len(s) == 1:
			return 1 if s[0] != '0' else 0
		
		dp = [0]*len(s)
		dp[-1] = 1 if s[-1] != '0' else 0
		if s[-2] == '0':
			dp[-2] = 0
		else:
			if (int(s[-2:]) >= 10) and (int(s[-2:]) <= 26):
				dp[-2] = dp[-1] + 1
			else:
				dp[-2] = dp[-1]

		for i in range(len(s)-3, -1, -1):
			if s[i] == '0':
				continue
			dp[i] += dp[i+1]
			n2 = int(s[i:i+2])
			if (n2 >= 10) and (n2 <= 26):
				dp[i] += dp[i+2]
				
			if dp[i] == 0:
				return 0

		return dp[0]

sol = Solution()
print(sol.numDecodings('26'))