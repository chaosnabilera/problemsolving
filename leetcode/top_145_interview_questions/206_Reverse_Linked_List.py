# Definition for singly-linked list.
class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next

class Solution:
    def reverseList(self, head: ListNode) -> ListNode:
        return self.reverseRecursive(None, head) if head != None else None

    def reverseRecursive(self, prev, node):
        nnext = node.next
        node.next = prev
        if nnext:
            return self.reverseRecursive(node, nnext)
        else:
            return node

fuck = Solution()

node5 = ListNode(5,None)
node4 = ListNode(4,node5)
node3 = ListNode(3,node4)
node2 = ListNode(2,node3)
node1 = ListNode(1,node2)

hey = fuck.reverseList(node1)

while hey:
    print(hey.val)
    hey = hey.next