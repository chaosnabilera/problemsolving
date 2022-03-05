#include <stdio.h>
#include <stdlib.h>
 
int main(void)
{
    int *heap1;
    int *heap2;
    int *heap3;
 
    heap1 = (int *)malloc(sizeof(int) * 50);
    heap2 = (int *)malloc(sizeof(int) * 50);
 
    printf("heap1 address : %p\n", heap1);
    printf("heap2 address : %p\n", heap2);
 
    *heap2 = 1234;
    printf("heap2 number : %d\n", *heap2);
 
    printf("free heap2 :)\n");
    free(heap2);
 
    heap3 = (int *)malloc(sizeof(int) * 50);
    printf("heap3 address : %p\n", heap3);
    printf("heap3 value : %d\n", *heap3);
 
    return 0;
}


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
typedef struct{
    char namep[10];
    void (*print)(void*);
} test;
 
typedef struct{
    char name[128];
} string;
 
void printName(test *t)
{
    printf("%s\n", t->name);
}
 
void shell(void)
{
    printf("This is Shell\n");
}
 
int main(void)
{
    test *t1;
    string *s1;
 
    t1 = malloc(256);
 
    strcpy(t1->name, "DOG");
    t1->print = (void*)printName;
 
    t1->print(t1);
 
    free(t1);
 
    s1 = malloc(256);
 
    scanf("%128s", s1->name);
 
    t1->print(t1);
 
    return 0;
}