from collections import defaultdict, Counter

def solve(a,b,c):
	n,m = len(a),len(c)
	diffdict = defaultdict(list)
	already = {}

	for i in range(n):
		if a[i] != b[i]:
			diffdict[b[i]].append(i)
		else:
			if a[i] not in already:
				already[a[i]] = i

	colcnt = Counter(c)
	for k in diffdict:
		if len(diffdict[k]) > colcnt[k]:
			return 'NO'

	unnecessary = []
	ans = [0]*m

	#print(diffdict)
	for i,col in enumerate(c):
		if col in diffdict:
			if len(diffdict[col]) > 1:
				curpos = diffdict[col][0]
				diffdict[col] = diffdict[col][1:]
			else:
				curpos = diffdict[col][0]
			while unnecessary:
				ans[unnecessary.pop()] = curpos
			ans[i] = curpos

		elif col in already:
			while unnecessary:
				ans[unnecessary.pop()] = already[col]
			ans[i] = already[col]
		else:
			unnecessary.append(i)

	if len(unnecessary) != 0:
		return 'NO'

	return 'YES\n'+' '.join(map(lambda e:str(e+1),ans))

if __name__ == '__main__':
	T = int(input())
	for t in range(T):
		n,m = tuple(map(int,input().split()))
		a = list(map(int,input().split()))
		b = list(map(int,input().split()))
		c = list(map(int,input().split()))
		print(solve(a,b,c))
