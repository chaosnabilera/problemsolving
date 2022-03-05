import random
import sys

if __name__ == '__main__':
	with open(sys.argv[1],'w') as ofile:
		ofile.write("1\n")
		ofile.write("100000 1\n")
		for i in range(100000):
			ofile.write("{} ".format(i+1))
		ofile.write("\n")