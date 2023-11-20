# xv6-lottery-scheduler
Replace the round robin scheduler in xv6 with a lottery scheduler.
The basic idea is : assign each running process a slice of the processor in proportion to the number of tickets it has. The more tickets a process has, the more it runs. Each time slice, a randomized lottery determines the winner of the lottery; that winning process is the one that runs for that time slice.
## Setting Tickets
Implement a new system call to set the number of tickets. The prototype of the system call is:
### int settickets(int)
This call sets the number of tickets of the calling process. <ins>By default, each process should get one ticket</ins>. By calling this routine a process can raise (reduce) the number of tickets it has, and thus receive a higher (lower) proportion of CPU cycles. This routine should return 0 if successful, and -1 otherwise (if, for example, the caller passes in a number less than one).
## Implementing Scheduler
Assign tickets to a process when it is created. Specifically, need to make sure a child process inherits the same number of tickets as its parent. Thus, if the parent has 10 tickets, and calls fork() to create a child process, the child should also get 10 tickets.
## Getting Process Statistics
Implement a second system call to gather some statistics about all the running process. The prototype for the second system call is 
### int getpinfo(struct pstat *) 
This routine returns some information about all running processes, including how many times each has been chosen to run and the process ID of each.
