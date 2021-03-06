/*
 * Copyright 2020, Data61, CSIRO (ABN 41 687 119 230)
 * Copyright 2015, 2016 Hesham Almatary <heshamelmatary@gmail.com>
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

#ifndef __ARCH_OBJECTTYPE_H
#define __ARCH_OBJECTTYPE_H

#ifdef HAVE_AUTOCONF
#include <autoconf.h>
#endif /* HAVE_AUTOCONF */

typedef enum _object {
    seL4_RISCV_4K_Page = seL4_ModeObjectTypeCount,
    seL4_RISCV_Mega_Page,
    seL4_RISCV_PageTableObject,
    seL4_ObjectTypeCount
} seL4_ArchObjectType;

typedef seL4_Word object_t;

#endif /* __ARCH_OBJECTTYPE_H */

