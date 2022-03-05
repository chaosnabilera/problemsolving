def to_group(A):
	if A == '0':
		return [0]

	res = []
	cc = '1'
	cnt = 0
	for c in A:
		if c == cc:
			cnt += 1
		else:
			res.append(cnt)
			cc = '1' if cc == '0' else '0'
			cnt = 1
	res.append(cnt)
	return res

def solve(S,E):
	if S == E:
		return 0

	if S == '0':
		S = '1'
		minval_delta = 1
	else:
		minval_delta = 0

	sarr,earr = to_group(S), to_group(E)
	slen, elen = len(sarr), len(earr)
	minval = 0xFFFFFFFF

	for s in range(slen+1):
		# s_prefix : not matched with e, s_suffix: matched with e
		s_prefix_len, s_suffix_len = s, slen-s
		# e_prefix: matched with s, e_suffix: not matched with s
		e_prefix_len, e_suffix_len = s_suffix_len, elen-s_suffix_len

		if e_suffix_len < 0:
			continue
		if s_prefix_len < e_suffix_len:
			continue

		part1_match = True
		for i in range(e_prefix_len-1):
			if sarr[s+i] != earr[i]:
				part1_match = False
				break

		if not part1_match:
			continue

		does_match = False
		if (slen & 1 == 0) and (e_prefix_len > 0) and (sarr[-1] <= earr[e_prefix_len-1]):
			val = earr[e_prefix_len-1] - sarr[-1]
			does_match = True
		elif (slen & 1 == 1) and (sarr[-1] == earr[e_prefix_len-1]):
			val = 0
			does_match = True
		elif s == slen:
			val = 0
			does_match = True

		if not does_match:
			continue

		val += s_prefix_len
		for j in range(e_prefix_len,elen):
			val += earr[j]

		minval = min(minval, val)

	if minval == 0xFFFFFFFF:
		return 'IMPOSSIBLE'
	else:
		return minval+minval_delta

if __name__ == '__main__':
	T = int(input())
	for t in range(T):
		S,E = input().split()
		print(f'Case #{t+1}: {solve(S,E)}')