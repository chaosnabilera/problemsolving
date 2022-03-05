import random

def solve(N,C):
	if (C < N-1) or (C > ( (N*(N+1)) >> 1 )-1):
		return 'IMPOSSIBLE'

	arr = [-1] * N

	right = N-1
	left = 0
	curturn = 'R'
	n = 1

	while C > 0:
		#print(arr, C)
		if C == right-left:
			if curturn == 'R':
				for i in range(left,right+1):
					arr[i] = n
					n += 1
			else:
				for i in range(right, left-1, -1):
					arr[i] = n
					n += 1
			C = 0
		else:
			if C - (right-left+1) >= (right-left-1):
				C -= (right-left+1)
				if curturn == 'R':
					arr[right] = n
					right -= 1
					curturn = 'L'
				else:
					arr[left] = n
					left += 1
					curturn = 'R'
				n += 1
			else:
				if curturn == 'R':
					pivot = left + (C - (right-left))
					for i in range(pivot, left-1, -1):
						arr[i] = n
						n += 1
					for i in range(pivot+1,right+1):
						arr[i] = n
						n += 1
				else:
					pivot = right - (C - (right-left))
					for i in range(pivot, right+1):
						arr[i] = n
						n += 1
					for i in range(pivot-1, left-1, -1):
						arr[i] = n
						n += 1
				C = 0

	if right == left and arr[right] == -1:
		arr[right] = n

	return arr


def getcost(N, iarr):
	cost = 0
	for i in range(N-1):
		minidx = i
		for j in range(i+1,N):
			if iarr[j] < iarr[minidx]:
				minidx, minval = j, iarr[j]
		iarr = iarr[:i] + iarr[i:minidx+1][::-1] + iarr[minidx+1:]
		cost += minidx-i+1
	return cost


def test():
	cnt = 0
	while cnt < 100:
		N = random.randint(2,100)
		C = random.randint(1,1000)
		rarr = solve(N,C)
		if rarr != 'IMPOSSIBLE':
			cnt += 1
			if getcost(N,rarr) != C:
				print(N,C,'Wrong answer')

if __name__ == '__main__':
	T = int(input())
	for t in range(T):
		N,C = tuple(map(int,input().split()))
		rarr = solve(N,C)
		if rarr == 'IMPOSSIBLE':
			print('Case #{}: IMPOSSIBLE'.format(t+1))
		else:
			print('Case #{}: {}'.format(t+1, ' '.join(map(str,rarr))))

		# if rarr != 'IMPOSSIBLE':
		# 	print('comparison: {} / {}'.format(getcost(N,rarr),C))