* ARM asm을 보고 이해해야 하는 문제인듯?

~~~
In ARM state, the value of the PC is the address of the current instruction plus 8 bytes.

In Thumb state:

For B, BL, CBNZ, and CBZ instructions, the value of the PC is the address of the current instruction plus 4 bytes.
For all other instructions that use labels, the value of the PC is the address of the current instruction plus 4 bytes, with bit[1] of the result cleared to 0 to make it word-aligned.
~~~

~~~
The easiest way to check if an address is considered to be ARM or Thumb is to check the disassembly. If the instruction is 32 bits wide – it is ARM, if it is 16 bits wide it is Thumb.
~~~

~~~
BX Rm and BLX Rm derive the target state from bit[0] of Rm:

if bit[0] of Rm is 0, the processor changes to, or remains in, ARM state

if bit[0] of Rm is 1, the processor changes to, or remains in, Thumb state.
~~~

* asm을 보면 r0가 함수 리턴 값이다

### key1
* mov r3, pc
	* pc (program counter)를 r3에 넣는다
~~~
   0x00008cdc <+8>:	    mov	r3, pc
   0x00008ce0 <+12>:	mov	r0, r3
~~~

* instruction이 4byte wide이니 ARM state인듯?
* 이걸 보건대 리턴 값(=r0)은 0x8cdc + 0x8 = 0x8CE4이다

### key2
* push {r6}
	* r6 값을 stack에 push
* add r6, pc, $1
	* r6에 pc+1을 넣는다 (r6+pc+1이 아니다!)
	* 이때 pc = 0x00008cfc + 0x8 = 0x8d04
	* 그럼 r6에는 0x8d05가 들어간다
	* 1 더하는 이유가 이해가 안되었는데 보니까 BX일때 1이 있으면 Thumb state라는 뜻이 되는 것 같다
* bx r6
	* bx : branch indirect + ARM <-> Thumb (이 경우는 ARM모드였으니 Thumb으로 간다)
		* r6로 가라 (1을 제외하고 보는듯? 즉 0x8d04로 가라)
		* 0x8d04는 결국 mov r3,pc니까 결국 다음으로 넘어가는거다...
	* bl 은 분기하되 return address를 r14에 저장한다 라는 뜻
* .code 16
    * 여기서 부터는 16bit (thumb) 모드로 짜져 있다
* mov r3, pc
    * r3에 pc를 넣어라
    * thumb mode니까 pc = 0x00008d04 + 4 = 0x8d08이다
* add	r3, $0x4
    * r3에 4를 더해라
    * r3 = 0x8d08 + 4 = 0x8d0c
* push	{r3}
	* r3를 push 해라
* pop	{pc}
	* pc에다 pop 해라
	* 이러면 r3 = 0x8d0c로 가는건데 그게 그냥 아래의 pop {r6} 하는 부분임
* .code	32
	* 여기서 부터는 32bit (ARM) 모드다
* pop	{r6}
	* r6에 pop해라
* epilogue 보면 마지막에 r3 = 0x8d0c를 r0에 넣는다 즉 리턴값은 0x8d0c

### key3
* mov r3, lr
	* lr을 r3에 넣어라
	* lr은 r14, 즉 리턴 어드레스가 있는 곳이다. key3의 경우는 0x8d80

### 답
0x8ce4 + 0x8d0c + 0x8d80 = 0x1A770‬ = 108400