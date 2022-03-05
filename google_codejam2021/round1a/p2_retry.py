import copy

def solve(cards):
	C = len(cards)
	total_sum = sum(map(lambda e:e[0]*e[1], cards))

	max_possible_sum = total_sum-2
	min_possible_sum = max(total_sum - (499*59), 0)

	for psum in range(max_possible_sum, min_possible_sum, -1):
		curval = psum
		gcnt = 0
		subtract = 0
		for p,n in cards:
			cnt = 0
			while gcnt < 60 and n > cnt and curval % p == 0:
				cnt += 1
				gcnt += 1
				curval //= p
				subtract += p

		# print(psum,curval,cards,factors)
		if curval == 1:
			subtracted_sum = total_sum - subtract
			if subtracted_sum == psum:
				return subtracted_sum

	return 0

if __name__ == '__main__':
	T = int(input())
	for t in range(T):
		M = int(input())
		cards = []
		for m in range(M):
			p,n = tuple(map(int,input().split()))
			cards.append([p,n])
		res = solve(cards)
		print(f'Case #{t+1}: {res}')