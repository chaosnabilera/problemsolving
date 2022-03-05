from typing import List

class Solution:
    def numIslands2(self, m: int, n: int, positions: List[List[int]]) -> List[int]:
        R,C = m,n
        parent = [[None]*C for r in range(R)]
        children_cnt = [[0]*C for r in range(R)]
        island_cnt = 0
        
        def find(r,c):
            nonlocal parent
            while parent[r][c] != (r,c):
                r,c = parent[r][c]
            return (r,c)
        
        def merge(r1,c1,r2,c2):
            nonlocal parent,children_cnt,island_cnt

            #print(1,r1,c1,parent)
            pr1,pc1 = find(r1,c1)
            #print(2,r2,c2,parent)
            pr2,pc2 = find(r2,c2)
            
            if pr1 == pr2 and pc1 == pc2:
                return
            
            if children_cnt[pr1][pc1] < children_cnt[pr2][pc2]:
                parent[pr1][pc1] = (pr2,pc2)
                children_cnt[pr2][pc2] += children_cnt[pr1][pc1]
            else:
                parent[pr2][pc2] = (pr1,pc1)
                children_cnt[pr1][pc1] += children_cnt[pr2][pc2]
            island_cnt -= 1
            
        ans = []
        for r,c in positions:
            #print(r,c)
            if parent[r][c] != None:
                ans.append(island_cnt)
                continue
            
            parent[r][c] = (r,c)
            island_cnt += 1
            
            if r > 0 and parent[r-1][c] != None:
                merge(r,c,r-1,c)
            if c > 0 and parent[r][c-1] != None:
                merge(r,c,r,c-1)
            if r < R-1 and parent[r+1][c] != None:
                merge(r,c,r+1,c)
            if c < C-1 and parent[r][c+1] != None:
                merge(r,c,r,c+1)
                
            ans.append(island_cnt)
            
        return ans

sol = Solution()
m = 4
n = 5
positions = [[2, 2], [3, 4], [2, 3], [3, 0], [1, 1], [3, 4], [3, 0], [2, 1], [3, 4], [1, 2], [3, 4], [1, 3], [0, 4], [1, 4], [3, 3], [3, 4], [0, 3], [3, 0], [3, 2], [3, 4]]

print(sol.numIslands2(m,n,positions))