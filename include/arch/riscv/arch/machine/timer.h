/*
 * Copyright 2017, Data61
 * Commonwealth Scientific and Industrial Research Organisation (CSIRO)
 * ABN 41 687 119 230.
 *
 * This software may be distributed and modified according to the terms of
 * the GNU General Public License version 2. Note that NO WARRANTY is provided.
 * See "LICENSE_GPLv2.txt" for details.
 *
 * @TAG(DATA61_GPL)
 */
#ifndef __ARCH_MACHINE_TIMER_H
#define __ARCH_MACHINE_TIMER_H

#ifdef CONFIG_KERNEL_MCS

#include <types.h>
#include <mode/util.h>
#include <arch/sbi.h>
#include <arch/machine/hardware.h>

/* The scheduler clock is greater than 1MHz */
#define TICKS_IN_US (TIMER_CLOCK_HZ / (US_IN_MS * MS_IN_S))

static inline CONST time_t getKernelWcetUs(void)
{
    /* Copied from x86_64. Hopefully it's an overestimate here. */
    return  10u;
}

static inline PURE ticks_t usToTicks(time_t us)
{
    return us * TICKS_IN_US;
}

static inline PURE time_t ticksToUs(ticks_t ticks)
{
    return div64(ticks, TICKS_IN_US);
}

static inline PURE ticks_t getTimerPrecision(void)
{
    return usToTicks(1);
}

static inline CONST ticks_t getMaxTicksToUs(void)
{
    return UINT64_MAX / TICKS_IN_US;
}

static inline PURE time_t getMaxUsToTicks(void)
{
    return usToTicks(getMaxTicksToUs());
}

/* Read the current time from the timer. */
static inline ticks_t getCurrentTime(void)
{
    return riscv_read_time();
}

/* set the next deadline irq - deadline is absolute */
static inline void setDeadline(ticks_t deadline)
{
    assert(deadline > NODE_STATE(ksCurTime));
    /* Setting the timer acknowledges any existing IRQs */
    sbi_set_timer(deadline);
}

/* ack previous deadline irq */
static inline void ackDeadlineIRQ(void)
{
}

#endif /* CONFIG_KERNEL_MCS */

#endif /* __ARCH_MACHINE_TIMER_H */
