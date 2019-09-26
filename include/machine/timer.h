/*
 * Copyright 2018, Data61
 * Commonwealth Scientific and Industrial Research Organisation (CSIRO)
 * ABN 41 687 119 230.
 *
 * This software may be distributed and modified according to the terms of
 * the GNU General Public License version 2. Note that NO WARRANTY is provided.
 * See "LICENSE_GPLv2.txt" for details.
 *
 * @TAG(DATA61_GPL)
 */
#ifndef __MACHINE_TIMER_H
#define __MACHINE_TIMER_H

#include <config.h>
#include <arch/machine/timer.h>

#ifdef CONFIG_KERNEL_MCS
#include <types.h>
#include <arch/linker.h>

/* Read the current time from the timer. */
/** MODIFIES: [*] */
static inline ticks_t getCurrentTime(void);
/* set the next deadline irq - deadline is absolute */
/** MODIFIES: [*] */
static inline void setDeadline(ticks_t deadline);
/* ack previous deadline irq */
/** MODIFIES: [*] */
static inline void ackDeadlineIRQ(void);

/* get the expected wcet of the kernel for this platform */
static PURE inline ticks_t getKernelWcetTicks(void)
{
    return usToTicks(getKernelWcetUs());
}
#else /* CONFIG_KERNEL_MCS */
static inline void resetTimer(void);
#endif /* !CONFIG_KERNEL_MCS */
#endif /* __MACHINE_TIMER_H */
