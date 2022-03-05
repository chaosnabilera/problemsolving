def dfs(v, graph):
	isloop = False
	lo, ro = graph

	# expand right
	pr, r = lo, ro
	expand_right = []
	while True:
		if len(v[r]) == 1:
			break
		else:
			nr1, nr2 = v[r]
			rn = nr1 if nr1 != pr else nr2
			expand_right.append(rn)
			if rn == lo: # we found loop
				isloop = True
				break
			pr = r
			r = rn

	if isloop:
		return True, graph + expand_right

	# expand left
	l, pl = lo, ro
	expand_left = []
	while True:
		if len(v[l]) == 1:
			break
		else:
			nl1, nl2 = v[l]
			nl = nl1 if nl1 != pl else nl2
			expand_left.append(nl)
			pl = l
			l = nl

	final_graph = expand_left[::-1] + graph + expand_right
	# if final_graph[0] > final_graph[-1]:
	# 	final_graph = final_graph[::-1]

	if len(final_graph) == 2:
		return True, final_graph
	else:
		return False, final_graph

def findMinvalInLineEnds(lines):
	minval, minval_idx = 0xFFFF, None
	secval, secval_idx = 0xFFFF, None

	for i in range(len(lines)):
		if lines[i][0] < minval:
			minval = lines[i][0]
			minval_idx = i
		elif lines[i][0] < secval:
			secval = lines[i][0]
			secval_idx = (i, 0)
		if lines[i][-1] < secval:
			secval = lines[i][-1]
			secval_idx = (i,-1)

	return minval, minval_idx, secval, secval_idx

def greedyConnect(lines, points):
	edges = []
	points.sort()
	while len(lines) > 0 or len(points) > 0:
		minval_p = points[0] if len(points) > 0 else 0xFFFF
		minval_l, minval_idx_l, secval_l, secval_idx_l = findMinvalInLineEnds(lines)

		if minval_p < minval_l:
			# if current minval is a point, just add self loop
			edges.append((minval_p, minval_p))
			points = points[1:]
		else:
			# if minval is one end of line, we merge that line with a point or a line
			if minval_p < secval_l:
				edges.append((minval_l, minval_p))
				li = minval_idx_l
				lines[li][0] = minval_p
				if lines[li][0] > lines[li][-1]:
					lines[li] = [lines[li][-1], lines[li][0]]
				points = points[1:]
			else:
				edges.append((minval_l, secval_l))
				li = minval_idx_l
				li_s, ei_s = secval_idx_l

				if li == li_s: # created loop
					del lines[li]
				else:
					lines[li][0] = lines[li_s][-1] if ei_s == 0 else lines[li_s][0]
					if lines[li][0] > lines[li][-1]:
						lines[li] = [lines[li][-1], lines[li][0]]
					del lines[li_s]
	return edges





if __name__ == '__main__':
	n,m = tuple(map(int, input().split()))
	v = [[] for i in range(n)]

	for i in range(m):
		v1,v2 = tuple(map(int, input().split()))
		v1,v2 = v1-1,v2-1
		v[v1].append(v2)
		v[v2].append(v1)

	# validate input
	input_valid = True
	for i in range(n):
		if len(v[i]) > 2:
			input_valid = False
			break
		v[i].sort()

	if not input_valid:
		print('NO')
		exit()

	loops = []
	lines = []
	points = []

	visited = [False for i in range(n)]

	for i in range(n):
		if visited[i]:
			continue
		elif len(v[i]) == 0:
			points.append(i)
			visited[i] = True
		elif len(v[i]) == 1 and v[i] == i:
			loops.append([i,i])
			visited[i] = True
		else:
			isloop, graph = dfs(v,[i,v[i][0]])
			for gi in graph:
				visited[gi] = True
			if isloop:
				loops.append(graph)
			else:
				lines.append(graph)

	# print('loops')
	# for p in loops:
	# 	print('\t{}'.format([e+1 for e in p]))
	# print('lines')
	# for p in lines:
	# 	print('\t{}'.format([e+1 for e in p]))
	# print('points')
	# for p in points:
	# 	print('\t{}'.format(p+1))

	# We only need two ends of the line
	for li in range(len(lines)):
		e1,e2 = lines[li][0], lines[li][-1]
		lines[li] = [e1,e2] if e1<e2 else [e2,e1]

	edges = greedyConnect(lines, points)

	print('YES')
	print(len(edges))
	for v1,v2 in edges:
		v1 += 1
		v2 += 1
		if v1 < v2:
			print('{} {}'.format(v1,v2))
		else:
			print('{} {}'.format(v2,v1))