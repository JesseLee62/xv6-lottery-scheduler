#include "types.h"
#include "x86.h"
#include "defs.h"
#include "param.h"
#include "mmu.h"
#include "proc.h"
#include "sysfunc.h"
#include "pstat.h"

extern struct {
  struct spinlock lock;
  struct proc proc[NPROC];
} ptable;

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return proc->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = proc->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;
  
  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(proc->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since boot.
int
sys_uptime(void)
{
  uint xticks;
  
  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

// ADD: sys_getpinfo
int 
sys_getpinfo(void){
    struct pstat *ps;
    if (argptr(0, (void*)&ps, sizeof(struct pstat)) < 0 || ps == NULL) {
        return -1;
    }
    
    // Ensure mutual exclusion to access the process table
    acquire(&ptable.lock);

    // Fill in ps with process statistics
    int i;
    for(i = 0; i < NPROC; i++){
      
      // Get a reference to the current process
      struct proc *curproc = &ptable.proc[i];

      // inuse
      if (curproc->state == UNUSED){
        ps->inuse[i] = 0;
      }else{
        ps->inuse[i] = 1;
        ps->tickets[i] = curproc->tickets;
        ps->pid[i] = curproc->pid;
        ps->ticks[i] = curproc->ticks;
      }
    }
    // Release the lock and return success
    release(&ptable.lock);

    return 0;
}

// ADD: sys_settickets
int 
sys_settickets(void) {
  	int n;
    if (argint(0, &n) < 0) {
        return -1;
    }
    
    if(n < 1){
        return -1;
    }
  	
    proc->tickets = n;	
	  //cprintf("set ti to: %d\n", proc->tickets);
    return 0;
}