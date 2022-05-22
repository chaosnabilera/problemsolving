def solve(N,K,A):
	tok_size = 1
	ti = 0
	i = 1

	while i < N:
		if A[ti] > A[i]:
			ti = 0
			tok_size = i+1
		elif A[ti] == A[i]:
			ti = (ti+1) % tok_size
		else:
			break
		i += 1

	# while tok_size > 1 and A[tok_size-1] == A[0]:
	# 	tok_size -= 1

	tok = A[:tok_size]

	# print(A)
	# print(tok)

	if len(tok) >= K:
		return tok[:K]
	else:
		d = K // len(tok)
		m = K % len(tok)
		return tok*d + tok[:m]


if __name__ == '__main__':
	N,K = tuple(map(int,input().split()))
	A = input()
	print(solve(N,K,A))