import math

def lcm(a,b):
	gcd = math.gcd(a,b)
	return (a*b)//gcd

def solve(x):
	# for a in range(1,x+1):
	# 	for b in range(a,x+1):
	# 		if math.gcd(a,b)+lcm(a,b) == x:
	# 			return '{} {}'.format(a,b)
	return '1 {}'.format(x-1)

if __name__ == '__main__':
	T = int(input())
	for t in range(T):
		print(solve(int(input())))