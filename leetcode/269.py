from collections import defaultdict
from collections import deque
from typing import List

class Solution:
    def alienOrder(self, words: List[str]) -> str:
        LT = defaultdict(set)
        GT = defaultdict(set)
        alphabet = list(set(''.join(words)))

        def recgraph(words):
            if len(words) < 2:
                return
            for i in range(len(words)-1):
                a,b = words[i][0], words[i+1][0]
                if a != b:
                    LT[a].add(b)
                    GT[b].add(a)
                if a == b and len(words[i][1:]) > 0 and len(words[i+1][1:]) == 0:
                    return -1

            nwdict = defaultdict(list)
            for w in words:
                if len(w) > 1:
                    nwdict[w[0]].append(w[1:])

            for nw in nwdict.values():
                if recgraph(nw) == -1:
                    return -1

        def checkcycle(c,visited):
            if c in visited:
                return False
            visited.add(c)
            for p in GT[c]:
                if not checkcycle(p,visited):
                    return False
            visited.remove(c)
            return True

        def insertionsort(iarr):
            for i in range(len(iarr)):
                for j in range(i+1,len(iarr)):
                    if iarr[i] in LT[iarr[j]]:
                        iarr[i],iarr[j] = iarr[j],iarr[i]

        # actual calc part
        if recgraph(words) == -1:
            return ''

        tomerge = deque(list(filter(lambda c:len(LT[c])==0, alphabet)))

        if len(tomerge) == 0:
            return ''

        # check cycle
        for c in alphabet:
            if not checkcycle(c, set([])):
                return ''

        while tomerge:
            c = tomerge.popleft()
            for p in GT[c]:
                LT[p] |= LT[c]
                tomerge.append(p)

        for c in alphabet:
            if c in LT[c] or c in GT[c]:
                return ''

        insertionsort(alphabet)
        return ''.join(alphabet)


sol = Solution()
words = ["z","x","z"]

print(sol.alienOrder(words))