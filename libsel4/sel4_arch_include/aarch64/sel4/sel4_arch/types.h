/*
 * Copyright 2020, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef __LIBSEL4_SEL4_SEL4_ARCH_TYPES_H_
#define __LIBSEL4_SEL4_SEL4_ARCH_TYPES_H_

#include <sel4/simple_types.h>

typedef seL4_Uint64 seL4_Word;
typedef seL4_Word seL4_CPtr;
typedef seL4_Word seL4_NodeId;
typedef seL4_Word seL4_PAddr;
typedef seL4_Word seL4_Domain;

typedef seL4_CPtr seL4_ARM_PageUpperDirectory;
typedef seL4_CPtr seL4_ARM_PageGlobalDirectory;
/* whether the VSpace refers to a PageUpperDirectory or PageGlobalDirectory directly
 * depends on the physical address size */
typedef seL4_CPtr seL4_ARM_VSpace;

typedef struct seL4_UserContext_ {
    /* frame registers */
    seL4_Word pc, sp, spsr, x0, x1, x2, x3, x4, x5, x6, x7, x8, x16, x17, x18, x29, x30;
    /* other integer registers */
    seL4_Word x9, x10, x11, x12, x13, x14, x15, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28;
    /* Thread ID registers */
    seL4_Word tpidr_el0, tpidrro_el0;
} seL4_UserContext;

#endif /* __LIBSEL4_SEL4_SEL4_ARCH_TYPES_H_ */
