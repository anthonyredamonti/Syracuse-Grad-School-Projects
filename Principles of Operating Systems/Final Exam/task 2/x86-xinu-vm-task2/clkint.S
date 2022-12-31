/* clkint.s - _clkint */

#include <icu.s>
		.text
count2:  .word  2 # 
count1000:	.word	1000
		.globl	sltop
		.globl	clkint
		.globl  cl1
clkint:
		pushal
		cli
		movb	$EOI,%al
		outb	%al,$OCW1_2

		incl	ctr1000
		subw	$1,count1000
		ja	cl1
		incl	clktime				# one second has passed. Increment clktime
		movw	$1000,count1000		# reload count1000
		subw	$1,count2 			# subtract 1 from count2
		ja		cl1       			# if 2 seconds has not passed, do not call checkprio
		movw	$2,count2 			# 2 seconds has passed. reload count2
		call	checkprio 			# call checkprio
cl1:
		cmpl	$0,slnonempty	# if no sleeping processes,
		je	clpreem		#   skip to preemption check
		movl	sltop,%eax	# decrement key of first
		decl	(%eax)		#   sleeping process
		jg	clpreem		# must use jg for signed int
		call	wakeup		# if zero, call wakeup
clpreem:	decl	preempt		# decrement preemption counter
		jg	clret		# must use jg for signed int
		call	resched		# if preemption, call resched
clret:					# return from interrupt
		sti
		popal
		iret
