def solve(N,X):
	# print(N,X)
	cnt = 0
	for i in range(1,N):
		icur = int(X[i])
		iprev= int(X[i-1])

		if icur > iprev:
			continue

		if icur == iprev:
			X[i] += '0'
			cnt += 1
			continue

		if len(X[i]) == len(X[i-1]):
			X[i] += '0'
			cnt += 1
			continue

		iprefix = int(X[i-1][:len(X[i])])
		if icur > iprefix:
			numadd = (len(X[i-1])-len(X[i]))
			X[i] += '0'*numadd
			cnt += numadd
		elif icur < iprefix:
			numadd = (len(X[i-1])-len(X[i])+1)
			X[i] += '0'*numadd
			cnt += numadd
		else:
			spostfix = X[i-1][len(X[i]):]
			ipostfix = int(spostfix)

			if len(str(ipostfix+1)) > len(spostfix):
				numadd = (len(X[i-1])-len(X[i])+1)
				X[i] += '0'*numadd
				cnt += numadd
			else:
				nextnum = ipostfix+1
				formatted = '0'*(len(spostfix)-len(str(nextnum))) + str(nextnum)
				numadd = len(formatted)
				X[i] += formatted
				cnt += numadd
	return cnt



if __name__ == '__main__':
	T = int(input())
	for t in range(T):
		N = int(input())
		X = input().strip().split()
		res = solve(N,X)
		print(f'Case #{t+1}: {res}')