import math

def solve(A,B):
	g = math.gcd(A,B)
	min_x, min_y = 0xFFFFFFFF,0xFFFFFFFF
	for x in range(-20,20):
		for y in range(-20,20):
			if (x*A)+(y*B) == g:
				if(abs(x)+abs(y) < abs(min_x)+abs(min_y)):
					min_x, min_y = x,y
	return min_x, min_y

if __name__ == '__main__':
	maxc = 0
	for A in range(1,20):
		for B in range(A+1,21):
			x,y = solve(A,B)
			print(f'A:{A} B:{B} x:{x} y:{y}')
			maxc = max(maxc,abs(x)+abs(y))
	print(maxc)