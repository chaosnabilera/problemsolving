from typing import List

class Solution:
	def wordBreak(self, s: str, wordDict: List[str]) -> bool:
		dp = [False] * (len(s)+1)
		dp[-1] = True

		lwdict = {}
		for word in wordDict:
			if len(word) not in lwdict:
				lwdict[len(word)] = set([])
			lwdict[len(word)].add(word)

		lwlist = list(lwdict.keys())
		lwlist.sort()

		for i in range(len(s)-1, -1, -1):
			di = 0
			while di < len(lwlist) and i+lwlist[di] <= len(s):
				d = lwlist[di]
				tok = s[i:i+d]
				if (d in lwdict) and dp[i+d] and (tok in lwdict[d]):
					dp[i] = True
					break
				di += 1

		return dp[0]

# s = 'leetcode'
# wd = ["leet", "code"]

s = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaab"
wd = ["a","aa","aaa","aaaa","aaaaa","aaaaaa","aaaaaaa","aaaaaaaa","aaaaaaaaa","aaaaaaaaaa"]

sol = Solution()
print(sol.wordBreak(s,wd))
