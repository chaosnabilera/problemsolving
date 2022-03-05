if __name__ == '__main__':
	T = int(input())
	for t in range(T):
		n,m = tuple(map(int,input().split()))
		iarr = tuple(map(int,input().split()))
		print(min(m,sum(iarr)))