def solve(a,b,c):
	slist = [a,b,c]
	slist.sort()
	a,b,c = slist
	mlist = [(0,0,1),(0,1,0),(1,0,0),(0,1,1),(1,0,1),(1,1,0),(1,1,1)]
	cnt = 0

	for da,db,dc in mlist:
		if a>=da and b>=db and c>=dc:
			a -= da
			b -= db
			c -= dc
			cnt += 1

	return cnt

if __name__ == '__main__':
	T = int(input())
	for t in range(T):
		a,b,c = tuple(map(int,input().split()))
		print(solve(a,b,c))