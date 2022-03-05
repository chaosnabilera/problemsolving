def mostsignificant

def solve(S,E):
	search = (1<<15)-1
	for i in range(search):
		cur = S
		for j in range(10):
			if (1<<j) & i:
				xor = cur

if __name__ == '__main__':
	T = int(input())
	for t in range(T):
		S,E = tuple(map(int,input().split()))
		ans = solve(S,E)
		print(f'Case #{t+1}: {ans}')
