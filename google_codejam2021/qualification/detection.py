import bisect
import math

INTEGRAL_ESTIMATE = []

# generate array of integration result of logistic function
def generate_estimation():
	global INTEGRAL_ESTIMATE
	x = -3
	while x <= 3:
		xm3 = math.log(1.0+math.exp(x-3.0))
		xp3 = math.log(1.0+math.exp(x+3.0))
		INTEGRAL_ESTIMATE.append((xp3-xm3)/6.0)
		x += 0.01

def estimate_x_from_average(avg):
	i = bisect.bisect_left(INTEGRAL_ESTIMATE, avg)
	return -3 + (0.01*i)

def solve(iarr):
	S = len(iarr) # number of people
	P = len(iarr[0]) # number of problems

	problem = [0]*P
	student = [0]*S

	for s in range(S):
		for p in range(P):
			result = int(iarr[s][p])
			student[s] += result
			problem[p] += result

	problem_x = [estimate_x_from_average(p/S) for p in problem]
	student_x = [estimate_x_from_average(s/P) for s in student]

	iproblem_x = [(i,p) for i,p in enumerate(problem_x)]
	iproblem_x.sort(key=lambda t:t[1])

	expected_solve = [0]*S
	actual_solve = [0]*S
	for s in range(S):
		sx = student_x[s]
		for p, px in iproblem_x[:100]:
			expected_solve[s] += 1/(1+math.exp(-(sx+px)))
			actual_solve[s] += int(iarr[s][p])

	# print(expected_solve)
	# print(actual_solve)

	diff = []
	for s in range(S):
		diff.append((s, actual_solve[s] - expected_solve[s]))
	diff.sort(key=lambda t:t[1], reverse = True)

	# print(diff[:10])

	return diff[0][0]

	
if __name__ == '__main__':
	T = int(input())
	P = int(input())
	generate_estimation()
	for t in range(T):
		iarr = [input() for i in range(100)]
		print('Case #{}: {}'.format(t+1, solve(iarr)+1))