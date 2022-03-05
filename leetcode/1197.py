from collections import deque
import heapq

class Solution:
    def minKnightMoves(self, x: int, y: int) -> int:
        q = deque([(0,0,0)])
        minmoves = {}
        
        x = abs(x)
        y = abs(y)
        
        while q:
            r,c,v = q.popleft()
            if r < -3 or c < -3:
                continue
                
            if abs(r)+abs(c) > 300:
                continue
                
            if (r,c) in minmoves:
                continue
            
            minmoves[(r,c)] = v
            
            if r==x and c==y:
                return v
            
            q.append((r+2,c+1,v+1))
            q.append((r+2,c-1,v+1))
            q.append((r+1,c+2,v+1))
            q.append((r+1,c-2,v+1))
            q.append((r-2,c+1,v+1))
            q.append((r-2,c-1,v+1))
            q.append((r-1,c+2,v+1))
            q.append((r-1,c-2,v+1))
            
        return -1


def hscore(x,y,r,c):
    xdist = abs(x-r)
    ydist = abs(y-c)
    if xdist > ydist:
        ldist, sdist = xdist, ydist
    else:
        ldist, sdist = ydist, xdist
    laststep = [0,3,2,3]

    if ldist == (sdist << 1):
        return sdist
    elif ldist < (sdist << 1):
        a1 = ldist >> 1
        a2 = ((sdist - a1) >> 2) << 1
        a3 = laststep[(sdist - a1) & 0x3]
        return a1+a2+a3
    else:
        a0 = sdist
        a1 = ldist - (sdist << 1)
        a2 = (a1 >> 2) << 1
        a3 = laststep[(a1-a2) & 0x3]
        print(ldist,sdist,a1,a2,a3)
        return a0 + a2 + a3

sol = Solution()
x,y = 100,100
print(sol.minKnightMoves(x,y))
print(hscore(x,y,0,0))

