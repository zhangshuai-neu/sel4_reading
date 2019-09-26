/*
 * Copyright 2017, Data61
 * Commonwealth Scientific and Industrial Research Organisation (CSIRO)
 * ABN 41 687 119 230.
 *
 * This software may be distributed and modified according to the terms of
 * the BSD 2-Clause license. Note that NO WARRANTY is provided.
 * See "LICENSE_BSD2.txt" for details.
 *
 * @TAG(DATA61_BSD)
 */

#include <sel4/sel4.h>

/** Userland per-thread IPC buffer address **/
__thread seL4_IPCBuffer *__sel4_ipc_buffer;

/** Consider moving bootinfo into libsel4_startup */
seL4_BootInfo *bootinfo;

/** Consider moving seL4_InitBootInfo into libsel4_startup */
void seL4_InitBootInfo(seL4_BootInfo *bi)
{
    bootinfo = bi;
}

seL4_BootInfo *seL4_GetBootInfo()
{
    return bootinfo;
}
