def bogosort(n,arr):
	arr.sort(reverse=True)
	return ' '.join(map(str,arr))

if __name__ == '__main__':
	T = int(input())
	for t in range(T):
		n = int(input())
		arr = list(map(int,input().split()))
		print(bogosort(n,arr))