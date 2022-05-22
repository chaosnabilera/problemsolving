import math

def solve(N,A):
	even = list(filter(lambda a:a&1==0, A))
	odd = list(filter(lambda a:a&1==1, A))

	even.sort()
	odd.sort()

	SA = even+odd
	cnt = 0
	for i in range(N-1):
		for j in range(i+1,N):
			if math.gcd(SA[i],2*SA[j]) > 1:
				cnt += 1

	print(cnt)

if __name__ == '__main__':
	T = int(input())
	for t in range(T):
		N = int(input())
		A = list(map(int,input().split()))
		solve(N,A)