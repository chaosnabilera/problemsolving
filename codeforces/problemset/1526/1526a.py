def solve(N,A):
	A.sort()
	ans = []
	for i in range(N):
		ans.append(A[i])
		ans.append(A[i+N])
	print(' '.join(map(str,ans)))

if __name__ == '__main__':
	T = int(input())
	for t in range(T):
		N = int(input())
		A = list(map(int,input().split()))
		solve(N,A)