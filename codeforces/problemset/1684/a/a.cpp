#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>

int solve(){
    char d[0x10];
    std::vector<int> digits;
    char sorted[0x10];
    int dlen = 0;

    scanf("%s", d);
    dlen = strlen(d);

    for(int i=0; i<dlen; ++i){
        digits.push_back(d[i]-'0');
    }

    std::sort(digits.begin(), digits.end());

    if(digits.size() == 2){
        return d[1] - '0';
    }
    else{
        return digits[0];
    }
}

int main(int argc, char** argv){
    int t;
    scanf("%d", &t);
    for(int i=0; i<t; ++i){
        printf("%d\n",solve());
    }
}