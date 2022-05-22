def solve(n, iarr):
	lastodd = None

	for i in range(n):
		if iarr[i] & 1:
			if lastodd != None:
				return f'2\n{lastodd+1} {i+1}'
			else:
				lastodd = i
		else:
			return f'1\n{i+1}'

	return '-1'



if __name__ == '__main__':
	T = int(input())
	for t in range(T):
		n = int(input())
		iarr = list(map(int,input().split()))
		print(solve(n,iarr))