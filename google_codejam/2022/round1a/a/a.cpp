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

char buf1[0x200];
char buf2[0x200];

char* solve(char* s){
    memset(buf1,0,sizeof(buf1));
    memset(buf2,0,sizeof(buf2));
    strcpy(buf1, s);

    int islen = strlen(s);
    int h = 0;
    char* cur = buf1;
    char* nxt = buf2;
    for(int it=0; it<islen; ++it){
        int curlen = strlen(cur);

        memset(nxt,0,sizeof(buf1));
        for(int i=0; i<=h; ++i)
            nxt[i] = cur[i];
        for(int i=h; i<curlen; ++i)
            nxt[i+1] = cur[i];

        string a = cur;
        string b = nxt;

        if(b < a){
            swap(nxt, cur);
            h = h+2;
        }
        else{
            h++;
        }
    }

    return cur;
}

int main(int argc, char** argv){
    char line[0x100];
    int t;
    scanf("%d", &t);
    for(int i=0; i<t; ++i){
        scanf("%s",line);
        printf("Case #%d: %s\n",i+1,solve(line));
    }
}