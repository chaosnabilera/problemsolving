if __name__ == '__main__':
	T = int(input())
	for t in range(T):
		x,y = tuple(map(int,input().split()))
		c1,c2,c3,c4,c5,c6 = tuple(map(int,input().split()))

		h_p = min(c2,c1+c3)
		h_n = min(c5,c6+c4)
		v_p = min(c6,c1+c5)
		v_n = min(c3,c2+c4)
		d_p = min(c1,c2+c6)
		d_n = min(c4,c3+c5)

		#print('h_p:{} h_n:{} v_p:{} v_n:{} d_p:{} d_n:{}'.format(h_p,h_n,v_p,v_n,d_p,d_n))

		# pattern 1
		h = h_p if y > 0 else h_n
		v = v_p if x > 0 else v_n
		cost = abs(x*v) + abs(y*h)
		#print(cost)

		# pattern 2
		d = d_p if x > 0 else d_n
		h = h_p if x < y else h_n
		cost = min(cost, abs(x*d) + abs(abs(x-y)*h))

		# pattern 3
		d = d_p if y > 0 else d_n
		v = v_p if y < x else v_n
		cost = min(cost, abs(y*d) + abs(abs(x-y)*v))

		print(cost)
		