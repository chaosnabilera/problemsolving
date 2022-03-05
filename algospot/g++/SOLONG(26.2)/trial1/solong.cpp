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

using namespace std;

const int BIGNUM = 987654321;

int N,M;
vector<pair<int,string>> Dict;
vector<string> Input;

struct Trie{
	Trie(Trie* _parent) : parent(_parent) {
		max_freq = 0;
		length = (parent == nullptr) ? 0 : parent->length + 1;
		num_keystroke = length;
		memset(child,0,sizeof(child));
	}
	~Trie(){
		for(int i=0; i<26; ++i)
			if(child[i])
				delete child[i];
	}
	int max_freq;
	int length;
	int num_keystroke;
	Trie* parent;
	Trie* child[26];
};

void insert_trie(Trie* node, int di, int si, int numk){
	int freq = Dict[di].first;
	string& word = Dict[di].second;

	// printf("word:%s freq:%d node->max_freq:%d node->length:%d si:%d numk:%d\n", 
	// 	word.c_str(), freq, node->max_freq, node->length, si, numk);

	if(freq > node->max_freq){
		node->max_freq = freq;
		numk = min(numk, node->length+1);
	}

	if(si == word.size()){
		node->num_keystroke = min(node->num_keystroke, numk);
	}
	else{
		int ci = word[si] - 'A';
		if(node->child[ci] == nullptr){
			node->child[ci] = new Trie(node);
		}
		insert_trie(node->child[ci], di, si+1, numk);
	}	
}

int count_keystrokes(Trie* node, string& s, int si){
	if(si == s.size()){
		return node->num_keystroke;
	}
	else{
		int ci = s[si] - 'A';
		if(node->child[ci] == nullptr)
			return s.size();
		else
			return count_keystrokes(node->child[ci], s, si+1);
	}
}

void get_input(){
	char word[11];
	int freq;

	scanf("%d %d", &N, &M);

	Dict.clear();
	Dict.reserve(N);
	for(int i=0; i<N; ++i){
		scanf("%s %d", word, &freq);
		Dict.push_back(make_pair(freq,word));
	}

	Input.clear();
	Input.reserve(M);
	for(int i=0; i<M; ++i){
		scanf("%s", word);
		Input.push_back(word);
	}
}

bool custom_compare(pair<int,string>& a, pair<int,string>& b){
	if(a.first == b.first){
		return a.second < b.second;
	}
	return a.first > b.first;
}

void solve(){
	Trie* trie_root = new Trie(nullptr);
	trie_root->max_freq = BIGNUM; // no blank-tab

	sort(Dict.begin(),Dict.end(),custom_compare);
	for(int di=0; di<Dict.size(); ++di){
		insert_trie(trie_root, di, 0, Dict[di].second.size());
	}

	int count = 0;
	for(int i=0; i<M; ++i){
		int cur = count_keystrokes(trie_root, Input[i], 0);
		// printf("%s %d\n",Input[i].c_str(),cur);
		count += cur;
		++count;
	}
	--count;

	printf("%d\n", count);
}

int main(int argc, char** argv){
	int T;
	scanf("%d", &T);
	for(int i=0; i<T; ++i){
		get_input();
		solve();
	}
}