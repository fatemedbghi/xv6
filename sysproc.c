#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

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
  return myproc()->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
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
    if(myproc()->killed){
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
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

int
sys_reverse_number(void)
{
  int num;
  asm ("movl %%edi, %0;"
                    : "=r"(num)
                    :
                    : "%edi");
  return reverse_number(num);
}

int
sys_get_children(void)
{
  int pid;
  if (argint(0, &pid) < 0)
      return -1;
  return get_children(pid);
}

void
sys_trace_syscalls(void)
{
  int  n;
  struct proc * p = myproc();
  if(p->pid == 2)
  {
    set_trace_state(1);
    while(1)
    {
      acquire(&tickslock);
      int ticks0;
      ticks0 = ticks;
      if(get_trace_state() == 1)
      {
        while(ticks - ticks0 < 500){
          if(myproc()->killed){
            release(&tickslock);
          }
          sleep(&ticks, &tickslock);
        }
        trace_syscalls(1);
      }
      release(&tickslock);
    }
  }
  else
  {
    if (argint(0, &n) < 0)
    {
        return;
    }
    set_trace_state(n);
  }
}

void
sys_change_line(void)
{

}

void
sys_set_ticket(void)
{

}

void
sys_set_bjf_param_process(void)
{

}

void
sys_set_bjf_param_system(void)
{

}

void
sys_print_info(void)
{

}
