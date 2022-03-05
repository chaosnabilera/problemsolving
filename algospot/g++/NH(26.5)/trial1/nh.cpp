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

const int MODNUM = 10007;
int N,M;
vector<string> iWord;

struct Trie{
	Trie(Trie* _parent) : parent(_parent) {
		memset(child,0,sizeof(child));
		for(int n=0; n<=100; ++n)
			dp[n] = -1;
		is_end = false;
		ac = nullptr;
	}
	~Trie(){
		for(int c=0; c<26; ++c)
			if(child[c])
				delete child[c];
	}
	void insert(string& word, int i){
		if(i > 0 && state_str.size() == 0){
			state_str = word.substr(0,i);
		}
		if(i == word.size()){
			is_end = true;
			return;
		}
		int c = word[i]-'a';
		if(!child[c])
			child[c] = new Trie(this);
		child[c]->insert(word, i+1);
	}
	Trie* parent;
	Trie* child[26];
	Trie* ac;
	int dp[101];
	bool is_end;
	string state_str;
};

void construct_aho_corasick(Trie* trie_root){
	queue<Trie*> q;

	// initial condition
	trie_root->ac = nullptr;
	for(int c=0; c<26; ++c){
		if(trie_root->child[c]){
			trie_root->child[c]->ac = trie_root;
			q.push(trie_root->child[c]);
		}
	}

	while(!q.empty()){
		Trie* cur = q.front(); q.pop();
		for(int c=0; c<26; ++c){
			if(cur->child[c]){
				Trie* ac = cur->ac;
				while(ac != nullptr){
					if(ac->child[c]){
						cur->child[c]->ac = ac->child[c];
						break;
					}
					ac = ac->ac;
				}
				if(!ac){
					cur->child[c]->ac = trie_root;
				}
				q.push(cur->child[c]);
			}
		}
	}
}

int rec_calculate(Trie* node, int n){
	int* dp = node->dp;

	if(dp[n] != -1)
		return dp[n];

	if(node->is_end){
		dp[n] = 0;
	}
	else if(n == 0){
		dp[n] = 1;
	}
	else{
		dp[n] = 0;
		for(int c=0; c<26; ++c){
			Trie* p = node;
			Trie* child = p->child[c];
			Trie* trie_root = nullptr;
			while(!child){
				if(p->ac == nullptr){
					trie_root = p;
					break;
				}
				p = p->ac;
				child = p->child[c];
			}
			if(trie_root){
				dp[n] += rec_calculate(trie_root, n-1);
			}
			else{
				dp[n] += rec_calculate(child, n-1);
			}
			dp[n] %= MODNUM;
		}
	}

	return dp[n];
}

void get_input(){
	char w[11];
	scanf("%d %d", &N, &M);

	iWord.clear();
	iWord.reserve(M);
	for(int i=0; i<M; ++i){
		scanf("%s", w);
		iWord.push_back(w);
	}
}

bool is_substr(string& a, string& b){
	return a.find(b) != string::npos;
}

void print_ac(Trie* node){
	for(int c=0; c<26; ++c){
		if(node->child[c]){
			print_ac(node->child[c]);
		}
	}
	cout << node->state_str << " : ";
	if(node->ac)
		cout << node->ac->state_str << endl;
	else
		cout << "is root!" << endl;
}

void solve(){
	vector<string> Word;
	Trie* trie_root = new Trie(nullptr);

	// sanitize input
	for(int i=0; i<iWord.size(); ++i){
		bool no_substr = true;
		for(int j=0; j<iWord.size(); ++j){
			if(i == j)
				continue;
			if(is_substr(iWord[i],iWord[j])){
				no_substr = false;
				break;
			}
		}
		if(no_substr)
			Word.push_back(iWord[i]);
	}

	// for(auto w:Word)
	// 	cout << w << endl; 

	for(int i=0; i<Word.size(); ++i)
		trie_root->insert(Word[i],0);

	construct_aho_corasick(trie_root);

	int res = rec_calculate(trie_root, N);

	// print_ac(trie_root);

	printf("%d\n",res);
}

int main(int argc, char** argv){
	int T;

	scanf("%d", &T);
	for(int i=0; i<T; ++i){
		get_input();
		solve();
	}
}