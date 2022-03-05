# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def buildTree(self, preorder: List[int], inorder: List[int]) -> TreeNode:
        numtonode = {n:TreeNode(n) for n in preorder}
        curpre = preorder
        curin = inorder
        
        while len(curpre) > 0:
            pre_ntoi = {curpre[i]:i for i in range(len(curpre))}
            in_ntoi = {curin[i]:i for i in range(len(curin))}
            
            for n in pre_ntoi:
                pre_ni = pre_ntoi[n]
                in_ni = in_ntoi[n]
                
            