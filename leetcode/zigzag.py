class CyclicIterator:
    def __init__(self, lists):
        self.lists = lists
        self.li = 0
        self.lli = 0

    def next(self) -> int:
        lists, li, lli = self.lists, self.li, self.lli
        retval = lists[li][lli]
        li += 1
        
        if li == len(lists):
            li = 0
            lli += 1
        
        while lists and lli >= len(lists[li]):
            del lists[li]
            if li >= len(lists):
                li = 0
                lli += 1
                
        self.li, self.lli = li, lli
        
        return retval
    
    def hasNext(self) -> bool:
        if self.lists:
            return True

lists = [
    [1 ,2 ,3 ,4],
    [5 ,6 ,7 ,8 ,9 ,10],
    [10,11,12,13,14,15],
    ['a','b','c','d','e','f','g','h','i'],
    [16,17,18,19]
]

sol = CyclicIterator(lists)

while sol.hasNext():
    print(sol.next())
