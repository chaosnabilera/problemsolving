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

int N,M;
TrieNode* Trie = nullptr;
vector<TrieNode*> W;
vector<string> S;

struct TrieNode{
	TrieNode() : freq(-1), wordlen(0), typecnt(-1) {
		memset(children, 0, sizeof(children));
		parent = nullptr;
	}
	~TrieNode(){
		for(int i=0; i<ALPHABETS; ++i){
			if(children[i]) delete children[i];
		}
	}
	inline int toidx(const char c){
		return c-'A';
	}
	void insert(const char* key, int fr, int wlen){
		if(*key == 0){
			freq = fr;
			wordlen = wlen;
			si = S.size()-1;
			// printf("whatthe? %d %d\n",freq,wordlen);
			W.push_back(this);
		}
		else{
			int keyidx = toidx(*key);
			if(children[keyidx] == nullptr){
				children[keyidx] = new TrieNode();
				children[keyidx]->wordlen = wordlen+1;
				children[keyidx]->parent = this;
			}
			children[keyidx]->insert(key+1, fr, wlen);
		}
	}

	TrieNode* find(const char* key){
		if(*key == 0) return this;
		int keyidx = toidx(*key);
		if(children[keyidx] == NULL) return nullptr;
		return children[keyidx]->find(key+1);
	}

	TrieNode* children[ALPHABETS];
	TrieNode* parent;
	int freq;
	int wordlen;
	int typecnt;
	int si;
};

void get_input(){
	char word[0x10];
	int freq;
	int wordlen;

	W.clear();
	S.clear();
	scanf("%d%d", &N, &M);
	Trie = new TrieNode();
	for(int i=0; i<N; ++i){
		scanf("%s%d",word,&freq);
		wordlen = strlen(word);
		S.push_back(word);
		Trie->insert(word,freq,wordlen);
	}
}

bool custom_compare(TrieNode* a, TrieNode* b){
	if(a->freq == b->freq){
		return S[a->si] < S[b->si];
	}
	return a->freq > b->freq;
}

TrieNode* find_ge_freq_parent(TrieNode* cur, TrieNode* target){
	if(cur == Trie)
		return nullptr;

	if(cur->freq >= target->freq)
		return cur;

	cur->freq = target->freq;
	return find_ge_freq_parent(cur->parent, target);
}

void solve(){
	char word[0x10];

	sort(W.begin(),W.end(),custom_compare);

	// for(auto w:W){
	// 	printf("%d %d\n",w->freq,w->typecnt);
	// }

	for(auto w:W){
		TrieNode* mfp = find_ge_freq_parent(w->parent,w);
		if(mfp == nullptr){
			w->typecnt = min(2,w->wordlen);
		}
		else{
			w->typecnt = min(mfp->wordlen + 2, w->wordlen);
		}
	}

	// for(auto w:W){
	// 	printf("%d %d %d\n",w->freq,w->wordlen,w->typecnt);
	// }

	int cnt = 0;
	for(int i=0; i<M; ++i){
		scanf("%s", word);
		TrieNode* res = Trie->find(word);
		int toadd = 0;
		if(res == nullptr || res->typecnt == -1){
			toadd = strlen(word);
		}
		else{
			toadd = res->typecnt;
		}

		// printf("%s %d\n",word,toadd);
		cnt += toadd;

		if(i != M-1)
			++cnt;
	}

	printf("%d\n", cnt);

	delete Trie;
	Trie = nullptr;
}

int main(int argc, char** argv){
	int c;
	scanf("%d", &c);
	for(int i=0; i<c; ++i){
		get_input();
		solve();
	}
}