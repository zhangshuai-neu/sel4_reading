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

#include <config.h>
#include <arch/model/statedata.h>
#include <plat/machine.h>

#ifdef CONFIG_KERNEL_MCS
#include <mode/util.h>

static inline CONST time_t getKernelWcetUs(void)
{
    return  10u;
}

static inline PURE ticks_t usToTicks(time_t us)
{
    assert(x86KStscMhz > 0);
    return us * x86KStscMhz;
}

static inline PURE time_t getMaxUsToTicks(void)
{
    return div64(UINT64_MAX, x86KStscMhz);
}

static inline PURE ticks_t getTimerPrecision(void)
{
    return usToTicks(1u);
}

static inline void ackDeadlineIRQ(void)
{
}

static inline ticks_t getCurrentTime(void)
{
    return x86_rdtsc();
}

static inline CONST ticks_t getMaxTicksToUs(void)
{
    return UINT64_MAX;
}

static inline PURE time_t ticksToUs(ticks_t ticks)
{
    return div64(ticks, x86KStscMhz);
}

static inline void setDeadline(ticks_t deadline)
{
    assert(deadline > NODE_STATE(ksCurTime));
    if (likely(x86KSapicRatio == 0)) {
        x86_wrmsr(IA32_TSC_DEADLINE_MSR, deadline);
    } else {
        /* convert deadline from tscKhz to apic khz */
        deadline -= getCurrentTime();
        apic_write_reg(APIC_TIMER_COUNT, div64(deadline, x86KSapicRatio));
    }
}
#else
static inline void resetTimer(void)
{
    /* nothing to do */
}
#endif /* CONFIG_KERNEL_MCS */


BOOT_CODE uint32_t tsc_init(void);

#endif /* __ARCH_MACHINE_TIMER_H */
