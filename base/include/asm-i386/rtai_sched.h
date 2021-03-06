/*
 * Copyright (C) 1999-2003 Paolo Mantegazza <mantegazza@aero.polimi.it>
 * Copyright (C) 2000      Stuart Hughes    <shughes@zentropix.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#ifndef _RTAI_ASM_I386_SCHED_H
#define _RTAI_ASM_I386_SCHED_H

#define rt_exchange_tasks(oldtask, newtask) \
	__asm__ __volatile__( \
	"pushl %%eax\n\t" \
	"pushl %%ebp\n\t" \
	"pushl %%edi\n\t" \
	"pushl %%esi\n\t" \
	"pushl %%edx\n\t" \
	"pushl %%ecx\n\t" \
	"pushl %%ebx\n\t" \
	"pushl $1f\n\t" \
	"movl (%%ecx), %%ebx\n\t" \
	"movl %%esp, (%%ebx)\n\t" \
	"movl (%%edx), %%esp\n\t" \
	"movl %%edx, (%%ecx)\n\t" \
	"ret\n\t" \
"1:	popl %%ebx\n\t \
	popl %%ecx\n\t \
	popl %%edx\n\t \
	popl %%esi\n\t \
	popl %%edi\n\t \
	popl %%ebp\n\t \
	popl %%eax\n\t" \
	: \
	: "c" (&oldtask), "d" (newtask) \
	);

#define init_arch_stack() \
do { \
	*--(task->stack) = data;		\
	*--(task->stack) = (int) rt_thread;	\
	*--(task->stack) = 0;			\
	*--(task->stack) = (int) rt_startup;	\
} while(0)

#define DEFINE_LINUX_CR0      static unsigned long linux_cr0;

#define DEFINE_LINUX_SMP_CR0  static unsigned long linux_smp_cr0[NR_RT_CPUS];

#define init_task_fpenv(task)  do { init_fpenv((task)->fpu_reg); } while(0)

static inline void *get_stack_pointer(void)
{
	void *sp;
	asm volatile ("movl %%esp, %0" : "=r" (sp));
	return sp;
}

#define RT_SET_RTAI_TRAP_HANDLER(x)  rt_set_rtai_trap_handler(x)

#define DO_TIMER_PROPER_OP()

#endif /* !_RTAI_ASM_I386_SCHED_H */
