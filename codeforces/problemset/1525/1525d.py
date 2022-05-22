def solve(N, iarr):
	x = []
	for i,v in enumerate(iarr):
		if v == 1:
			x.append(i)

	K = len(x)
	if K == 0:
		return 0
		
	dp = [[float('inf')]*(K) for _ in range(N)]

	if iarr[0] == 0:
		dp[0][0] = abs(x[0]-0)

	for n in range(1,N):
		if iarr[n] == 0:
			dp[n][0] = min(dp[n-1][0], abs(x[0]-n))
		else:
			dp[n][0] = dp[n-1][0]

	# for row in dp:
	# 	print(dp)

	# print()

	for k in range(1,K):
		for n in range(k,N):
			if iarr[n] == 0:
				dp[n][k] = min(dp[n-1][k], dp[n-1][k-1] + abs(x[k]-n))
			else:
				dp[n][k] = dp[n-1][k]

	# for k in range(K):
	# 	for n in range(N):
	# 		print("{:10}".format(dp[n][k]),end=' ')
	# 	print()

	return dp[N-1][K-1]


if __name__ == '__main__':
	N = int(input())
	iarr = list(map(int,input().split()))
	print(solve(N,iarr))