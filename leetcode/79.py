from typing import List
import copy

def recSolve(board, visited, cr, cc, cstr):
	#print(cr,cc,cstr)
	if len(cstr) == 0:
		return True
	
	numrow = len(board)
	numcol = len(board[0])
	visited.add((cr,cc))
	# up
	nr, nc = cr-1, cc
	if (nr >= 0) and ((nr,nc) not in visited) and board[nr][nc] == cstr[0]:
		if recSolve(board, copy.deepcopy(visited), nr, nc, cstr[1:]):
			return True
	# down
	nr, nc = cr+1, cc
	if (nr <= numrow-1) and ((nr,nc) not in visited) and board[nr][nc] == cstr[0]:
		if recSolve(board, copy.deepcopy(visited), nr, nc, cstr[1:]):
			return True
	# left
	nr, nc = cr, cc-1
	if (nc >= 0) and ((nr,nc) not in visited) and board[nr][nc] == cstr[0]:
		if recSolve(board, copy.deepcopy(visited), nr, nc, cstr[1:]):
			return True
	# right
	nr, nc = cr, cc+1
	if (nc <= numcol-1) and ((nr,nc) not in visited) and board[nr][nc] == cstr[0]:
		if recSolve(board, copy.deepcopy(visited), nr, nc, cstr[1:]):
			return True
		
	return False
	
class Solution:
	def exist(self, board: List[List[str]], word: str) -> bool:
		numrow = len(board)
		numcol = len(board[0])
		for r in range(numrow):
			for c in range(numcol):
				if board[r][c] == word[0]:
					if recSolve(board, set([]), r, c, word[1:]):
						return True
		return False
		
board = [["A","B","C","E"],["S","F","E","S"],["A","D","E","E"]]
word = "ABCESEEEFS"

sol = Solution()
print(sol.exist(board, word))