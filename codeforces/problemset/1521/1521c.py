import sys

def solve(N):
	ans = [0]*N

	N_even = N if (N&1) == 0 else N-1
	i0 = None
	for i in range(0,N_even,2):
		print(f'? 2 {i+(1)} {i+1+(1)} 1')
		sys.stdout.flush()
		r1 = int(input())

		if r1 == 1:
			i0 = i
			break
		elif r1 == 2:
			print(f'? 2 {i+1+(1)} {i+(1)} 1')
			sys.stdout.flush()
			r2 = int(input())
			if r2 == 1:
				i0 = i+1
				break

	if i0 == None:
		i0 = N-1

	ans[i0] = 1
	for i in range(N):
		if i == i0:
			continue
		print(f'? 1 {i0+(1)} {i+(1)} {N-1}')
		sys.stdout.flush()
		ans[i] = int(input())

	print("! "+" ".join(map(str,ans)))
	sys.stdout.flush()


if __name__ == '__main__':
	T = int(input())
	for t in range(T):
		N = int(input())
		solve(N)