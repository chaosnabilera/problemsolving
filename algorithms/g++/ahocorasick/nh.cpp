#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <queue>
#include <utility>

#define ALPHABETS 26

const int MOD = 10007;
int cache[101][1001];

struct TrieNode{
	TrieNode* children[ALPHABETS];
	TrieNode* next[ALPHABETS];
	int no;
	int terminal_id;
	TrieNode* fail;
	std::vector<int> output;

	TrieNode() : terminal_id(-1){
		memset(children, 0, sizeof(children));
		memset(next, 0, sizeof(next));
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

void computeTransition(TrieNode* cur, int& nodeCounter){
	cur->no = nodeCounter; ++nodeCounter;

	for(int c =0; c<ALPHABETS; ++c){
		TrieNode* next = cur;
		while(next != next->fail && next->children[c] == NULL)
			next = next->fail;
		if(next->children[c]) next = next->children[c];
		cur->next[c] = next;

		if(cur->children[c]){
			computeTransition(cur->children[c], nodeCounter);
		}
	}
}

int count(int length, TrieNode* state){
	if(state->output.size()) return 0;
	if(length == 0) return 1;
	int& ret = cache[length][state->no];
	if(ret != -1) return ret;
	ret = 0;

	for(int letter = 0; letter < ALPHABETS; ++letter){
		ret += count(length-1, state->next[letter]);
		ret %= MOD;
	}

	return ret;
}


void solve(char istr[][11], int M, int N){
	TrieNode trie;
	int nodecounter = 0;
	for(int m=0; m<M; ++m){
		trie.insert(istr[m],m);
	}
	computeFailFunc(&trie);
	computeTransition(&trie, nodecounter);

	for(int i=0; i<=N; ++i){
		for(int j=0; j<=nodecounter; ++j){
			cache[i][j] = -1;
		}
	}

	int ans = count(N, &trie);
	printf("%d\n", ans);
}

int main(int argc, char** argv){
	int C,N,M;
	char istr[100][11];

	scanf("%d", &C);
	for(int c=0; c<C; ++c){
		scanf("%d %d", &N, &M);
		for(int m=0; m<M; ++m){
			scanf("%s", istr[m]);
		}
		solve(istr, M, N);
	}
}