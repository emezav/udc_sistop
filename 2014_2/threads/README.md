Thread samples
==========


This folder contains some POSIX thread samples

* thread0.c Rudimentary multi-threaded text editor.
This example creates two additional threads to (dummy) check for spelling and
(dummy) check for updates.

A real editor should read one character at time, not a complete line!

  ````
   gcc -lpthread -o thread0 thread0.c
 ```` 
 or
  ````
   LDFLAGS=-lpthread make thread0
 ```` 

* thread1.c Critical section. This program creates N threads, and each thread
increments a global variable. Without the use of a mutex, this should lead to 
a race condition.

* thread2.c Several threads using one single mutex. Only a thread can enter the
critical section at any time.

* thread3.c All threads should be locked on their own semaphores, main thread
randomly unlocks them.

#Author

Erwin Meza Vega <emezav@gmail.com>
