from typing import List
import collections

class Solution:
	def threeSum(self, nums: List[int]) -> List[List[int]]:
		cnum = collections.Counter(nums)
		res = []
		pl = list(filter(lambda n:n>0, cnum.keys()))
		pos = set(pl)
		nl = list(filter(lambda n:n<0, cnum.keys()))
		neg = set(nl)

		if 0 in cnum:
			if cnum[0] >= 3:
				res.append([0,0,0])
			for p in pos:
				if (-p) in neg:
					res.append([-p,0,p])

		for i in range(len(pl)):
			if cnum[pl[i]] > 1 and (-2*pl[i]) in neg:
				res.append([-2*pl[i], pl[i], pl[i]])
			for j in range(i+1, len(pl)):
				nij = -(pl[i]+pl[j])
				if nij in neg:
					res.append([nij, pl[i], pl[j]])

		for i in range(len(nl)):
			if cnum[nl[i]] > 1 and (-2*nl[i]) in pos:
				res.append([nl[i], nl[i], (-2*nl[i])])
			for j in range(i+1, len(nl)):
				nij = -(nl[i]+nl[j])
				if nij in pos:
					res.append([nl[i],nl[j],nij])

		return(res)

hey = Solution()
print(hey.threeSum([-1,0,1,2,-1,-4]))