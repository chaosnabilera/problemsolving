# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def maxDepth(self, root: TreeNode) -> int:       
        return self.recursive(root, 0)
    
    def recursive(self, node: TreeNode, depth):
        if not node:
            return depth
        else:
            return max(self.recursive(node.left, depth+1), self.recursive(node.right, depth+1))
        