import sys

def binarysearch(arr, beg, end, v):
	while True:
		if beg == end:
			if end == len(arr)-1:
				# beg = end-1
				return arr + [v]
			else:
				end = beg+1

		if beg + 1 == end:
			print(arr[beg],arr[end],v)
			mv = int(input())
			if mv == arr[beg]:
				return [v] + arr
			elif mv == v:
				return arr[:beg+1] + [v] + arr[end:]
			else:
				return arr[:end+1] + [v] + arr[end+1:]
			break

		mp = (beg+end) >> 1
		print(arr[mp],arr[mp+1],v)
		mv = int(input())

		if mv == v:
			return arr[:mp+1] + [v] + arr[mp+1:]
		elif mv == arr[mp]:
			end = mp-1
		elif mv == arr[mp+1]:
			beg = mp+1

def solve(N,Q):
	# initial request
	arr = [1,2,3]
	print(1,2,3)
	med = int(input())
	arr[1],arr[med-1] = arr[med-1],arr[1]

	for i in range(4,N+1):
		mp = len(arr) >> 1
		print(arr[mp],arr[mp+1],i)
		mv = int(input())

		if mv == i: # most happy case
			arr = arr[:mp+1] + [i] + arr[mp+1:]
		elif mv == arr[mp]: # binary search left
			arr = binarysearch(arr, 0, mp, i)
		else:
			arr = binarysearch(arr, mp+1, len(arr)-1, i)

	return arr


if __name__ == '__main__':
	T,N,Q = tuple(map(int,input().split()))
	for t in range(T):
		print(' '.join(map(str, solve(N,Q))))
		res = int(input())