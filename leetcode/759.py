import heapq

class Interval:
    def __init__(self, start: int = None, end: int = None):
        self.start = start
        self.end = end

class Solution:
    def employeeFreeTime(self, schedule: '[[Interval]]') -> '[Interval]':
        minheap = []
        si = [0]*len(schedule)
        N = len(schedule)
        for i in range(N):
            heapq.heappush(minheap, (schedule[i][0].start, schedule[i][0].end, i))
        
        ans = []
        
        cs,ce = None, None
        while minheap:
            print(minheap)
            s,e,i = heapq.heappop(minheap)
            si[i] += 1
            if si[i] < len(schedule[i]):
                heapq.heappush(minheap, (schedule[i][si[i]].start, schedule[i][si[i]].end, i))
                
            if cs != None:
                if s > ce:
                    ans.append([ce,s])
                    cs, ce = None, None
                else:
                    ce = e
            else:
                cs, ce = s, e
                
        return ans


ilist = [[Interval(1,2),Interval(5,6)], [Interval(1,3)], [Interval(4,10)]]
sol = Solution()
print(sol.employeeFreeTime(ilist))
