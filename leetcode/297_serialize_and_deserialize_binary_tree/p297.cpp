#include <iostream>
#include <string>
#include <sstream>

//Definition for a binary tree node.
struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
 
class Codec {
public:
	// Encodes a tree to a single string.
	std::string serialize(TreeNode* root) {
		if(!root){
			return "";
		}
		std::stringstream ss;
		rec_serialize(root, ss);
		return ss.str();
	}

	void rec_serialize(TreeNode* node, std::stringstream& ss){
		char numbuf[0x10] = {0};
		sprintf(numbuf, "%05d", node->val);
		ss << numbuf;

		if(node->left){
			rec_serialize(node->left, ss);
		}
		else{
			ss << "#";
		}

		if(node->right){
			rec_serialize(node->right, ss);
		}
		else{
			ss << "#";
		}
	}

	// Decodes your encoded data to tree.
	TreeNode* deserialize(std::string data) {
		int di = 0;
		if(data.size() == 0){
			return nullptr;
		}
		return rec_deserialize(data, di);
	}

	TreeNode* rec_deserialize(std::string& data, int& di){
		TreeNode* ret = nullptr;
		if(data[di] == '#'){
			di += 1;
		}
		else{
			std::string valstr(&data[di], &data[di+5]);
			int val = std::stoi(valstr);
			// printf("%d\n",val);
			ret = new TreeNode(val);
			di += 5;
			
			ret->left = rec_deserialize(data, di);
			ret->right= rec_deserialize(data, di);
		}
		return ret;
	}
};

int main(int argc, char** argv){
	Codec cd;

	TreeNode n0(0);
	TreeNode n1(-1);
	TreeNode n2(2);
	TreeNode n3(-3);
	TreeNode n4(4);
	TreeNode n5(-5);

	n0.left = &n1;
	n1.left = &n2;
	n1.right= &n3;
	n3.right= &n4;
	n4.right= &n5;

	std::string r = cd.serialize(&n0);

	std::cout<< r << std::endl;

	cd.deserialize(r);
}