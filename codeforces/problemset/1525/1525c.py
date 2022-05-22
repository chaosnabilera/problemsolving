from collections import deque

def solve(n,m,xarr,darr):
	oddarr = []
	evenarr = []
	for i in range(n):
		if xarr[i] & 1:
			oddarr.append((xarr[i],darr[i],i))
		else:
			evenarr.append((xarr[i],darr[i],i))

	ans = [-1] * n
	rodd = partsolve(oddarr, m)
	for k in rodd:
		ans[k] = rodd[k]
	reven = partsolve(evenarr,m)
	for k in reven:
		ans[k] = reven[k]

	return ' '.join(map(str,ans))

def partsolve(arr, m):
	res = {}
	arr.sort(key=lambda e:e[0])
	Ldeq, Rdeq = deque([]),deque([])

	for x,d,i in arr:
		if d == 'L':
			Ldeq.append((x,d,i))
		else:
			Rdeq.append((x,d,i))

		if Ldeq and Rdeq and Ldeq[-1][0] > Rdeq[-1][0]:
			lx,ld,li = Ldeq.pop()
			rx,rd,ri = Rdeq.pop()
			tm = (lx - rx) >> 1
			res[li] = tm
			res[ri] = tm

	while len(Ldeq) > 1:
		x1,d1,i1 = Ldeq.popleft()
		x2,d2,i2 = Ldeq.popleft()
		tm = x1 + ((x2-x1) >> 1)
		res[i1] = tm
		res[i2] = tm

	while len(Rdeq) > 1:
		x1,d1,i1 = Rdeq.pop()
		x2,d2,i2 = Rdeq.pop()
		tm = (m-x1) + ((x1-x2) >> 1)
		res[i1] = tm
		res[i2] = tm

	if Ldeq and Rdeq:
		xl,dl,il = Ldeq.popleft()
		xr,dr,ir = Rdeq.pop()

		a,b = xl, (m-xr)
		if b < a:
			a,b = b,a

		tm = (m+a+b) >> 1
		res[il] = tm
		res[ir] = tm

	return res

if __name__ == '__main__':
	T = int(input())
	for t in range(T):
		n,m = tuple(map(int,input().split()))
		xarr = list(map(int,input().split()))
		darr = input().split()

		print(solve(n,m,xarr,darr))