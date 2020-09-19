/*
 * Privileged Cache Clearing Module (x86_64)
 * Created By Schrodinger ZHU <i@zhuyi.fan>
 * Date: Sept. 19, 2020
 */

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/smp.h>
#include <asm/cacheflush.h>
#include <asm/tlbflush.h>

#define DRIVER_AUTHOR "Schrodinger ZHU <i@zhuyi.fan>"
#define DRIVER_DESC   "Privileged Cache Clearing Module (x86_64)"

/*
 * Module Inplementation (__flush_all)
 * ---------------------------------------------------------
 * Use core APIs and privileged inline assemblies to re-init the CPU status.
 * `flush_tlb_all` is a low-level Core API of Linux Kernel.
 * `wbinvd` runs only in ring 0 kernel mode.
 */
void __flush_all ( void* __omitted ) {
    __flush_tlb_all( ); // flush all TLB
    flush_cache_all( ); // flush all cache
    asm("wbinvd" ::: "memory"); // clear all internal and external cache
    printk(KERN_INFO "CPU %d cache and TLB cleared successfully.\n", smp_processor_id());
}

/*
 * Module Inplementation (init_module)
 * ---------------------------------------------------------
 * call `__flush_all` on all cpu.
 */
int init_module ( void ) {
    on_each_cpu( __flush_all, NULL, 1 );
    printk(KERN_INFO "All cache and TLB cleared successfully.\n");
    return 0;
}

/*
 * Module Inplementation (cleanup_module)
 * ---------------------------------------------------------
 * Simply log the unload information.
 */
void cleanup_module ( void ) {
    printk(KERN_INFO "clearup module unloaded.\n");
}

/*
 * Module Information
 * -----------------------------------------------------------
 * Licence and author information
 */
MODULE_LICENSE("GPL");
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
