from collections import deque

def solve(n,m,x,d):
	even = []
	odd = []
	for i in range(n):
		if x[i] & 1:
			odd.append((i,x[i],d[i]))
		else:
			even.append((i,x[i],d[i]))

	even_solution = stacksolve(even, m)
	odd_solution = stacksolve(odd, m)

	ans = []
	for i in range(n):
		if i in even_solution:
			ans.append(even_solution[i])
		else:
			ans.append(odd_solution[i])

	return ' '.join(map(str, ans))

def stacksolve(iarr, m):
	rdeque = deque([])
	ldeque = deque([])
	iarr.sort(key=lambda e:e[1])

	#print(iarr)

	ans = {}

	for i,x,d in iarr:
		if d == 'R':
			rdeque.append((i,x,d))
		else:
			if len(rdeque) > 0:
				li,lx,ld = i,x,d
				ri,rx,rd = rdeque.pop()
				t = abs(lx-rx) >> 1
				ans[li] = t
				ans[ri] = t
			else:
				ldeque.append((i,x,d))

	while len(ldeque) >= 2:
		i1,x1,d1 = ldeque.popleft()
		i2,x2,d2 = ldeque.popleft()
		t = x1 + (abs(x2-x1)//2)
		ans[i1] = t
		ans[i2] = t

	while len(rdeque) >= 2:
		i1,x1,d1 = rdeque.pop()
		i2,x2,d2 = rdeque.pop()
		t = (m-x1) + (abs(x1-x2)//2)
		ans[i1] = t
		ans[i2] = t

	if len(ldeque) == 1 and len(rdeque) == 1:
		ir,xr,dr = rdeque.pop()
		il,xl,dl = ldeque.pop()

		xa, xb = xl, m-xr
		minx, maxx = min(xa,xb), max(xa,xb)
		t = minx + ((m+maxx-minx)//2)
		ans[il] = t
		ans[ir] = t

	elif len(ldeque) == 1:
		i,x,d = ldeque.pop()
		ans[i] = -1
	elif len(rdeque) == 1:
		i,x,d = rdeque.pop()
		ans[i] = -1

	return ans

if __name__ == '__main__':
	T = int(input())
	for t in range(T):
		n,m = tuple(map(int, input().split()))
		x = list(map(int,input().split()))
		d = input().split()
		print(solve(n,m,x,d))