from collections import Counter

def solve(s, px, py):
	cnt = Counter(s)
	sx = cnt['R'] - cnt['L']
	sy = cnt['U'] - cnt['D']

	if (sx,sy) == (px,py):
		return 'YES'

	dx,dy = px-sx, py-sy

	rm_x = 'L' if dx > 0 else 'R'
	rm_y = 'D' if dy > 0 else 'U'

	if abs(dx) > 0 and cnt[rm_x] < abs(dx):
		return 'NO'

	if abs(dy) > 0 and cnt[rm_y] < abs(dy):
		return 'NO'

	return 'YES'


if __name__ == '__main__':
	T = int(input())
	for t in range(T):
		px,py = tuple(map(int,input().split()))
		s = input()
		print(solve(s,px,py))