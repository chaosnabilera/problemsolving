from collections import Counter

if __name__ == '__main__':
	t = int(input())
	for i in range(t):
		n = int(input())
		barr = list(map(int, input().split()))
		bcnt = Counter(barr)
		msg = 'NO'
		for n in bcnt:
			if bcnt[n] >= 2:
				msg = 'YES'
				break
		print(msg)