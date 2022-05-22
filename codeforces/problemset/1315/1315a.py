def solve(a,b,x,y):
	area1 = a*y
	area2 = a*(b-y-1)
	area3 = b*x
	area4 = b*(a-x-1)
	return max(area1,area2,area3,area4)

if __name__ == '__main__':
	T = int(input())
	for t in range(T):
		a,b,x,y = tuple(map(int,input().split()))
		print(solve(a,b,x,y))