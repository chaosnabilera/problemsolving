import math

if __name__ == '__main__':
	n = int(input())
	rc = list(map(int,input().split()))
	bs = list(map(int,input().split()))

	sum_rc = sum(rc)
	sum_bs = sum(bs)

	if sum_rc > sum_bs:
		print(1)
	else:
		only_rc = 0
		only_bs = 0
		for i in range(n):
			if rc[i] == 1 and bs[i] == 0:
				only_rc += 1
			if rc[i] == 0 and bs[i] == 1:
				only_bs += 1
		if only_rc == 0:
			print(-1)
		else:
			print((only_bs//only_rc)+1)