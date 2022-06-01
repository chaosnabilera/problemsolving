#include <iostream>

int main(int argc, char** argv){
    int t, l1, r1, l2, r2;
    scanf("%d", &t);

    for(int i=0; i<t; ++i){
        scanf("%d%d%d%d", &l1, &r1, &l2, &r2);
        if(l1 > l2){
            std::swap(l1,l2);
            std::swap(r1,r2);
        }

        if(r1 < l2){
            printf("%d\n", l1+l2);
        }
        else{
            printf("%d\n", l2);
        }
    }
}