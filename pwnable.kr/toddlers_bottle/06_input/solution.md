* python으로 짜야함 (stage1_4.py, stage5.py 참조)
    * stage5는 누군가 접속해 줘야 해서 따로 만듦

* 마지막에 /bin/cat flag 하는데 python은 write할수 있는 directory에서 돌아야 해서 flag에 대한 symbolic link를 만들어야 한다

~~~
ln -s /home/input2/flag flag
...
input2@pwnable:/tmp/cn$ python stage1_4.py 60029
Welcome to pwnable.kr
Let's see if you know how to give input to program
Just give me correct inputs then you will get the flag :)
Stage 1 clear!
Stage 2 clear!
Stage 3 clear!
Stage 4 clear!
input2@pwnable:/tmp/cn$ Stage 5 clear!
Mommy! I learned how to pass various input in Linux :)
~~~

