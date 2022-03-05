def alternating(vals, m):
	ans = []
	for i in range(m):
		ans.append(vals[i%len(vals)])
	return ans

def solve(n,m,mat):
	if mat[0][1] == mat[1][0]:
		print('YES')
		print(' '.join(alternating(['1','2'], m+1)))
	elif m & 1 == 1:
		print('YES')
		print(' '.join(alternating(['1','2'], m+1)))
	else:
		if n == 2:
			print('NO')
		else:
			if mat[1][2] == mat[2][1]:
				print('YES')
				print(' '.join(alternating(['2','3'], m+1)))
			elif mat[0][2] == mat[2][0]:
				print('YES')
				print(' '.join(alternating(['1','3'], m+1)))
			elif mat[0][1] == mat[1][2] == mat[2][0]:
				print('YES')
				print(' '.join(alternating(['1','2','3'], m+1)))
			elif mat[0][1] == mat[2][1] == mat[1][0]:
				print('YES')
				print(' '.join(alternating(['1','3','2'], m+1)))
			else:
				if mat[0][1] != mat[0][2]:
					center, neigh = '1', ['2','3']
				elif mat[1][0] != mat[1][2]:
					center, neigh = '2', ['1','3']
				else:
					center, neigh = '3', ['1','2']

				ans = []

				if (m//2) & 1 == 0:
					ans += alternating([center,neigh[0]], (m//2)+1)
					ans += alternating([neigh[1],center], (m//2))
				else:
					ans += alternating([neigh[0],center], (m//2)+1)
					ans += alternating([neigh[1],center], (m//2))
				
				print('YES')
				print(' '.join(ans))

if __name__ == '__main__':
	T = int(input())
	for t in range(T):
		n,m = tuple(map(int,input().split()))
		mat = [input() for _ in range(n)]
		solve(n,m,mat)