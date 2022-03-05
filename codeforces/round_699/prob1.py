from collections import Counter

def solve(x,y,s):
	cnt = Counter(s)

	need = {}
	if x > 0:
		need['R'] = x
	elif x < 0:
		need['L'] = -x

	if y > 0:
		need['U'] = y
	elif y < 0:
		need['D'] = -y

	for k in need:
		if (k not in cnt) or cnt[k] < need[k]:
			return 'NO'

	return 'YES'



if __name__ == '__main__':
	T = int(input())
	for t in range(T):
		x,y = map(int, input().split())
		s = input()
		print(solve(x,y,s))