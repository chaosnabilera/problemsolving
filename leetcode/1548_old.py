from typing import List

class Solution:
    def mostSimilar(self, n: int, roads: List[List[int]], names: List[str], targetPath: List[str]) -> List[int]:
        P = len(targetPath)

        # build graph from roads
        adjascent = {i:set([]) for i in range(n)}
        for a,b in roads:
            adjascent[a].add(b)
            adjascent[b].add(a)

        
        print('adjascent')
        print(adjascent)

        # calculate name_idx
        name_to_idx = {}
        num_unique_names = 0
        names_idx = [-1]*n
        for i,nm in enumerate(names):
            if nm not in name_to_idx:
                name_to_idx[nm] = num_unique_names
                num_unique_names += 1
            names_idx[i] = name_to_idx[nm]

        print('name_to_idx')
        print(name_to_idx)

        same_name_list = [[] for i in range(num_unique_names)]
        for i,n in enumerate(names_idx):
            same_name_list[n].append(i)

        print('same_name_list')
        print(same_name_list)

        target_path_candidate_nodes = []
        for nm in targetPath:
            if nm in name_to_idx:
                target_path_candidate_nodes.append(same_name_list[name_to_idx[nm]])
            else:
                target_path_candidate_nodes.append([])

        print('target_path_candidate_nodes')
        print(target_path_candidate_nodes)

        target_name_to_idx = []
        for nm in targetPath:
            if nm in name_to_idx:
                target_name_to_idx.append(name_to_idx[nm])
            else:
                target_name_to_idx.append(-1)


        # define dfs function
        def dfs(sofar, cur_node_idx, target_name_idx, cur_depth, target_depth):
            if cur_depth == target_depth:
                if node_name_idx[cur_node_idx] == target_name_idx:
                    return sofar
                else:
                    return None

            sofar.append(cur_node_idx)
            for nxt in adjascent[cur]:
                retval = dfs(sofar, nxt, target_name_idx, cur_depth+1, target_depth)
                if retval != None:
                    return sofar
            sofar.pop()

        def expand_right(start_node_idx, num_append):
            res = []
            cur = start_node_idx
            for i in range(num_append):
                nxt = next(iter(adjascent[cur]))
                res.append(nxt)
                cur = nxt
            return res

        def expand_left(start_node_idx, num_append):
            return expand_right(start_node_idx, num_append)[::-1]

        # setup dp
        dp = [[] for i in range(P)]

        # set base case
        for right in range(P-1,-1,-1):
            if len(target_path_candidate_nodes[right]) > 0:
                for cand in target_path_candidate_nodes[right]:
                    exp_seq = expand_right(cand, P-1-right)
                    dp[right].append(([cand]+exp_seq, len(exp_seq)))
                break

        min_edit_sequence = None
        for di in range(right-1, -1, -1):
            for cur_node_idx in target_path_candidate_nodes[di]:
                for pi in range(di+1,P):
                    min_edit_distance = 0xFFFF

                    for pseq, ped in dp[pi]:
                        if ped + (pi-di-1) >= min_edit_distance:
                            continue

                        target_name_idx = target_name_to_idx[pi]
                        dfs_res = dfs([], cur_node_idx, target_name_idx, 0, pi-di)
                        if dfs_res == None:
                            continue





        if right == 0:
            return [0]+expand_right(0, len(targetPath)-1)


sol = Solution()

# n = 4
# roads = [[1,0],[2,0],[3,0],[2,1],[3,1],[3,2]]
# names = ["ATL","PEK","LAX","DXB"]
# targetPath = ["ABC","DEF","GHI","JKL","MNO","PQR","STU","VWX"]

# n = 6
# roads = [[0,1],[1,2],[2,3],[3,4],[4,5]]
# names = ["ATL","PEK","LAX","ATL","DXB","HND"]
# targetPath = ["ATL","DXB","HND","DXB","ATL","LAX","PEK"]

n = 4
roads = [[1,0],[2,0],[3,0],[2,1],[3,1],[3,2]]
names = ["ATL","PEK","LAX","DXB"]
targetPath = ["ABC","DEF","GHI","JKL","MNO","PQR","STU","VWX"]

print(sol.mostSimilar(n, roads, names, targetPath))