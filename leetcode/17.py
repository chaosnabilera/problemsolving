from typing import List

class Solution:
	def letterCombinations(self, digits: str) -> List[str]:
		if len(digits) == 0:
			return []

		dl = ['abc','def','ghi','jkl','mno','pqrs','tuv','wxyz']
		digits = [int(c)-2 for c in digits]
		
		comnum = [0]*len(digits)
		comnum[-1] = 1
		for i in range(1, len(comnum)):
			lastdigit = digits[-1-i+1]
			lastdigitnumcomb = len(dl[lastdigit])
			comnum[-1-i] = comnum[-1-i+1] * lastdigitnumcomb
		totcom = 1
		for d in digits:
			totcom *= len(dl[d])
		
		res = []
		for t in range(totcom):
			curtok = ''
			for i in range(len(digits)):
				ci = t // comnum[i]
				t  = t %  comnum[i]
				curtok += dl[digits[i]][ci]
			res.append(curtok)

		return res

hey = Solution()
print(hey.letterCombinations('234'))
		