POWER_OF_2 = [2**i for i in range(32)]

def solve(N):
	if N & 1 == 1:
		return 'Bob'

	for i in range(32):
		if POWER_OF_2[i] == N:
			if i & 1 == 1:
				return 'Bob'
			else:
				return 'Alice'

	return 'Alice'


if __name__ == '__main__':
	T = int(input())
	for t in range(T):
		N = int(input())
		print(solve(N))