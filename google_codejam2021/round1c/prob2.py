from collections import deque

def solve(y):
	ystr = str(y)

	curnum = 1
	curstr = '1'
	while len(curstr) < len(ystr)+1:
		curnum += 1
		curstr += str(curnum)

	minroar = int(curstr)

	for i in range(1,len(ystr)):
		# case 1 - just make consecutive from beginning
		tokstr = ystr[:i]
		toknum = int(tokstr)
		tokarr = [tokstr]
		
		for j in range(18):
			toknum += 1
			tokstr = str(toknum)
			tokarr.append(tokstr)

		beg = 0
		curlen = 0
		end = 0
		while curlen < len(ystr):
			curlen += len(tokarr[end])
			end += 1

		# print(tokarr)

		for beg in range(len(tokarr)):
			for end in range(beg+1,len(tokarr)):
				curint = int(''.join(tokarr[beg:end]))
				if curint > y:
					minroar = min(minroar, curint)

	return minroar

if __name__ == '__main__':
	T = int(input())
	for t in range(T):
		y = int(input())
		ans = solve(y)
		print(f'Case #{t+1}: {ans}')