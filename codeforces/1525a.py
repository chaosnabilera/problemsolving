import math

def solve(k):
	e, w = k, 100 - k
	g = math.gcd(e,w)
	e //= g
	w //= g
	return e+w

if __name__ == '__main__':
	T = int(input())
	for t in range(T):
		k = int(input())
		print(solve(k))