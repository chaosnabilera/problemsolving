def solve(S):
	N = len(S)

	qlen = [0]*(N+1)
	for i in range(N-1,-1,-1):
		if S[i] == '?':
			qlen[i] = qlen[i+1]+1

	blen = [0]*N
	blen[N-1] = 1

	for i in range(N-2,-1,-1):
		if S[i] == '?':
			blen[i] = 1+blen[i+1]
		else:
			if S[i+1] == '?':
				if i+qlen[i+1] == N-1:
					blen[i] = 1+blen[i+1]
				else:
					if qlen[i+1] & 1 == 0:
						if S[i+1+qlen[i+1]] != S[i]:
							blen[i] = 1+blen[i+1]
						else:
							blen[i] = 1+qlen[i+1]
					else:
						if S[i+1+qlen[i+1]] == S[i]:
							blen[i] = 1+blen[i+1]
						else:
							blen[i] = 1+qlen[i+1]
			elif S[i+1] != S[i]:
				blen[i] = 1+blen[i+1]
			else:
				blen[i] = 1

	# print(blen)
	print(sum(blen))
			

if __name__ == '__main__':
	T = int(input())
	for t in range(T):
		S = input()
		solve(S)