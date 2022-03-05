def solve(a,b):
	ans = 0
	for i in range(30):
		cur = (1<<i)
		if cur & a and cur & b:
			ans |= cur
	return (a^ans) + (b^ans)


if __name__ == '__main__':
	T = int(input())
	for t in range(T):
		a,b = tuple(map(int,input().split()))
		print(solve(a,b))