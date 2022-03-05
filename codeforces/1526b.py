def solve(X):
	div_11, mod_11 = X//11, X%11
	if (div_11 // 10) >= mod_11:
		print('YES')
	else:
		print('NO')

if __name__ == '__main__':
	T = int(input())
	for t in range(T):
		X = int(input())
		solve(X)