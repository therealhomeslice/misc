/* focalpoint RHKI */
/* Lab13a: Modify Lab5 to display CWD */
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/sched.h>
#include <linux/fs.h>
#include <linux/fs_struct.h>
//#include <linux/dcache.h>

#include <linux/delay.h>
#include <linux/kthread.h>

#define DRIVER_AUTHOR "focalpoint"
#define DRIVER_DESC   "Lab13a"    // Modify lab 5 to display current directory

MODULE_LICENSE("GPL");           // Get rid of taint message by declaring code as GPL.

/*  Or with defines, like this: */
MODULE_AUTHOR(DRIVER_AUTHOR);    // Who wrote this module?
MODULE_DESCRIPTION(DRIVER_DESC); // What does this module do?

struct task_struct *ts;

int init(void);
void cleanup(void);

int thread(void *data)
{
	struct task_struct *task;
	int last_pid = 0;

	while(1)
	{
		/* find a sleep process */
		printk("Found sleep process, getting cwd ...\n");
		
		/* display CWD by walking task_struct */

		msleep(100);
		if (kthread_should_stop())
			break;
	}

	return 0;
}


int init(void)
{
	printk(KERN_INFO "init_module() called\n");
	ts = kthread_run(thread, NULL, "kthread");

	return 0;
}

void cleanup(void)
{
   printk(KERN_ALERT "Unloading sleep_killer ...\n");
   kthread_stop(ts);
}

module_init(init);
module_exit(cleanup);

