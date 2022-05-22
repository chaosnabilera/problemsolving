if __name__ == '__main__':
	T = int(input())
	for t in range(T):
		A,B = tuple(map(int,input().split()))
		if B == 1:
			print('NO')
		else:
			if B == 2:
				x = A
				y = 3*A
				z = x+y
			else:
				x = A
				y = A*(B-1)
				z = x+y
			print('YES')
			print(x,y,z)
