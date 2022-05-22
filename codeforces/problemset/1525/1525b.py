def solve(n, arr):
	for i in range(1,n):
		if arr[i] < arr[i-1]:
			break
	else:
		return 0

	if arr[0] == 1 or arr[-1] == n:
		return 1

	if arr[0] == n and arr[-1] == 1:
		return 3
	else:
		return 2

if __name__ == '__main__':
	T = int(input())
	for t in range(T):
		n = int(input())
		arr = list(map(int,input().split()))
		print(solve(n,arr))