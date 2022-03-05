from typing import List

def recSolve(cstr, no, nc, res):
	if no == 0 and nc == 0:
		res.append(cstr)
	if no > 0:
		recSolve(cstr+'(',no-1,nc,res)
	if nc > no:
		recSolve(cstr+')',no,nc-1,res)

class Solution:
	def generateParenthesis(self, n: int) -> List[str]:
		res = []
		cstr = '('
		no, nc = n-1, n

		recSolve(cstr,no,nc,res)

		return res

hey = Solution()
print(hey.generateParenthesis(3))