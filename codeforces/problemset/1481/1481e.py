def solve(n, arr):
	l = {}
	r = {}
	cnt = {}
	dp = [0]*(n+1)

	for i in range(n):
		c = arr[i]
		if c not in l:
			l[c] = i

	for i in range(n-1,-1,-1):
		c = arr[i]
		if c not in cnt:
			r[c] = i
			cnt[c] = 0
		
		cnt[c] += 1
		dp[i] = dp[i+1]

		if l[c] == i:
			dp[i] = max(dp[i], cnt[c]+dp[r[c]+1])
		else:
			dp[i] = max(dp[i], cnt[c])

	#print(dp)

	return n-dp[0]

if __name__ == '__main__':
	n = int(input())
	arr = list(map(int,input().split()))
	print(solve(n,arr))