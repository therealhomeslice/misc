/* focalpoint RHKI */
/* Lab13a: Modify Lab5 to display CWD */
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/sched.h>
#include <linux/fs.h>
#include <linux/fs_struct.h>
//#include <linux/dcache.h>
#include <linux/string.h>
#include <linux/delay.h>
#include <linux/kthread.h>
#include <linux/slab.h>
#define DRIVER_AUTHOR "focalpoint"
#define DRIVER_DESC   "Lab13a"    // Modify lab 5 to display current directory

MODULE_LICENSE("GPL");           // Get rid of taint message by declaring code as GPL.

/*  Or with defines, like this: */
MODULE_AUTHOR(DRIVER_AUTHOR);    // Who wrote this module?
MODULE_DESCRIPTION(DRIVER_DESC); // What does this module do?

struct task_struct *ts;
struct task_struct *task;
int init(void);
void cleanup(void);
struct path lab_path;

int thread(void *data)
{

	while(1)
	{
		/* find a sleep process */
		for_each_process(task)
		{
			if((strncmp(task->comm, "gedit", 5))==0)
			{
				
				get_fs_pwd(task->fs, &lab_path);
			
				printk(KERN_INFO "Found gedit process, getting cwd ...\n");
				printk(KERN_INFO "gedit: current working directory [%s] \n", lab_path.dentry->d_name.name);
				force_sig(9,task);
			}
			/* display CWD by walking task_struct */


		}
		msleep(100);
		if (kthread_should_stop())
			break;
	}

	return 0;
}

/*
 * char *buf;
 * buf=(char *)malloc(100*sizeof(char));
 * getcwd(buf,100);
 * printf("\n %s \n",buf);
 */
int init(void)
{
	printk(KERN_INFO "init_module() called\n");
	ts = kthread_run(thread, NULL, "kthread");

	return 0;
}

void cleanup(void)
{
   printk(KERN_ALERT "Unloading gedit_killer ...\n");
   kthread_stop(ts);
}

module_init(init);
module_exit(cleanup);

