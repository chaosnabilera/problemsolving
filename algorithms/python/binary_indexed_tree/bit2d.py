class fenwick2d:
	def __init__(self, iarr):
		if len(iarr) == 0 or len(iarr[0]) == 0:
			return

		self.varr = [[0]*(len(iarr[0])+1) for i in range(len(iarr)+1)]
		self.farr = [[0]*(len(iarr[0])+1) for i in range(len(iarr)+1)]

		self.R = len(self.farr)
		self.C = len(self.farr[0])

		for r in range(len(iarr)):
			for c in range(len(iarr[0])):
				self.update(r, c, iarr[r][c])

	def update(self, r, c, val):
		r,c = r+1,c+1
		delta = val - self.varr[r][c]
		self.varr[r][c] = val
		R,C = self.R, self.C

		row = r
		while row < R:
			col = c
			while col < C:
				self.farr[row][col] += delta
				clsb = col - (col & (col-1))
				col += clsb

			rlsb = row - (row & (row-1))
			row += rlsb

	def sumRegion(self, r1, c1, r2, c2):
		r1,c1,r2,c2 = r1+1,c1+1,r2+1,c2+1
		return self._sum(r2, c2) - self._sum(r2, c1-1) - self._sum(r1-1, c2) + self._sum(r1-1, c1-1)

	def _sum(self, r, c):
		result = 0
		row = r
		while row:
			col = c
			while col:
				result += self.farr[row][col]
				col &= (col-1)
			row &= (row-1)
		return result

def naivesum(arr, r1, c1, r2, c2):
	result = 0
	for r in range(r1, r2+1):
		result += sum(arr[r][c1:c2+1])
	return result


rarr = [
  [3, 0, 1, 4, 2],
  [5, 6, 3, 2, 1],
  [1, 2, 0, 1, 5],
  [4, 1, 0, 1, 7],
  [1, 0, 3, 0, 5]
]

fw2 = fenwick2d(rarr)
print(fw2.sumRegion(2,1,4,3))
fw2.update(3,2,2)
print(fw2.sumRegion(2,1,4,3))
