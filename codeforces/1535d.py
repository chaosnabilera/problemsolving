K,S,Q = None,None,None
LIMIT = None
CNTTREE = None
LtS = None
StL = None

def solve(p,c):
	global S,CNTTREE

	si = p-1
	S[si] = c

	li = StL[si]
	while li > 0:
		si = LtS[li]
		if li >= (LIMIT >> 1):
			CNTTREE[li] = 2 if S[si] == '?' else 1
		else:
			if S[si] == '0':
				CNTTREE[li] = CNTTREE[li*2]
			elif S[si] == '1':
				CNTTREE[li] = CNTTREE[li*2+1]
			else:
				CNTTREE[li] = CNTTREE[li*2] + CNTTREE[li*2+1]
		li >>= 1

	# print(S,CNTTREE)
	print(CNTTREE[1])


if __name__ == '__main__':
	K = int(input())
	S = list(input())
	Q = int(input())

	LIMIT = 2**K
	CNTTREE = [0]*LIMIT

	LtS = [None]*LIMIT
	StL = [None]*LIMIT

	# compute idx transitions
	lv_beg = 1
	lv_end = 2
	li = 1
	while lv_beg < LIMIT:
		li = lv_beg
		s_beg = LIMIT-lv_end
		s_end = LIMIT-lv_beg

		for i in range(lv_end-lv_beg):
			li = lv_beg+i
			si = s_beg+i
			LtS[li] = si
			StL[si] = li

		lv_beg, lv_end = lv_end, lv_end << 1

	# print(f'LtS: {LtS}')
	# print(f'StL: {StL}')

	leaf_start = LIMIT >> 1
	for li in range(leaf_start,LIMIT):
		si = LtS[li]
		CNTTREE[li] = 2 if S[si] == '?' else 1

	curlv_start = leaf_start >> 1
	curlv_end = leaf_start
	while curlv_start > 0:
		for li in range(curlv_start, curlv_end):
			si = LtS[li]
			if S[si] == '0':
				CNTTREE[li] = CNTTREE[li*2]
			elif S[si] == '1':
				CNTTREE[li] = CNTTREE[li*2+1]
			else:
				CNTTREE[li] = CNTTREE[li*2]+CNTTREE[li*2+1]
		curlv_start, curlv_end = curlv_start >> 1, curlv_start

	# print(S,CNTTREE)

	for q in range(Q):
		p,c = input().split()
		p = int(p)
		solve(p,c)