import random

def solve(x):
	if x < 11:
		return 'NO'
	if x % 11 == 0:
		return 'YES'
	if x < 111:
		return 'NO'
	if x % 111 == 0:
		return 'YES'

	div = x // 111
	mod = x % 111

	if mod % 11 == 0:
		return 'YES'

	min_necessary = 0xFFFFFFFF
	for i in range(1,11):
		if (i*11) - mod >= 0:
			min_necessary = min(min_necessary, (i*11)-mod)

	if div >= min_necessary:
		return 'YES'

	return 'NO'


if __name__ == '__main__':
	T = int(input())
	for t in range(T):
		x = int(input())
		print(solve(x))

# if __name__ == '__main__':
# 	ones = [int('1'*i) for i in range(2,9)]
# 	for t in range(10000):
# 		s = 0
# 		aa = []
# 		for o in ones:
# 			a = random.randint(0,100)
# 			s += a*o
# 			aa.append((a,o))
# 		if solve(s) == 'NO':
# 			print(s)
# 			print(aa)