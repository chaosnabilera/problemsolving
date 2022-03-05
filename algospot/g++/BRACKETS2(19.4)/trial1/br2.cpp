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

char iLine[10001];
int lenLine;

void solve(){
	scanf("%s", iLine);
	lenLine = strlen(iLine);

	vector<char> stack;

	for(int i=0; i<lenLine; ++i){
		char c = iLine[i];
		if(c == '(' || c == '[' || c == '{'){
			stack.push_back(c);
		}
		else{
			if(stack.empty()){
				printf("NO\n");
				return;
			}
			else if((c == ')' && stack.back() == '(') || (c==']' && stack.back() == '[') || (c=='}' && stack.back() == '{')){
				stack.pop_back();
			}
			else{
				printf("NO\n");
				return;
			}
		}
	}

	if(stack.empty()){
		printf("YES\n");
	}
	else{
		printf("NO\n");
	}
}

int main(int argc, char** argv){
	int T;
	scanf("%d", &T);
	for(int i=0; i<T; ++i){
		solve();
	}
}