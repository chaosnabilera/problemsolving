class LLNode:
	def __init__(self, val):
		self.val = val
		self.prev = None
		self.next = None

def solve(N,B):
	if N == 1:
		return 'YES'

	neginf = LLNode(-float('inf'))
	median = LLNode(B[0])
	posinf = LLNode(float('inf'))

	neginf.next = median
	median.prev = neginf
	median.next = posinf
	posinf.prev = median

	for i in range(1,N):
		# print(B[i])

		if B[i] > median.next.val:
			# print(B[i],median.next.val)
			return 'NO'
		if B[i] < median.prev.val:
			# print(B[i],median.prev.val)
			return 'NO'

		if B[i] < median.val:
			if B[i] > median.prev.val:
				newmed = LLNode(B[i])
				prev = median.prev
				prev.next = newmed
				newmed.prev = prev
				newmed.next = median
				median.prev = newmed
				median = newmed
			else:
				median = median.prev
		elif B[i] > median.val:
			if B[i] < median.next.val:
				newmed = LLNode(B[i])
				nextn = median.next
				nextn.prev = newmed
				newmed.next = nextn
				newmed.prev = median
				median.next = newmed
				median = newmed
			else:
				median = median.next

	return 'YES'

if __name__ == '__main__':
	T = int(input())
	for t in range(T):
		N = int(input())
		B = list(map(int,input().split()))
		print(solve(N,B))