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
#include <cmath>

using namespace std;

char iStr[10001];

bool solve(){
	char* p = iStr;
	vector<char> stack;
	while(*p){
		char c = *p;
		if(c == '(' || c == '{' || c == '['){
			stack.push_back(c);
		}
		else if(stack.empty()){
			return false;
		}
		else{
			if(c == ')'){
				if(stack.back() == '(')
					stack.pop_back();
				else
					return false;
			}
			else if(c == '}'){
				if(stack.back() == '{')
					stack.pop_back();
				else
					return false;
			}
			else if(c == ']'){
				if(stack.back() == '[')
					stack.pop_back();
				else
					return false;
			}
		}
		++p;
	}

	return stack.empty();
}

int main(int argc, char** argv){
	int c;
	scanf("%d", &c);
	for(int i=0; i<c; ++i){
		scanf("%s", iStr);
		if(solve())
			printf("YES\n");
		else
			printf("NO\n");
	}
}