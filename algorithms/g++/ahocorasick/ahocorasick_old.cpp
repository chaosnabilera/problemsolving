#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <queue>
#include <utility>

#define ALPHABETS 26

struct TrieNode{
	TrieNode* children[ALPHABETS];
	int terminal_id;
	TrieNode* fail;
	std::vector<int> output;

	TrieNode() : terminal_id(-1){
		memset(children, 0, sizeof(children));
		fail = nullptr;
	}
	~TrieNode(){
		for(int i=0; i<ALPHABETS; ++i){
			if(children[i]) delete children[i];
		}
	}
	inline int toidx(const char c){
		return c-'a';
	}
	void insert(const char* key, int id){
		if(*key == 0){
			terminal_id = id;
		}
		else{
			int keyidx = toidx(*key);
			if(children[keyidx] == nullptr){
				children[keyidx] = new TrieNode();
			}
			children[keyidx]->insert(key+1, id);
		}
	}
	int find(const char* key){
		if(*key == 0) return terminal_id;
		int keyidx = toidx(*key);
		if(children[keyidx] == NULL) return -1;
		return children[keyidx]->find(key+1);
	}
};

void computeFailFunc(TrieNode* trie_root){
	std::queue<TrieNode*> q;
	trie_root->fail = trie_root;
	q.push(trie_root);

	while(!q.empty()){
		TrieNode* cur = q.front(); q.pop();

		for(int c = 0; c < ALPHABETS; ++c){
			TrieNode* child = cur->children[c];
			if(!child) continue;
			if(cur == trie_root){ // special case. because cur == cur->fail
				child->fail = trie_root;
			}
			else{
				TrieNode* fnode = cur->fail; // This assumes that cur != cur->fail
				while(fnode != trie_root && fnode->children[c] == NULL){
					fnode = fnode->fail;
				}
				if(fnode->children[c]) fnode = fnode->children[c];
				child->fail = fnode;
			}

			child->output = child->fail->output;
			if(child->terminal_id != -1)
				child->output.push_back(child->terminal_id);
			q.push(child);
		}
	}
}

std::vector<std::pair<int,int>>* ahoCorasick(const char* s, int slen, TrieNode* trie_root){
	std::vector<std::pair<int,int>>* pret = new std::vector<std::pair<int,int>>();
	std::vector<std::pair<int,int>>& ret = *pret;
	TrieNode* state = trie_root;

	for(int i=0; i<slen; ++i){
		int ci = s[i] - 'a';
		while(state != trie_root && state->children[ci] == NULL)
			state = state->fail;
		if(state->children[ci])
			state = state->children[ci];
		for(int j=0; j<state->output.size(); ++j){
			ret.push_back(std::make_pair(i, state->output[j]));
		}
	}
	return pret;
}

int main(){
	TrieNode trie;
	std::vector<std::string> str = {"god","goddamn","gogogo","what","whatthe","whatthefuck","shit","shithitsthefan","itsthefan","thefan"};
	
	for(int i=0; i<str.size(); ++i){
		trie.insert(str[i].c_str(),i);
	}
	computeFailFunc(&trie);

	const char* haystack = "eqwrljkgogogoddamnwhatthefuckshithitsthefanafdsjlafdthefan";
	int haystack_len = strlen(haystack);

	std::vector<std::pair<int,int>>* pres = ahoCorasick(haystack, haystack_len, &trie);

	for(auto it=pres->begin(); it != pres->end(); ++it){
		printf("%d %s\n", it->first, str[it->second].c_str());
	}
}