from typing import List

def kthElement2SortedArray(nums1, nums2, k):
    if len(nums1) > len(nums2):
        longarr, shortarr = nums1, nums2
    else:
        longarr, shortarr = nums2, nums1

    L,S = len(longarr), len(shortarr)

    # Check for invalid input
    if k >= L+S:
        return -1
    # Check for trivial case
    if S == 0:
        return longarr[k]
    if k == 0:
        return min(longarr[0], shortarr[0])
    if k == L+S-1:
        return max(longarr[-1], shortarr[-1])

    smin, smax = max(0,k-L), min(k,S)
    while True:
        s = (smin+smax) >> 1
        l = k-s

        # print('s:{} l:{}'.format(s,l))

        if (s > 0) and (l < L) and (shortarr[s-1] > longarr[l]):
            smax = max(s-1, smin)
        elif (l > 0) and (s < S) and (longarr[l-1] > shortarr[s]):
            smin = min(s+1, smax)
        else:
            if (s >= S):
                return longarr[l]
            elif (l >= L):
                return shortarr[s]
            else:
                return min(shortarr[s], longarr[l])

                
class Solution:
    def findMedianSortedArrays(self, nums1: List[int], nums2: List[int]) -> float:
        MN = len(nums1) + len(nums2)
        if MN & 1 == 1:
            return kthElement2SortedArray(nums1, nums2, (MN >> 1))
        else:
            a1 = kthElement2SortedArray(nums1, nums2, (MN >> 1))
            a2 = kthElement2SortedArray(nums1, nums2, (MN >> 1)-1)
            return (a1+a2)/2.0

sol = Solution()
nums1 = [2]
nums2 = []

print(sol.findMedianSortedArrays(nums1, nums2))