#include <random>
#include <limits>
#include <utility>

template <typename T>
class RNG32{
public:
	RNG32<T>(T beg = std::numeric_limits<T>::min(), T end = std::numeric_limits<T>::max()){
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

template <typename T>
class TNode {
public:
	// variables
	T key;
	unsigned int priority;
	unsigned int size;
	TNode<T>* left;
	TNode<T>* right;

	// methods
	TNode<T>(T _key, unsigned int _priority){
		key = _key;
		priority = _priority;
		size = 1;
		left = nullptr;
		right = nullptr;
	}
	void setLeft(TNode<T>* newleft){
		left = newleft;
		recalculateSize();
	}
	void setRight(TNode<T>* newright){
		right = newright;
		recalculateSize();
	}
	void recalculateSize(){
		size = 1;
		if(left) size += left->size;
		if(right) size += right->size;
	}
};

#define TNODEPAIR std::pair<TNode<T>*,TNode<T>*>

template <typename T>
class Treap{
public:
	Treap<T>() {
		treap_root = nullptr;
	};
	~Treap<T>() {};
	void insert(T key){
		TNode<T>* newnode = new TNode<T>(key, rng());
		treap_root = insert_node(treap_root, newnode);
	}
	void inorder_traverse(){
		printf("inorder traverse: ");
		recursive_inorder_traverse(treap_root);
		printf("\n");
	}
	bool find(T key){
		return recursive_find(treap_root, key);
	}
	void erase(T key){ // this doesn't care whether key actually exists or not
		treap_root = recursive_erase(treap_root, key);
	}
	unsigned int size(){
		if(!treap_root) return 0;
		return treap_root->size;
	}
	T kth(unsigned int k){
		return recursive_kth(treap_root, k)->key;
	}
	unsigned int count_less_than(T key){
		return recursive_count_less_than(treap_root, key);
	}
	unsigned int count_more_than(T key){
		return recursive_count_more_than(treap_root, key);
	}
private:
	TNode<T>* treap_root;
	RNG32<unsigned int> rng;
	TNODEPAIR split(TNode<T>* root, T pivot_key){
		if(root == nullptr) return TNODEPAIR(nullptr,nullptr);
		if(root->key < pivot_key){
			TNODEPAIR right_split = split(root->right, pivot_key);
			root->setRight(right_split.first);
			return TNODEPAIR(root, right_split.second);
		}
		else{
			TNODEPAIR left_split = split(root->left, pivot_key);
			root->setLeft(left_split.second);
			return TNODEPAIR(left_split.first, root);
		}
	}
	TNode<T>* insert_node(TNode<T>* root, TNode<T>* node){
		// case 1 : root does not exist
		if(!root) return node;

		// case 2 : root should change to node
		if(root->priority < node->priority){
			TNODEPAIR splitted = split(root, node->key);
			node->setLeft(splitted.first);
			node->setRight(splitted.second);
			return node;
		}
		// case 3 : node should be inserted either left or right
		if(node->key < root->key){
			root->setLeft(insert_node(root->left, node));
		}
		else{
			root->setRight(insert_node(root->right, node));
		}
		return root;
	}
	bool recursive_find(TNode<T>* root, T key){
		if (!root) return false;

		if(root->key == key){
			return true;
		}
		else{
			if(key < root->key){
				return recursive_find(root->left, key);
			}
			else{
				return recursive_find(root->right, key);
			}
		}
	}
	// note: max_key(less) < min_key(more)
	TNode<T>* merge(TNode<T>* less, TNode<T>* more){
		if(less == nullptr) return more;
		if(more == nullptr) return less;

		if(less->priority < more->priority){
			more->setLeft(merge(less,more->left));
			return more;
		}
		else{
			less->setRight(merge(less->right,more));
			return less;
		}
	}
	TNode<T>* recursive_erase(TNode<T>* root, T key){
		if(!root) return root;

		if(root->key == key){
			TNode<T>* ret = merge(root->left, root->right);
			delete root;
			return ret;
		}

		if(key < root->key){
			root->setLeft(recursive_erase(root->left, key));
		}
		else{
			root->setRight(recursive_erase(root->right, key));
		}
		return root;
	}
	TNode<T>* recursive_kth(TNode<T>* root, unsigned int k){
		unsigned int   left_size = 0;
		if(root->left) left_size = root->left->size; 
		if(k <= left_size) return recursive_kth(root->left, k);
		if(k == left_size+1) return root;
		return recursive_kth(root->right, k-left_size-1);
	}
	unsigned int recursive_count_less_than(TNode<T>* root, T key){
		if(!root) return 0;
		if(root->key >= key){
			return recursive_count_less_than(root->left, key);
		}
		else{
			unsigned int left_size = (root->left) ? root->left->size : 0;
			return left_size + 1 + recursive_count_less_than(root->right, key);
		}
	}
	unsigned int recursive_count_more_than(TNode<T>* root, T key){
		if(!root) return 0;
		if(root->key <= key){
			return recursive_count_more_than(root->right, key);
		}
		else{
			unsigned int right_size = (root->right) ? root->right->size : 0;
			return right_size + 1 + recursive_count_more_than(root->left, key);
		}
	}

	void recursive_inorder_traverse(TNode<T>* node){
		if(!node) return;
		recursive_inorder_traverse(node->left);
		printf("%d ", node->key);
		recursive_inorder_traverse(node->right);
	}
};

int main(int argc, char** argv){
	Treap<int> treap;
	int* rand_nums = new int[10];
	RNG32<int> irng(-20,20);

	printf("generated random numbers:");
	for(int i=0; i<10; ++i){
		rand_nums[i] = irng();
		printf(" %d", rand_nums[i]);
		treap.insert(rand_nums[i]);
	}
	printf("\n");

	treap.inorder_traverse();

	for(int i=-20; i<=20; ++i){
		if(treap.find(i)){
			printf("%d exist\n", i);
		}
	}
	printf("\n");

	for(int i=-20; i<=20; ++i){
		if(treap.find(i)){
			printf("After erasing %d:\n\t",i);
			treap.erase(i);
			treap.inorder_traverse();
		}
	}
	printf("\n");
}