# xv6-lottery-scheduler
Replace the round robin scheduler in xv6 with a lottery scheduler.
The basic idea is : assign each running process a slice of the processor in proportion to the number of tickets it has. The more tickets a process has, the more it runs. Each time slice, a randomized lottery determines the winner of the lottery; that winning process is the one that runs for that time slice.
## Setting Tickets
Implement a new system call to set the number of tickets. The prototype of the system call is:
### int settickets(int)
This call sets the number of tickets of the calling process. <ins>By default, each process should get one ticket</ins>. By calling this routine a process can raise (reduce) the number of tickets it has, and thus receive a higher (lower) proportion of CPU cycles. This routine should return 0 if successful, and -1 otherwise (if, for example, the caller passes in a number less than one).
