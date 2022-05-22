def solve(N,A):
	cntneg = 0
	for a in A:
		if a < 0:
			print('NO')
			return

	A = set(A)

	while len(A) <= 300:
		nextA = set([])

		for aa in A:
			nextA.add(aa)
			for ab in A:
				if aa != ab:
					nextA.add(abs(aa-ab))

		if len(nextA) == len(A):
			A = nextA
			break

		A = nextA

	if len(A) > 300:
		print('NO')
	else:
		print('YES')
		print(len(A))
		print(' '.join(map(str,A)))


if __name__ == '__main__':
	T = int(input())
	for t in range(T):
		N = int(input())
		A = list(map(int,input().split()))
		solve(N,A)
	exit(0)