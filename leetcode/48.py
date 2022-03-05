from typing import List

def printMatrix(matrix):
	pformat = '{:4} '*len(matrix)
	for row in matrix:
		print(pformat.format(*row))


class Solution:
	def rotate(self, matrix: List[List[int]]) -> None:
		"""
		Do not return anything, modify matrix in-place instead.
		"""
		D = len(matrix)
		# transpose
		for r in range(D):
			for c in range(r):
				matrix[r][c], matrix[c][r] = matrix[c][r], matrix[r][c]
		# reflection
		for r in range(D):
			for c in range(D//2):
				matrix[r][c], matrix[r][D-c-1] = matrix[r][D-c-1], matrix[r][c]

idat = [[5,1,9,11],[2,4,8,10],[13,3,6,7],[15,14,12,16]]
sol = Solution()
sol.rotate(idat)
printMatrix(idat)