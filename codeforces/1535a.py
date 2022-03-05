if __name__ == '__main__':
	T = int(input())
	for t in range(T):
		s1,s2,s3,s4 = tuple(map(int,input().split()))

		w1 = max(s1,s2)
		w2 = max(s3,s4)
		if w1 < w2:
			if max(w1,min(s3,s4)) == w1:
				print('YES')
			else:
				print('NO')
		else:
			if max(w2,min(s1,s2)) == w2:
				print('YES')
			else:
				print('NO')