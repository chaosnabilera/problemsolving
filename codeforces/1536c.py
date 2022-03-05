from collections import defaultdict
import math

def solve(N,S):
	ans = []
	cnt = {'D':0, 'K':0}
	ratio_cnt = defaultdict(int)

	for i in range(N):
		cnt[S[i]] += 1
		d = cnt['D']
		k = cnt['K']

		g = math.gcd(d,k)
		d //= g
		k //= g

		ratio_cnt[(d,k)] += 1
		ans.append(ratio_cnt[(d,k)])

	print(' '.join(map(str,ans)))

if __name__ == '__main__':
	T = int(input())
	for t in range(T):
		N = int(input())
		S = input()
		solve(N,S)