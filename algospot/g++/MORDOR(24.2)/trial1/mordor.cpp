#include <iostream>

using namespace std;

int N, Q;
int Pos[100000];
int Neg[100000];

struct TNode{
	TNode(int _maxval, int _beg, int _end) : maxval(_maxval), beg(_beg), end(_end) {
		left = nullptr;
		right = nullptr;
	};
	~TNode(){
		if(left)
			delete left;
		if(right)
			delete right;
	}

	int maxval;
	int beg;
	int end;
	TNode* left;
	TNode* right;
};

TNode* rec_build(int beg, int end, int* arr){
	if(beg == end){
		return new TNode(arr[beg], beg, end);
	}
	else{
		int mid = (beg+end) >> 1;

		TNode* left = rec_build(beg,   mid, arr);
		TNode* right= rec_build(mid+1, end, arr);

		TNode* node = new TNode(max(left->maxval, right->maxval), beg, end);
		node->left = left;
		node->right= right;

		return node;
	}
}

int find_range(TNode* node, int beg, int end){
	// printf("%d %d : %d %d\n",node->beg, node->end, beg, end);
	if(node->beg == beg && node->end == end){
		return node->maxval;
	}

	int mid = (node->beg + node->end) >> 1;
	if(end <= mid){
		return find_range(node->left,  beg, end);
	}
	else if(beg > mid){
		return find_range(node->right, beg, end);
	}
	else{
		int lres = find_range(node->left,  beg,  mid);
		int rres = find_range(node->right, mid+1,end);
		return max(lres, rres);
	}
}

void solve(){
	int beg,end;

	scanf("%d %d", &N, &Q);
	for(int i=0; i<N; ++i){
		scanf("%d", &Pos[i]);
		Neg[i] = -Pos[i];
	}

	TNode* max_tree = rec_build(0,N-1,Pos);
	TNode* min_tree = rec_build(0,N-1,Neg);

	for(int i=0; i<Q; ++i){
		scanf("%d %d", &beg, &end);
		// printf("%d %d\n",beg,end);
		int maxres = find_range(max_tree, beg, end);
		int minres = find_range(min_tree, beg, end);
		printf("%d\n", maxres+minres);
	}

	delete max_tree;
	delete min_tree;
}

int main(int argc, char** argv){
	int T;
	scanf("%d", &T);
	for(int i=0; i<T; ++i){
		solve();
	}
}