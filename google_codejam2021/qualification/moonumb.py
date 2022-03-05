def solve(X,Y,S):
	dpC = [0]*len(S)
	dpJ = [0]*len(S)

	for i in range(len(S)-2,-1,-1):
		dpC[i] = dpC[i+1]
		dpJ[i] = dpJ[i+1]

		if S[i] == '?':
			if S[i+1] == '?':
				dpC[i] = min(dpC[i+1], dpJ[i+1]+X)
				dpJ[i] = min(dpC[i+1]+Y, dpJ[i+1])
			elif S[i+1] == 'C':
				dpC[i] = dpC[i+1]
				dpJ[i] = dpC[i+1] + Y
			elif S[i+1] == 'J':
				dpC[i] = dpJ[i+1] + X
				dpJ[i] = dpJ[i+1]
		else:
			if S[i+1] == '?':
				if S[i] == 'C':
					dpC[i] = min(dpC[i+1], dpJ[i+1]+X)
					dpJ[i] = dpC[i]
				elif S[i] == 'J':
					dpJ[i] = min(dpC[i+1]+Y, dpJ[i+1])
					dpC[i] = dpJ[i]
			else:
				if S[i] == 'C' and S[i+1] == 'J':
					dpC[i] = dpJ[i+1] + X
					dpJ[i] = dpC[i]
				elif S[i] == 'J' and S[i+1] == 'C':
					dpJ[i] = dpC[i+1] + Y
					dpC[i] = dpJ[i]

	# print(dpC)
	# print(dpJ)
	return min(dpC[0],dpJ[0])

def recsolve(X,Y,S):
	if len(S) <= 1:
		return 0

	if S[0] == 'C':
		if S[1] == 'C':
			return recsolve(X,Y,S[1:])
		elif S[1] == 'J':
			return X + recsolve(X,Y,S[1:])
		else:
			cres = recsolve(X,Y,'C'+S[2:])
			jres = recsolve(X,Y,'J'+S[2:])
			return min(cres, X+jres)
	elif S[0] == 'J':
		if S[1] == 'C':
			return Y + recsolve(X,Y,S[1:])
		elif S[1] == 'J':
			return recsolve(X,Y,S[1:])
		else:
			cres = recsolve(X,Y,'C'+S[2:])
			jres = recsolve(X,Y,'J'+S[2:])
			return min(Y+cres, jres)
	else:
		cres = recsolve(X,Y,'C'+S[2:])
		jres = recsolve(X,Y,'J'+S[2:])
		return min(cres, jres)

if __name__ == '__main__':
	T = int(input())
	for t in range(T):
		X,Y,S = input().split()
		X,Y = int(X), int(Y)
		print('Case #{}: {}'.format(t+1, solve(X,Y,S)))
		#print('rec: {}'.format(recsolve(X,Y,S)))