from collections import deque

def solve(N,arr):
	arr.sort(reverse=True)
	arr = deque(arr)

	cost = 0
	cnt = 0

	# print(arr)
	while arr:
		if cnt >= arr[-1][0]:
			b,a = arr.pop()
			cnt += a
			cost += a
		else:
			aa = min(arr[0][1], arr[-1][0] - cnt)
			arr[0][1] -= aa
			cnt += aa
			cost += (aa << 1)
			if arr[0][1] == 0:
				arr.popleft()

	return cost

if __name__ == '__main__':
	N = int(input())
	arr = []
	for n in range(N):
		a,b = tuple(map(int,input().split()))
		arr.append([b,a])
	print(solve(N,arr))
