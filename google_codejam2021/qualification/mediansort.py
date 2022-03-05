import sys

def binarysearch(arr, beg, end, v):
	while True:
		if beg == end:
			if end == len(arr)-1:
				beg = end-1
			else:
				end = end+1

		if beg + 1 == end:
			print(arr[beg],arr[end],v)
			mv = int(input())
			if mv == arr[beg]:
				return arr[:beg] + [v] + arr[beg:]
			elif mv == v:
				return arr[:end] + [v] + arr[end:]
			else:
				return arr[:end+1] + [v] + arr[end+1:]

		mp = (beg+end) >> 1
		print(arr[beg],arr[mp],v)
		mv = int(input())

		if mv == arr[beg]:
			return arr[:beg] + [v] + arr[beg:]
		elif mv == v:
			beg += 1
			end = mp
			if beg == end:
				return arr[:end] + [v] + arr[end:]
		elif mv == arr[mp]:
			beg = mp+1

def solve(N,Q):
	# initial request
	arr = [1,2,3]
	print(1,2,3)
	med = int(input())
	arr[1],arr[med-1] = arr[med-1],arr[1]

	for i in range(4,N+1):
		mp = len(arr) >> 1
		print(arr[0],arr[mp],i)
		mv = int(input())

		if mv == arr[0]: # most happy case
			arr = [i] + arr
		elif mv == i: # binary search left
			arr = binarysearch(arr, 1, mp, i)
		else:
			arr = binarysearch(arr, mp+1, len(arr)-1, i)

	return arr


if __name__ == '__main__':
	T,N,Q = tuple(map(int,input().split()))
	for t in range(T):
		print(' '.join(map(str, solve(N,Q))))
		res = int(input())