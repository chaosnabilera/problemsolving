#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <cstring>
#include <limits>
#include <utility>
#include <queue>
#include <array>
#include <string>
#include <deque>
#include <cstring>

using namespace std;

int N;
int preorder[100];
int inorder[100];

int preorder_idx[1001];
int inorder_idx[1001];

struct BT{
	BT(int _val) : val(_val) { left = nullptr; right=nullptr; }
	~BT() {
		if(left != nullptr)
			delete left;
		if(right != nullptr)
			delete right;
	}
	int val;
	BT* left;
	BT* right;
};

void get_input(){
	scanf("%d", &N);
	for(int i=0; i<N; ++i)
		scanf("%d", &preorder[i]);
	for(int i=0; i<N; ++i)
		scanf("%d", &inorder[i]);
}

BT* rec_build(int pbeg, int pend, int ibeg, int iend){
	int rootval = preorder[pbeg];

	// printf("%d %d %d %d\n")

	BT* res = new BT(rootval);

	int lcnt = inorder_idx[rootval] - ibeg;
	int rcnt = iend - inorder_idx[rootval];

	if(lcnt)
		res->left = rec_build(pbeg+1, pbeg+lcnt, ibeg, ibeg+lcnt-1);
	
	if(rcnt)
		res->right = rec_build(pbeg+lcnt+1, pend, ibeg+lcnt+1, iend);

	return res;
}

void print_postorder(BT* node){
	if(node->left)
		print_postorder(node->left);
	if(node->right)
		print_postorder(node->right);

	printf("%d ",node->val);
}

void solve(){
	for(int i=0; i<N; ++i){
		preorder_idx[preorder[i]] = i;
		inorder_idx[inorder[i]] = i;
	}

	BT* root = rec_build(0,N-1,0,N-1);
	print_postorder(root);
	printf("\n");

	delete root;
}

int main(int argc, char** argv){
	int T;
	scanf("%d", &T);
	for(int i=0; i<T; ++i){
		get_input();
		solve();
	}
}