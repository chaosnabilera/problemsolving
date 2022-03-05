def solve(n,k,h):
	i = 0

	if n == 1:
		return -1

	while k > 0 and i < n-1:
		if h[i] >= h[i+1]:
			i += 1
			continue

		# now h[i+1] > h[i]
		if i == 0:
			a = h[1]-h[0]
			h[0] += a
			k -= a
		else:
			if h[i-1] == h[i]:
				h[i] += 1
				k -= 1
				if k == 0:
					return i+1
				i -= 1
			else:
				a = min(h[i-1]-h[i],h[i+1]-h[i])
				h[i] += a
				k -= a

	if k > 0:
		return -1
	else:
		return i+1


if __name__ == '__main__':
	T = int(input())
	for t in range(T):
		n,k = tuple(map(int,input().split()))
		h = list(map(int,input().split()))
		print(solve(n,k,h))