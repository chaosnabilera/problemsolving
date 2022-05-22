import heapq

def solve(N,A):
	minheap = []
	health = 0

	for v in A:
		if health + v >= 0:
			heapq.heappush(minheap, v)
			health += v
		else:
			if minheap and minheap[0] < v:
				health -= heapq.heappop(minheap)
				heapq.heappush(minheap,v)
				health += v

	print(len(minheap))

if __name__ == '__main__':
	N = int(input())
	A = list(map(int,input().split()))
	solve(N,A)