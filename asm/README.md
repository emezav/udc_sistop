Assembly samples
==========


This folder contains some assembly and C samples

* dup.c and duplicate.s: Assembly stack frame, call assembly from C. Compile and link together: 
  ````
   gcc -o dup dup.c duplicate.s
 ```` 
* exit.S: How to invoke the exit() syscall from assembly
* myfork.s and myfork_program.c : Assembly - c interaction, fork system call from assembly. Compile and link together:
 ````
    gcc -o myfork_program myfork_program.c myfork.s
 ````

#Notes

On 64 bit systems, compile with -m32 flag.


#Author

Erwin Meza Vega <emezav@gmail.com>
