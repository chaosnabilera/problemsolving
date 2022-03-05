def solve(k,h):
	N = len(h)
	cur = 0

	while k > 0:
		cur = N
		for i in range(1,N):
			if h[i-1] < h[i]:
				cur = i-1
				break
		if cur == N:
			break

		k -= 1
		h[cur] += 1

	if cur == N:
		return -1
	else:
		return cur+1


if __name__ == '__main__':
	T = int(input())
	for t in range(T):
		n,k = map(int,input().split())
		h = list(map(int,input().split()))
		print(solve(k,h))