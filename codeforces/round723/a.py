def solve(n,iarr):
	iarr.sort()
	ans = []
	for i in range(n):
		ans.append(str(iarr[i]))
		ans.append(str(iarr[n+i]))
	return ' '.join(ans)

if __name__ == '__main__':
	T = int(input())
	for t in range(T):
		n = int(input())
		iarr = list(map(int,input().split()))
		print(solve(n,iarr))