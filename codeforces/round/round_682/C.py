def makeEven(num):
	if num & 1 == 1:
		num += 1
	return num

def makeOdd(num):
	if num & 1 == 0:
		num += 1
	return num

if __name__ == '__main__':
	t = int(input())
	for i in range(t):
		n,m = tuple(map(int, input().split()))
		mat = [list(map(int,input().split())) for i in range(n)]
		for i in range(n):
			if i&1 == 0:
				for j in range(m):
					if j & 1 == 0:
						mat[i][j] = makeEven(mat[i][j])
					else:
						mat[i][j] = makeOdd(mat[i][j])
			else:
				for j in range(m):
					if j & 1 == 0:
						mat[i][j] = makeOdd(mat[i][j])
					else:
						mat[i][j] = makeEven(mat[i][j])
		for r in range(n):
			print(' '.join([str(c) for c in mat[r]]))