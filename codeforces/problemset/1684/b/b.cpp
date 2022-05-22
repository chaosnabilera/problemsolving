#include <iostream>

void solve(){
    int a,b,c;
    scanf("%d%d%d", &a, &b, &c);
    printf("%d %d %d\n",a+b+c,b+c,c);
}

int main(int argc, char** argv){
    int t;
    scanf("%d", &t);
    for(int i=0; i<t; ++i){
        solve();
    }
}