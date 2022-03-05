import random

def generate_random(M,N):
	res = []
	for i in range(M*N):
		res.append([random.randint(0,M-1),random.randint(0,N-1)])
	return res

if __name__ == '__main__':
	M = 200
	N = 50
	with open('305_input_random.txt','w') as ofile:
		ofile.write(f'{M}\n')
		ofile.write(f'{N}\n')
		ofile.write(f'{str(generate_random(M,N))}\n')