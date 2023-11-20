# xv6-lottery-scheduler
Replace the current round robin scheduler in xv6 with a lottery scheduler.
The basic idea is : assign each running process a slice of the processor in proportion to the number of tickets it has. The more tickets a process has, the more it runs. Each time slice, a randomized lottery determines the winner of the lottery; that winning process is the one that runs for that time slice.
# Setting Tickets
