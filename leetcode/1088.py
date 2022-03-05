def nearest_legit_high(num):
	num = list(str(num))
	legit = ['0','1','6','8','9']
	next_legit = {'2':'6','3':'6','4':'6','5':'6','7':'8'}

	i = 0
	while i < len(num):
		if num[i] not in legit:
			num[i] = next_legit[num[i]]
			i += 1
			break
		i += 1

	while i < len(num):
		num[i] = '0'
		i += 1

	return int(''.join(num))

def nearest_legit_low(num):
	num = list(str(num))
	legit = ['0','1','6','8','9']
	next_legit = {'2':'1','3':'1','4':'1','5':'1','7':'6'}

	i = 0
	while i < len(num):
		if num[i] not in legit:
			num[i] = next_legit[num[i]]
			i += 1
			break
		i += 1

	while i < len(num):
		num[i] = '9'
		i += 1

	return int(''.join(num))

def to_base_5(num):
	num = list(str(num))
	k = 0
	bsum = 0
	ston = {'0':0,'1':1,'6':2,'8':3,'9':4}
	for i in range(len(num)-1,-1,-1):
		bsum += ston[num[i]] * (5**k)
		k += 1
	return bsum

def base5_to_str(num):
	arr = []
	ntos = ['0','1','6','8','9']
	while num:
		div = num // 5
		mod = num % 5
		arr.append(ntos[mod])
		num = div
	return ''.join(arr[::-1])

def is_confusing(numstr, numint):
	arr = []
	opposite = {'0':'0','1':'1','6':'9','8':'8','9':'6'}
	for i in range(len(numstr)-1,-1,-1):
		arr.append(opposite[numstr[i]])
	arr = ''.join(arr)
	if int(arr) == numint:
		return False
	else:
		return True

for i in range(1,30):
	numstr = base5_to_str(i)
	numint = int(numstr)
	if numint > 100:
		break
	if is_confusing(numstr,numint):
		print(numstr)