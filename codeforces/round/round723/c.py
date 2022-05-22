import heapq

def solve(n,arr):
	neg = []
	score = 0

	i = 0
	poscnt = 0
	for i in range(n):
		if arr[i] >= 0:
			score += arr[i]
			poscnt += 1
		else:
			if score + arr[i] >= 0:
				heapq.heappush(neg, arr[i])
				score += arr[i]
			else:
				if neg and neg[0] < arr[i]:
					score += abs(heapq.heappop(neg))
					heapq.heappush(neg, arr[i])
					score += arr[i]

	return poscnt + len(neg)

if __name__ == '__main__':
	n = int(input())
	arr = list(map(int,input().split()))
	print(solve(n,arr))