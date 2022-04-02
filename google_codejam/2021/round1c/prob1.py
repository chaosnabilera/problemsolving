import heapq
import math

def solve(N,K,P):
	P = list(set(P))
	P.sort()

	pqueue1 = []
	pqueue2 = []

	heapq.heappush(pqueue1, -(P[0]-1))
	heapq.heappush(pqueue2, -(P[0]-1))
	heapq.heappush(pqueue1, -(K-P[-1]))
	heapq.heappush(pqueue2, -(K-P[-1]))

	for i in range(1,len(P)):
		lenrange = P[i]-P[i-1]-1
		if lenrange & 1:
			# oddcnt = lenrange - (math.ceil(((lenrange-1) >> 1)/2)*2)
			oddcnt = math.ceil(lenrange/2)
			heapq.heappush(pqueue1,-oddcnt)
		else:
			heapq.heappush(pqueue1, -(lenrange>>1))
		heapq.heappush(pqueue2,-lenrange)

	# print(pqueue1)
	# print(pqueue2)

	ans = -pqueue2[0]
	if len(pqueue1) > 1:
		q11 = -heapq.heappop(pqueue1)
		q12 = -heapq.heappop(pqueue1)
		ans = max(ans, q11+q12)

	return ans/K


if __name__ == '__main__':
	T = int(input())
	for t in range(T):
		N,K = tuple(map(int,input().split()))
		P = list(map(int,input().split()))
		ans = solve(N,K,P)
		print(f'Case #{t+1}: {ans}')