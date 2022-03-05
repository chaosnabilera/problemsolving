from typing import List

def getGTEIndex(arr, beg, end, val):
    if end <= beg:
        return end
    if val > arr[end-1]:
        return end
    if val <= arr[beg]:
        return beg
    
    cbeg = beg
    cend = end
    while True:
        p = (cbeg+cend) >> 1
        if (arr[p] >= val) and (arr[p-1] < val):
            return p
        else:
            if arr[p] < val:
                cbeg = p+1
            else:
                cend = p-1
            

def kthElement2SortedArray(nums1, nums2, k):
    parr, pbeg, pend = nums1, 0, len(nums1)
    farr, fbeg, fend = nums2, 0, len(nums2)

    while True:
        if pbeg == pend:
            parr, farr = farr, parr
            pbeg, fbeg = fbeg, pbeg
            pend, fend = fend, pend

        pp = (pbeg+pend)>>1
        pval = parr[pp]

        #print('pbeg:{} pend:{} pp:{} pval:{} fbeg:{} fend:{}'.format(pbeg,pend,pp,pval,fbeg,fend))

        fgte = getGTEIndex(farr, fbeg, fend, pval)
        cnt = (pp-pbeg) + (fgte-fbeg)

        #print('pbeg:{} pend:{} pp:{} pval:{} fbeg:{} fend:{} fgte:{} cnt:{}'.format(pbeg,pend,pp,pval,fbeg,fend,fgte,cnt))

        if cnt == k:
            return pval
        else:
            if cnt < k:
                k -= cnt+1
                pbeg = pp+1
                fbeg = fgte
            else:
                pend = pp
                fend = fgte
                
                
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