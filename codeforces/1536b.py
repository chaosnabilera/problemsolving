def solve(N,S,alist):
	slist = []
	for c in S:
		slist.append(c)
	for i in range(N-1):
		slist.append(S[i:i+2])
	for i in range(N-2):
		slist.append(S[i:i+3])

	sset = set(slist)

	for ans in alist:
		if ans not in sset:
			return ans

def create_alist():
	A = 'abcdefghijklmnopqrstuvwxyz'
	alist = []

	for a in A:
		alist.append(a)
	for a1 in A:
		for a2 in A:
			alist.append(a1+a2)
	for a1 in A:
		for a2 in A:
			for a3 in A:
				alist.append(a1+a2+a3)

	return alist


if __name__ == '__main__':
	T = int(input())
	alist = create_alist()
	for t in range(T):
		N = int(input())
		S = input()
		print(solve(N,S,alist))