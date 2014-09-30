Classical synchronization problems
==========

This folder contains the code for some classical synchronization problems.

Compile with:

  ````
   gcc -lpthread -o FILE FILE.c
 ```` 
 or
  ````
   LDFLAGS=-lpthread make FILE
 ```` 

* threads.c Simple framework for thread creation, down and up

* prodcons.c Producer and consumer problem, Tanenbaum.

* philosphers.c Philosophers problem, Tanenbaum.

* readwrite.c Readers and writers, Tanenbaum,.

#Author

Erwin Meza Vega <emezav@gmail.com>
