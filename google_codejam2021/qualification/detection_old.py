def solve(iarr):
	S = len(iarr) # number of people
	P = len(iarr[0]) # number of problems

	iarr = [[int(c) for c in line] for line in iarr]

	# calculate overall performance
	total_solved = [0]*S
	for s in range(S):
		for p in range(P):
			total_solved[s] += iarr[s][p]
		total_solved[s] /= P
	total_solved_rank = [(total_solved[s],s) for s in range(S)]
	total_solved_rank.sort(reverse=True)

	sidx_to_total_rank = {}
	for i,val in enumerate(total_solved_rank):
		tperf, tidx = val
		sidx_to_total_rank[tidx] = i

	# calculate difficulties of problems
	difficulty = [0]*P
	for s in range(S):
		for p in range(P):
			difficulty[p] += iarr[s][p]
	for p in range(P):
		difficulty[p] /= P

	difficulty_rank = [(difficulty[p],p) for p in range(P)]
	difficulty_rank.sort()

	# Use top 100 difficult problems as indicator
	difficult_solved = [0]*S
	for s in range(S):
		for prank,pidx in difficulty_rank[:100]:
			difficult_solved[s] += iarr[s][pidx]
		difficult_solved[s] /= 100

	difficult_solved_rank = [(difficult_solved[s],s) for s in range(S)]
	difficult_solved_rank.sort(reverse=True)

	for i in range(20):
		dperf, didx = difficult_solved_rank[i]
		if sidx_to_total_rank[didx] > 50:
			return didx

	return difficult_solved_rank[0][1]
	
if __name__ == '__main__':
	T = int(input())
	P = int(input())
	for t in range(T):
		iarr = [input() for i in range(100)]
		print('Case #{}: {}'.format(t+1, solve(iarr)+1))