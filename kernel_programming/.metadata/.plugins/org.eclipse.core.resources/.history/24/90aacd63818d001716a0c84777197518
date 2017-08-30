/* focalpoint LKIKI */
/* Lab12: Syscalls Lab */
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/unistd.h>
#include <linux/semaphore.h>
#include <linux/mm.h>
#include <linux/highmem.h>
#include <asm/unistd.h>

#define DRIVER_AUTHOR "focalpoint"
#define DRIVER_DESC   "Lab12"

MODULE_LICENSE("GPL");           // Get rid of taint message by declaring code as GPL.

/*  Or with defines, like this: */
MODULE_AUTHOR(DRIVER_AUTHOR);    // Who wrote this module?
MODULE_DESCRIPTION(DRIVER_DESC); // What does this module do?

int init(void);
void cleanup(void);
//Had to change the datatype of _addr from the content
int set_page_rw(unsigned long int _addr)
{
	unsigned int level;
	pte_t *pte = lookup_address(_addr, &level);
	if(pte->pte &~ _PAGE_RW) pte->pte |= _PAGE_RW;
	return 0;
}
//had to change sys_call_table from void** to unsigned long *
unsigned long *sys_call_table;

asmlinkage int (*original_call) (const char*);

//asmlinkage long sys_unlink(const char *pathname)
asmlinkage long my_sys_unlink(const char *pathname)
{
   printk("unlinker: File unlink attempted and stopped!\n");
   //return original_call(pathname);
   return -1;
}

int init_module()
{
    // sys_call_table address in System.map
	//[root@localhost boot]# cat /boot/System.map-3.10.0-514.el7.x86_64 | grep sys_call_table
	//ffffffff816a0800 RW sys_call_table
	//ffffffff816a7400 R ia32_sys_call_table

	/* get address of sys_call_table */
	sys_call_table = (unsigned long *) 0xffffffff816a0800;
		//Make sure to cast the address appropriately
	/* change page attributes to RW */
	set_page_rw(*sys_call_table);
		//argument of sys_call_table needs to be dereferenced
	
	/* replace function call address of unlink */
	original_call = sys_call_table[__NR_unlink];		//store original
	sys_call_table[__NR_unlink] = my_sys_unlink;		//replace it
    return 0;
}
		//The sys_call_table[] lines will have cast warnings.  Ignore them.
void cleanup_module()
{
   sys_call_table[__NR_unlink] = original_call;
}
