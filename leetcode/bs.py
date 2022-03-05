
def searchBinary(sortedarr, target):
	left = 0
	right = len(sortedarr)-1

	while True:
		test = (left+right) // 2
		if sortedarr[test] == target:
			return test

		if left == right:
			break

		if sortedarr[test] < target:
			left = test+1
		else:
			right = test-1

	return -1

hey = [0,1,2,3,4,5,6,7,8,9]

print(searchBinary(hey,0))
print(searchBinary(hey,1))
print(searchBinary(hey,2))
print(searchBinary(hey,3))
print(searchBinary(hey,4))
print(searchBinary(hey,5))
print(searchBinary(hey,6))
print(searchBinary(hey,7))
print(searchBinary(hey,8))
print(searchBinary(hey,9))
print(searchBinary(hey,71))
print(searchBinary(hey,744))