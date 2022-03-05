import heapq

def solve(n, iarr):
	cmd = []
	for i in range(n-1):
		if iarr[i] < iarr[i+1]:
			cmd.append([i,i+1,iarr[i],iarr[i]+1])
		else: # iarr
			cmd.append([i,i+1,iarr[i]])

if __name__ == '__main__':
	T = int(input())
	for t in range(T):
		n = int(input())
		iarr = list(map(int,input().split()))