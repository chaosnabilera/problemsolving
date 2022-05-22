def solve(a,b,c):
	N,M = len(a), len(c)
	demand = {}  # indices that needs to change to certain color
	same = {}    # indices that needs to stay the same
	wait = []
	ans = [0]*M
 
	for i in range(N):
		if a[i] != b[i]:
			if b[i] not in demand:
				demand[b[i]] = []
			demand[b[i]].append(i)
		else:
			if a[i] not in same:
				same[a[i]] = i
 
	for j in range(M):
		color = c[j]
		if color in demand:
			topaint = demand[color].pop()
			if len(demand[color]) == 0:
				del demand[color]
				same[color] = topaint
 
			while wait:
				ans[wait.pop()] = topaint
			ans[j] = topaint
 
		elif color in same:
			topaint = same[color]
			while wait:
				ans[wait.pop()] = topaint
			ans[j] = topaint
 
		else:
			wait.append(j)
 
	if wait or demand:
		print('NO')
	else:
		print('YES')
		print(' '.join(str(v+1) for v in ans))
 
 
if __name__ == '__main__':
	T = int(input())
	for t in range(T):
		n,m = map(int,input().split())
		a = list(map(int, input().split()))
		b = list(map(int, input().split()))
		c = list(map(int, input().split()))
		solve(a,b,c)