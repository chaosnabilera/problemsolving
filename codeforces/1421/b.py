def solve(N,iarr):
	s = iarr[0][1]+iarr[1][0]
	f = iarr[N-1][N-2]+iarr[N-2][N-1]

	ans = []
	if s in ['00','11']:
		sc = s[0]
		if f[0] == sc:
			ans.append((N-1,N-2))
		if f[1] == sc:
			ans.append((N-2,N-1))
	else:
		if f in ['00','11']:
			fc = f[0]
			if s[0] == fc:
				ans.append((0,1))
			if s[1] == fc:
				ans.append((1,0))
		else: # make s 00 and f 11
			if s[0] == '1':
				ans.append((0,1))
			if s[1] == '1':
				ans.append((1,0))
			if f[0] == '0':
				ans.append((N-1,N-2))
			if f[1] == '0':
				ans.append((N-2,N-1))

	print(len(ans))
	for r,c in ans:
		print(r+1,c+1)

if __name__ == '__main__':
	T = int(input())
	for t in range(T):
		N = int(input())
		iarr = []
		for n in range(N):
			iarr.append(input().strip())
		solve(N,iarr)