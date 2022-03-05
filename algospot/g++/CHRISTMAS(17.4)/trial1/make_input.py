import random
import sys

if __name__ == '__main__':
	with open(sys.argv[1], 'w') as ofile:
		N = int(sys.argv[2])
		K = int(sys.argv[3])
		ofile.write("3\n")
		for ii in range(3):
			ofile.write("{} {}\n".format(N,K))
			for i in range(N):
				ofile.write("{} ".format(random.randint(1,100000)))
			ofile.write("\n")