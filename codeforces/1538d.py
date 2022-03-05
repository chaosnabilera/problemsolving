import math
from collections import defaultdict

def calculate_prime_numbers(max_num):
	isprime = [True]*(max_num+1)

	isprime[0] = False
	isprime[1] = False

	for i in range(2,max_num+1):
		if not isprime[i]:
			continue
		for j in range(i*i,max_num+1,i):
			isprime[j] = False

	return list(filter(lambda i:isprime[i], range(max_num)))


def factorize(X,prime_list):
	i = 0
	factors = defaultdict(int)
	while i < len(prime_list) and X >= prime_list[i]:
		if X % prime_list[i] == 0:
			factors[prime_list[i]] += 1
			X = X // prime_list[i]
		else:
			i += 1

	if X != 1:
		factors[X] += 1

	return factors

# A <= B
def solve(A,B,K,prime_list):
	if B < A:
		A,B = B,A
	if K == 1:
		return 'YES' if B > A and B % A == 0 else 'NO'

	ab_gcd = math.gcd(A,B)

	a_div_gcd = A // ab_gcd
	b_div_gcd = B // ab_gcd

	adg_factor = factorize(a_div_gcd, prime_list)
	bdg_factor = factorize(b_div_gcd, prime_list)
	g_factor   = factorize(ab_gcd, prime_list)

	if sum(adg_factor.values()) + sum(bdg_factor.values()) + (2*sum(g_factor.values())) >= K:
		return 'YES'
	else:
		return 'NO'


if __name__ == '__main__':
	maxK = 10**9
	prime_list = calculate_prime_numbers(int(maxK**0.5)+1)

	T = int(input())
	for t in range(T):
		A,B,K = tuple(map(int,input().split()))
		print(solve(A,B,K,prime_list))