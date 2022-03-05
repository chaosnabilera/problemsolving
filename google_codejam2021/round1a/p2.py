# brute force
def solve(cards):
	N = len(cards)
	maxval = 0
	for i in range(1<<N):
		pmult = 1
		psum = 0
		for j in range(len(cards)):
			if (1<<j) & i:
				psum += cards[j]
			else:
				pmult *= cards[j]
		if psum == pmult:
			maxval = max(maxval, psum)
	return maxval

if __name__ == '__main__':
	T = int(input())
	for t in range(T):
		M = int(input())
		cards = []
		for m in range(M):
			P,N = tuple(map(int,input().split()))
			for n in range(N):
				cards.append(P)
		res = solve(cards)
		print(f'Case #{t+1}: {res}')
