import math
import sys

if __name__ == '__main__':
	low = 1
	high = 1000000

	while low < high:
		med = math.ceil((low+high)/2)
		print(med)
		sys.stdout.flush()

		response = input()

		if response == '>=':
			low = med
		else:
			high = med-1

	print('! {}'.format(low))