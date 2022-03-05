def solve(A,B):
	if B == 1:
		print('NO')
		return

	if B == 2:
		x,y = A, 3*A
		z = x+y
	else:
		x = A
		y = (B-1)*A
		z = x+y 

	print('YES')
	print(x,y,z)


if __name__ == '__main__':
	T = int(input())
	for t in range(T):
		A,B = tuple(map(int,input().split()))
		solve(A,B)