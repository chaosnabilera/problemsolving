def solve(n, iarr):
	consecutive = True
	for i in range(n-1):
		if iarr[i+1] != iarr[i]+1:
			consecutive = False
			break

	if consecutive:
		return 0

	if iarr[0] == 1:
		return 1
	elif iarr[n-1] == n:
		return 1
	else:
		if iarr[0] == n and iarr[n-1] == 1:
			return 3
		else:
			return 2

if __name__ == '__main__':
	T = int(input())
	for t in range(T):
		n = int(input())
		iarr = list(map(int,input().split()))
		print(solve(n,iarr))