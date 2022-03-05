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
#include <random>

using namespace std;

template <typename T>
class RNG32{
public:
	RNG32<T>(T beg, T end){
		rd = new std::random_device();
		gen = new std::mt19937((*rd)());
		dis = new std::uniform_int_distribution<T>(beg, end);
	}
	T operator()(){
		return (*dis)(*gen);
	}
private:
	std::random_device* rd;
	std::mt19937* gen;
	std::uniform_int_distribution<T>* dis;
};

int N;
int A[50000];
RNG32<int> rng(0,10000000);

struct Treap{
	int priority;
	int value;
	int count;

	Treap* left;
	Treap* right;
	Treap* parent;

	Treap(int _value){
		priority = rng();
		value = _value;
		count = 1;
		left   = nullptr;
		right  = nullptr;
		parent = nullptr;
	}

	void setLeft(Treap* tree){
		count = 1;
		if(right)
			count += right->count;
		left = tree;
		if(left){
			count += left->count;
			left->parent = this;
		}
	}

	void setRight(Treap* tree){
		count = 1;
		if(left)
			count += left->count;
		right = tree;
		if(right){
			count += right->count;
			right->parent = this;
		}
	}

	Treap* insert(Treap* node){
		if(node->priority < priority){
			if(node->value < value){
				if(left)
					setLeft(left->insert(node));
				else
					setLeft(node);
			}
			else{
				if(right)
					setRight(right->insert(node));
				else
					setRight(node);
			}
			return this;
		}
		else{
			pair<Treap*, Treap*> sres = split(node->value);
			node->setLeft(sres.first);
			node->setRight(sres.second);
			return node;
		}
	}

	// return self and parent
	Treap* find_kth_element(int k){
		int left_count  = (left) ? left->count : 0;
		int right_count = (right) ? right->count : 0;

		if(k == left_count + 1){
			return this;
		}
		else if(k <= left_count){
			return left->find_kth_element(k);
		}
		else{
			return right->find_kth_element(k-(left_count+1));
		}
	}

	pair<Treap*,Treap*> split(int sval){
		if(value < sval){
			if(right){
				Treap* oright = right;
				setRight(nullptr);
				pair<Treap*,Treap*> rres = oright->split(sval);
				setRight(rres.first);
				return make_pair(this, rres.second);
			}
			else{
				return make_pair(this, nullptr);
			}
		}
		else{
			if(left){
				Treap* oleft = left;
				setLeft(nullptr);
				pair<Treap*,Treap*> rres = oleft->split(sval);
				setLeft(rres.second);
				return make_pair(rres.first, this);
			}
			else{
				return make_pair(nullptr,this);
			}
		}
	}
};

Treap* merge(Treap* lt, Treap* rt){
	if(!lt && !rt)
		return nullptr;
	if(!lt)
		return rt;
	if(!rt)
		return lt;

	Treap* root = nullptr;
	if(lt->priority > rt->priority){
		root = lt;
		Treap* lr = root->right;
		root->setRight(nullptr);
		Treap* mres = merge(lr,rt);
		root->setRight(mres);
	}
	else{
		root = rt;
		Treap* rl = root->left;
		root->setLeft(nullptr);
		Treap* mres = merge(lt,rl);
		root->setLeft(mres);
	}

	return root;
}

Treap* remove_element(Treap* root, Treap* node){
	Treap* cur = root;
	Treap* merged = merge(node->left,node->right);
	Treap* parent = node->parent;

	// printf("%p %p %p\n",root,node,parent);

	if(root == node){
		delete root;
		if(merged){
			merged->parent = nullptr;
		}
		return merged;
	}
	else{
		if(parent->left == node)
			parent->setLeft(merged);
		else
			parent->setRight(merged);

		Treap* cur = parent;
		parent = parent->parent;
		while(parent){
			if(parent->left == cur)
				parent->setLeft(cur);
			else
				parent->setRight(cur);
			cur = parent;
			parent = parent->parent;
		}

		delete node;

		return root;
	}
}

void inorder(Treap* node){
	if(!node)
		return;
	inorder(node->left);
	printf("%d(%d) ",node->value,node->count);
	inorder(node->right);
}

void preorder(Treap* node){
	if(!node)
		return;

	int lval = (node->left) ? node->left->value  : -1;
	int rval = (node->right)? node->right->value : -1;

	printf("%3d %3d %3d\n",node->value,lval,rval);
	preorder(node->left);
	preorder(node->right);
}

void get_input(){
	scanf("%d", &N);
	for(int i=0; i<N; ++i){
		scanf("%d", &A[i]);
	}
}

void solve(){
	Treap* root = new Treap(1);
	for(int i=2; i<=N; ++i)
		root = root->insert(new Treap(i));

	vector<int> ans;

	// inorder(root);	printf("\n");
	// preorder(root);

	for(int i=N-1; i>=0; --i){
		Treap* kth = root->find_kth_element(root->count - A[i]);
		ans.push_back(kth->value);
		root = remove_element(root, kth);
		// inorder(root);	printf("\n");
		// preorder(root);
	}
	reverse(ans.begin(),ans.end());

	for(auto a:ans)
		printf("%d ",a);
	printf("\n");
}

int main(int argc, char** argv){
	int T;
	scanf("%d", &T);
	for(int i=0; i<T; ++i){
		get_input();
		solve();
	}

	// N = 16;

	// Treap* root = new Treap(1);
	// for(int i=2; i<=N; ++i){
	// 	Treap* node = new Treap(i);
	// 	root = root->insert(node);
	// 	printf("root: %d\n",root->value);
	// }

	// pair<Treap*,Treap*> kth;
	// for(int i=1; i<=16; ++i){
	// 	kth = root->find_kth_element(i,nullptr);
	// 	printf("%dth: %d\n",i,kth.first->value);
	// }

	// inorder(root);
	// printf("\n");

	// preorder(root);

	// for(int i=0; i<5; ++i){
	// 	printf("root:%d\n", root->value);
	// 	root = remove_element(root, root, nullptr);
	// 	printf("after remove root (%d): ", root->value);
	// 	inorder(root);
	// 	printf("\n");
	// }
}