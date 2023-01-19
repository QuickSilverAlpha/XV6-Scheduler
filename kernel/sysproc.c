#include "kernel/syscall.h"
#include "kernel/types.h"
#include "kernel/x86.h"
#include "kernel/defs.h"
#include "kernel/date.h"
#include "kernel/param.h"
#include "kernel/memlayout.h"
#include "kernel/mmu.h"
#include "kernel/proc.h"
#include "kernel/rand.h"


int sys_fork(void) { return fork(); }

int sys_exit(void) {
  exit();
  return 0; // not reached
}

int sys_wait(void) { return wait(); }

int sys_kill(void) {
  int pid;

  if (argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int sys_getpid(void) { return proc->pid; }

int sys_sbrk(void) {
  int addr;
  int n;

  if (argint(0, &n) < 0)
    return -1;
  addr = proc->sz;
  if (growproc(n) < 0)
    return -1;
  return addr;
}

int sys_sleep(void) {
  int n;
  uint ticks0;

  if (argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while (ticks - ticks0 < n) {
    if (proc->killed) {
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int sys_uptime(void) {
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

int sys_nice(void) {
  // The priority for a process ranges from 0-39 with 0 being the highest priority and 39 the lowest
  int n;
  if (argint(0, &n) < 0)
    return -1;
  
  if (n < 0) { 
    return -1;
  }
  else if (n > 39) {
    proc->priority = 39;
    proc->tickets = 4;  
  }
  else {
    proc->priority = n;
    if(n==0){
      proc->tickets = 160;
    }
    else{
      proc->tickets = 160 - (4*n);
    }
  }
  return proc->priority;
}
  /*
  int pid, pr;
  if(argint(0, &pid) < 0)
    return -1;

  if(argint(1, &pr) < 0)
    return -1;

  if (pr < 0) { 
    return -1;
  }
  else if (pr > 39) {
    return nice(pid, 39); 
  }
  else {
    return nice(pid, pr);
    
  }
  */

  

int sys_schedmode(void){

  int mode;
 
  if (argint(0, &mode) < 0)
    return -1;

  if (mode == 0 || mode == 1) {
    int ret_mode = schedmod(mode);
    return ret_mode;
  }
  else {
    mode = 0;
    int ret_mode = schedmod(0);
    return ret_mode;
  }
  return -1; 
}

int sys_rettickets(void){
  return proc->tickets;
}

uint sys_retcpucount(void){
  return proc->count;
}