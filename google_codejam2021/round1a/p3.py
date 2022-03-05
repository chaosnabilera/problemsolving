import math

import operator as op
from functools import reduce

def nCr(n, r):
    r = min(r, n-r)
    numer = reduce(op.mul, range(n, n-r, -1), 1)
    denom = reduce(op.mul, range(1, r+1), 1)
    return numer // denom  # or / in Python 2

def solve(iarr):
	while len(iarr) < 3:
		iarr.append(iarr[-1])

	Q = len(iarr[0][0])
	A,B,C = iarr[0][1], iarr[1][1], iarr[2][1]
	qx,qa,qb,qc = [],[],[],[]

	for q in range(Q):
		aa = iarr[0][0][q]
		ab = iarr[1][0][q]
		ac = iarr[2][0][q]

		if aa == ab and ab == ac:
			qx.append((q,aa))
		elif aa == ab and ab != ac:
			qa.append((q,aa))
		elif aa == ac and ab != ac:
			qb.append((q,aa))
		else:
			qc.append((q,ab))

	sum_x, sum_a, sum_b, sum_c = 0,0,0,0
	cnt = 0

	for x in range(len(qx)+1):
		a = A+B-(2*x)-len(qb)-len(qc)
		if (a < 0) or (a & 1) or ((a>>1) > len(qa)):
			continue
		a >>= 1

		b = A+C-(2*x)-len(qa)-len(qc)
		if (b < 0) or (b & 1) or ((b>>1) > len(qb)):
			continue
		b >>= 1

		c = B+C-(2*x)-len(qa)-len(qb)
		if (c < 0) or (c & 1) or ((c>>1) > len(qc)):
			continue
		c >>= 1

		ncr_x = nCr(len(qx),x)
		ncr_a = nCr(len(qa),a)
		ncr_b = nCr(len(qb),b)
		ncr_c = nCr(len(qc),c)

		curcnt = ncr_x*ncr_a*ncr_b*ncr_c

		sum_x += curcnt*x
		sum_a += curcnt*a
		sum_b += curcnt*b
		sum_c += curcnt*c
		cnt += curcnt

	optans = [''] * Q
	optscr = 0

	for sv,qarr in [(sum_x,qx),(sum_a,qa),(sum_b,qb),(sum_c,qc)]:
		if (sv*2) > (len(qarr)*cnt):
			optscr += sv
			for i,tf in qarr:
				optans[i] = tf
		else:
			optscr += (len(qarr)*cnt)-sv
			for i,tf in qarr:
				optans[i] = 'F' if tf == 'T' else 'T'

	optans = ''.join(optans)

	gcdv = math.gcd(optscr, cnt)
	optscr = f'{optscr//gcdv}/{cnt//gcdv}'

	return optans, optscr


if __name__ == '__main__':
	T = int(input())
	for t in range(T):
		N,Q = tuple(map(int,input().split()))
		iarr = []
		for n in range(N):
			ans, scr = input().split()
			iarr.append((ans,int(scr)))

		optans,optscr = solve(iarr)
		print(f'Case #{t+1}: {optans} {optscr}')