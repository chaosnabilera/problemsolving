def solve(n, iarr):
	maxh = max(iarr)
	for e in iarr:
		if (maxh-e) & 1:
			return 'NO'

	return 'YES'

if __name__ == '__main__':
	T = int(input())
	for t in range(T):
		n = int(input())
		iarr = list(map(int,input().split()))
		print(solve(n,iarr))