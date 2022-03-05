import math

def solve(k):
	g = math.gcd(k,100-k)
	e,w = k//g, (100-k)//g
	return e+w

if __name__ == '__main__':
	T = int(input())
	for t in range(T):
		k = int(input())
		print(solve(k))