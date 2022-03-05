#include <iostream>
#include <vector>

class Node {
public:
	int val;
	std::vector<Node*> children;

	Node() {}

	Node(int _val) {
		val = _val;
	}

	Node(int _val, std::vector<Node*> _children) {
		val = _val;
		children = _children;
	}
};

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
 

class Codec {
public:
	// Encodes an n-ary tree to a binary tree.
	TreeNode* encode(Node* root) {
		if(!root) return nullptr;
		return rec_encode(root);
	}

	TreeNode* rec_encode(Node* node){
		TreeNode* treenode = new TreeNode(node->val);
		TreeNode child_ll(-1);
		TreeNode* ll_tail = &child_ll;

		for(Node* src_child : node->children){
			ll_tail->right = rec_encode(src_child);
			ll_tail = ll_tail->right;
		}
		treenode->left = child_ll.right;

		return treenode;
	}
	
	// Decodes your binary tree to an n-ary tree.
	Node* decode(TreeNode* root) {
		if(!root) return nullptr;
		return rec_decode(root);
	}

	Node* rec_decode(TreeNode* treenode){
		Node* node = new Node(treenode->val);
		TreeNode* child = treenode->left;
		while(child){
			node->children.push_back(rec_decode(child));
			child = child->right;
		}
		return node;
	}
};


int main(int argc, char** argv){

}