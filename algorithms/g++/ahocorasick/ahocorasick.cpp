#include <algorithm>
#include <array>
#include <cmath>
#include <cstring>
#include <deque>
#include <iostream>
#include <limits>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

#define ALPHABETS 26

struct TrieNode{
	TrieNode* children[ALPHABETS];
	int terminal_id;  // 여기가 끝이 아니면 0이상의 정수, 아니면 -1
	TrieNode* fail;
	vector<int> output;

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

void compute_fail_func(TrieNode* trie_root){
	queue<TrieNode*> q;
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
				// Fail node는 언제나 BFS depth상 지금보다 낮기 때문에 이미 Fail node는 다 만들어져 있음
				TrieNode* fnode = cur->fail; // This assumes that cur != cur->fail
				while(fnode != trie_root && fnode->children[c] == NULL){
					fnode = fnode->fail;
				}
				if(fnode->children[c]) fnode = fnode->children[c];
				child->fail = fnode;
			}

			// child가 terminal이 아니더라도 fail node가 terminal이면 여기가 끝인 답이 있는것임
			// 예: abcd와 bc가 있다고 했을때 abc까지 왔다면 abc는 끝까지 만들어진게 아니지만 
			//     내포된 bc가 terminal이므로 abc시점에서 bc는 output이 맞음
			//     abc의 fail node는 bc이고
			child->output = child->fail->output; 
			if(child->terminal_id != -1)
				child->output.push_back(child->terminal_id);
			q.push(child);
		}
	}
}

// 반드시 전에 compute_fail_func 이 불려야 함
void aho_corasick(const char* s, int slen, TrieNode* trie_root, vector<pair<int,int>>& find_result){
	find_result.clear(); // (index in s, matching 된 word의 id)
	TrieNode* state = trie_root;

	for(int i=0; i<slen; ++i){
		int ci = s[i] - 'a';
		while(state != trie_root && state->children[ci] == NULL)
			state = state->fail;
		if(state->children[ci])
			state = state->children[ci];
		for(int j=0; j<state->output.size(); ++j){
			find_result.push_back(make_pair(i, state->output[j]));
		}
	}
}

int main(){
	vector<pair<int,int>> find_result;
	TrieNode trie;
	vector<string> str = {"god","goddamn","gogogo","what","whatthe","whatthefuck","shit","shithitsthefan","itsthefan","thefan"};
	
	for(int i=0; i<str.size(); ++i){
		trie.insert(str[i].c_str(),i);
	}
	compute_fail_func(&trie);

	const char* haystack = "eqwrljkgogogoddamnwhatthefuckshithitsthefanafdsjlafdthefan";
	int haystack_len = strlen(haystack);

	aho_corasick(haystack, haystack_len, &trie, find_result);

	for(auto& p:find_result){
		int sidx = p.first;
		int terminal_id = p.second;
		printf("%d %s\n", sidx, str[terminal_id].c_str());
	}
}