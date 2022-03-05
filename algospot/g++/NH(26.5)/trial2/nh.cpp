#include <algorithm>
#include <array>
#include <cmath>
#include <cstring>
#include <deque>
#include <iostream>
#include <limits>
#include <map>
#include <queue>
#include <random>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

#define ALPHABETS 26

struct TrieNode;

vector<TrieNode*> Nodes;

struct TrieNode{
	TrieNode() : terminal_id(-1), fail(nullptr) {
		memset(children, 0, sizeof(children));
		node_no = Nodes.size();
		Nodes.push_back(this);
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
	int terminal_id;  // 여기가 끝이 아니면 0이상의 정수, 아니면 -1
	TrieNode* fail;
	int node_no;
	TrieNode* children[ALPHABETS];
	vector<int> output;
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

const int MODNUM = 10007;
int N,M;
vector<string> Word;
TrieNode* Trie;
int DP[1000][101];

void get_input(){
	char line[0x10];

	Word.clear();
	scanf("%d%d",&N,&M);
	for(int i=0; i<M; ++i){
		scanf("%s",line);
		Word.push_back(line);
	}
}

int rec_solve(int node_no, int length){
	if(DP[node_no][length] != -1)
		return DP[node_no][length];

	int res = 0;

	if(length == 0){
		if(Nodes[node_no]->output.size() == 0)
			res = 1;
	}
	else{
		TrieNode* nxtnode = nullptr;
		for(int c=0; c<ALPHABETS; ++c){
			if(Nodes[node_no]->children[c])
				nxtnode = Nodes[node_no]->children[c];
			else{
				nxtnode = Nodes[node_no]->fail;
				while(nxtnode != Trie && nxtnode->children[c] == NULL)
					nxtnode = nxtnode->fail;
				if(nxtnode->children[c])
					nxtnode = nxtnode->children[c];
			}
			if(nxtnode->output.size())
				continue;

			res = (res + rec_solve(nxtnode->node_no, length-1)) % MODNUM;
		}
	}

	DP[node_no][length] = res;
	return res;
}

void solve(){
	Nodes.clear();

	// Create Trie
	Trie = new TrieNode();
	for(int i=0; i<Word.size(); ++i)
		Trie->insert(Word[i].c_str(), i);

	// Compute aho-corasick
	compute_fail_func(Trie);

	// do DP
	memset(DP,0xFF,sizeof(DP));
	printf("%d\n", rec_solve(0,N));

	delete Trie;
}

int main(int argc, char** argv){
	int c;
	scanf("%d", &c);
	for(int i=0; i<c; ++i){
		get_input();
		solve();
	}
}