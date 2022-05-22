def tworegularpolygons(n,m):
	return 'YES' if (n % m == 0) else 'NO'

if __name__ == '__main__':
	T = int(input())
	for t in range(T):
		n,m = tuple(map(int,input().split()))
		print(tworegularpolygons(n,m))