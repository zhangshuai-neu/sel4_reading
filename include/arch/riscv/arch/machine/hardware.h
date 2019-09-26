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

/*
 *
 * Copyright 2016, 2017 Hesham Almatary, Data61/CSIRO <hesham.almatary@data61.csiro.au>
 * Copyright 2015, 2016 Hesham Almatary <heshamelmatary@gmail.com>
 */

#ifndef __ARCH_MACHINE_HARDWARE_H
#define __ARCH_MACHINE_HARDWARE_H

#include <util.h>

#include <mode/hardware.h>

#ifndef __ASSEMBLER__

#include <config.h>
#include <linker.h>

#include <arch/types.h>
#include <sel4/sel4_arch/constants.h>

/* The highest valid physical address that can be indexed in the kernel window */
#define PADDR_TOP (KERNEL_BASE - PPTR_BASE + PADDR_BASE)
/* A contiguous region of physical address space at PADDR_LOAD is mapped
 * to KERNEL_ELF_BASE, and the size of this region is KDEV_PPTR-KERNEL_ELF_BASE.
 * PADDR_HIGH_TOP is the end of this physical address region. */
#define PADDR_HIGH_TOP (KDEV_PPTR - KERNEL_ELF_BASE + PADDR_LOAD)

/* Translates from a physical address and a value in the kernel image */
#define KERNEL_BASE_OFFSET (KERNEL_ELF_BASE - PADDR_LOAD)

/* Convert our values into general values expected by the common code */
#define kernelBase KERNEL_BASE
/* This is the top of the kernel window, not including the kernel image */
#define PPTR_TOP KERNEL_BASE
#define PPTR_USER_TOP seL4_UserTop
#define BASE_OFFSET (PPTR_BASE - PADDR_BASE)

#define PAGE_BITS seL4_PageBits

/* MMU RISC-V related definitions. See RISC-V manual priv-1.10 */

/* Extract the n-level PT index from a virtual address. This works for any
 * configured RISC-V system with CONFIG_PT_LEVEL (which can be 2 on Sv32,
 * 3 on Sv38, or 4 on Sv48)
 */
#define RISCV_GET_PT_INDEX(addr, n)  (((addr) >> (((PT_INDEX_BITS) * ((CONFIG_PT_LEVELS) - (n))) + seL4_PageBits)) & MASK(PT_INDEX_BITS))
#define RISCV_GET_LVL_PGSIZE_BITS(n) (((PT_INDEX_BITS) * (CONFIG_PT_LEVELS - (n))) + seL4_PageBits)
#define RISCV_GET_LVL_PGSIZE(n)      BIT(RISCV_GET_LVL_PGSIZE_BITS((n)))
/*
 * These values are defined in RISC-V priv-1.10 manual, they represent the
 * exception codes saved in scause register (by the hardware) on traps.
 */
enum vm_fault_type {
    RISCVInstructionMisaligned = 0,
    RISCVInstructionAccessFault = 1,
    RISCVInstructionIllegal = 2,
    RISCVBreakpoint = 3,
    /* reserved */
    RISCVLoadAccessFault = 5,
    RISCVAddressMisaligned = 6,
    RISCVStoreAccessFault = 7,
    RISCVEnvCall = 8,
    /* 9-11 reserved */
    RISCVInstructionPageFault = 12,
    RISCVLoadPageFault = 13,
    /* 14 - reserved */
    RISCVStorePageFault = 15
                          /* >= 16 reserved */
};
typedef uint32_t vm_fault_type_t;

enum frameSizeConstants {
    RISCVPageBits        = seL4_PageBits,
    RISCVMegaPageBits    = seL4_LargePageBits,
    RISCVGigaPageBits    = seL4_HugePageBits,
#if CONFIG_PT_LEVELS == 4
    RISCVTeraPageBits    = seL4_TeraPageBits
#endif
};

enum vm_page_size {
    RISCV_4K_Page,
    RISCV_Mega_Page,
    RISCV_Giga_Page,
    RISCV_Tera_Page
};
typedef uint32_t vm_page_size_t;

static inline unsigned int CONST pageBitsForSize(vm_page_size_t pagesize)
{
    switch (pagesize) {
    case RISCV_4K_Page:
        return RISCVPageBits;

    case RISCV_Mega_Page:
        return RISCVMegaPageBits;

#if CONFIG_PT_LEVELS > 2
    case RISCV_Giga_Page:
        return RISCVGigaPageBits;
#endif

#if CONFIG_PT_LEVELS == 4
    case RISCV_Tera_Page:
        return RISCVTeraPageBits;
#endif

    default:
        fail("Invalid page size");
    }
}
#endif /* __ASSEMBLER__ */

#define LOAD_S STRINGIFY(LOAD)
#define STORE_S STRINGIFY(STORE)

#endif /* !__ARCH_MACHINE_HARDWARE_H */
