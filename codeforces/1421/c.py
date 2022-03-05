if __name__ == '__main__':
	s = input()
	print(3)
	print('L 2')
	s = s[1]+s
	#print(s)
	print('R 2')
	s = s + s[1:-1][::-1]
	#print(s)
	print('R {}'.format(len(s)-1))
	s = s + s[-2]
	#print(s)