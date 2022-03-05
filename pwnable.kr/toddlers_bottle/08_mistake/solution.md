* 실행해 보면 do not bruteforce.... 하고는 그냥 아무것도 안나온다. 소스를 보면 input password라고 떠야 할것 같은데
* 자세히 보면 이 부분에 문제가 있다
~~~
if(fd=open("/home/mistake/password",O_RDONLY,0400) < 0){
                printf("can't open password %d\n", fd);
                return 0;
        }
~~~
* 사실 (fd=open("/home/mistake/password",O_RDONLY,0400)) < 0 을 의도했겠지만 연산자 우선순위 때문에 fd = (open("/home/mistake/password",O_RDONLY,0400) < 0) 되어서 fd에 0이 들어가 버렸다.
* 실제로 아무거나 10자를 치면 input password가 나오는것을 볼 수 있다
* pw_buf2 ^ 1 한게 pw_buf와 같으면 되는데 pw_buf와 pw_buf2를 우리가 모두 정할수 있으므로 ^1 했을때 같게 하면 된다

~~~
mistake@pwnable:~$ ./mistake
do not bruteforce...
bbbbbbbbbb
input password : cccccccccc
Password OK
Mommy, the operator priority always confuses me :(
~~~