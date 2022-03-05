from typing import List

def isPalindrome(cstr):
	return cstr == cstr[::-1]

def recPartition(res, src):
	for i in range(len(src)):
		myres = []
		curtok = src[:i+1]
		if not isPalindrome(curtok):
			continue
		nexttok = src[i+1:]
		if len(nexttok) == 0:
			res.append([curtok])
		else:
			recPartition(myres, src[i+1:])
			for mr in myres:
				res.append([curtok]+mr)

class Solution:
	def partition(self, s: str) -> List[List[str]]:
		res = []
		recPartition(res, s)
		return res

sol = Solution()
print(sol.partition("aaaba"))