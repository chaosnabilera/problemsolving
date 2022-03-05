#include <iostream>
#include <string>
#include <cstring>

using namespace std;

char iQuad[0x1000];
int iQuadLen;

string rec_solve(int s){
	if(iQuad[s] == 'b')
		return "b";
	if(iQuad[s] == 'w')
		return "w";
	string lu = rec_solve(s+1);
	string ru = rec_solve(s+1+lu.size());
	string ld = rec_solve(s+1+lu.size()+ru.size());
	string rd = rec_solve(s+1+lu.size()+ru.size()+ld.size());

	return "x"+ld+rd+lu+ru;
}

void solve(){
	scanf("%s", iQuad);
	iQuadLen = strlen(iQuad);
	cout << rec_solve(0) << endl;
}

int main(int argc, char** argv){
	int T;
	scanf("%d",&T);
	for(int i=0; i<T; ++i){
		solve();
	}
}