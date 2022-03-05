def solve(N,A):
	minval, mini = A[0],0
	for i in range(1,N):
		if A[i] < minval:
			minval = A[i]
			mini = i

	ans = []
	if mini != 0:
		ans.append([0,mini,minval,A[0]])

	for i in range(1,N):
		if A[i] != minval+i:
			ans.append([0,i,minval,minval+i])

	print(len(ans))
	for i,j,x,y in ans:
		print(i+1,j+1,x,y)

if __name__ == '__main__':
	T = int(input())
	for t in range(T):
		N = int(input())
		A = list(map(int,input().split()))
		solve(N,A)