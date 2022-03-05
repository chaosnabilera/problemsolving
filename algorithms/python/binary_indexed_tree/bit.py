import random

class fenwick:
	def __init__(self, iarr):
		self.varr = [0] * (len(iarr)+1)
		self.farr = [0] * (len(iarr)+1)
		for i in range(1,len(iarr)+1):
			self.update(i, iarr[i-1])

	def update(self, i, val):
		delta = val - self.varr[i];
		self.varr[i] = val

		idx = i
		#print('i:{}'.format(i))
		while idx < len(self.farr):
			#print('idx:{}'.format(idx))
			self.farr[idx] += delta
			lsb = idx - (idx & (idx-1))
			idx += lsb

	def sum(self, i, j):
		if i == 1:
			return self._sum(j)
		else:
			return self._sum(j) - self._sum(i-1)

	def _sum(self, i):
		idx = i
		result = 0
		while idx:
			result += self.farr[idx]
			idx &= (idx-1)
		return result

#rarr = [i for i in range(1,11)]
rarr = [random.randint(-1000,1000) for i in range(1,1001)]

fw = fenwick(rarr)

for i in range(len(rarr)-2):
	for j in range(i+1, len(rarr)):
		I, J = i+1, j+1
		fr = fw.sum(I,J)
		pr = sum(rarr[i:j+1])

		if fr != pr:
			print(i,j,pr,I,J,fr,rarr[i:j+1])
			print("fuck!")
			exit()

print("good")