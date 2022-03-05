0xdeadbeef = 3735928559

~~~
...
random = rand();
...
scanf("%d", &key);
...
if( (key ^ random) == 0xdeadbeef )
~~~

rand() 에 대해 seed가 안되어 있어서 같은 값이 나온다

~~~
#include <stdio.h>

int main(){
        unsigned int random;
        random = rand();

        printf("%08X\n",random);
        return 0;
}
~~~

이렇게 컴파일 해보면 6B8B4567 가 나옴

~~~
>>> 0xDEADBEEF ^ 0x6B8B4567
3039230856
~~~

~~~
random@pwnable:~$ ./random
3039230856
Good!
Mommy, I thought libc random is unpredictable...
~~~

