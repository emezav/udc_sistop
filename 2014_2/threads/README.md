Thread samples
==========


This folder contains some POSIX thread samples

* thread0.c Rudimentary multi-threaded text editor.
This example creates two additional threads to (dummy) check for spelling and
(dummy) check for updates.

A real editor should read one character at time, not a complete line!

  ````
   gcc -lpthread -o thread0 thread0.o
 ```` 
 or
  ````
   LDFLAGS=-lpthread make thread0
 ```` 

* thread1.c Critical section. This program creates N threads

#Author

Erwin Meza Vega <emezav@gmail.com>
