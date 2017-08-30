/* focalpoint LKI */
/* Lab10: Timing Management Lab */
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

#include <linux/delay.h>
#include <linux/timer.h>
#include <linux/sched.h>

#define DRIVER_AUTHOR "focalpoint"
#define DRIVER_DESC   "Lab10"

MODULE_LICENSE("GPL");           // Get rid of taint message by declaring code as GPL.

/*  Or with defines, like this: */
MODULE_AUTHOR(DRIVER_AUTHOR);    // Who wrote this module?
MODULE_DESCRIPTION(DRIVER_DESC); // What does this module do?

/* Global timer */
static struct timer_list my_timer;

int init(void);
void cleanup(void);

void my_timer_callback(unsigned long data)
{
	printk("extimer: my_timer_callback called\n");
}

int init(void)
{
	//unsigned long delay;

	printk(KERN_INFO "init_module() called\n");
	printk("extimer: delaying startup for 10 seconds\n");

	/* delay startup for 10 seconds */
	mdelay(10000);
	//m for milliseconds!  insmod on this will cause it to hang.
	printk("extimer: installing timer\n");

	/* install timer my_timer */
	init_timer(&my_timer);					
		//Initializes the timer with the internal clock

	printk("extimer: setting timer to fire callback in 20 seconds\n");

	/* add a timer to fire my_timer_callback in 20 seconds */
	my_timer.expires = jiffies + 20;		//Now + 20 seconds from now
	my_timer.data = 0;						//Start at 0 to count
	my_timer.function = my_timer_callback;	//The function to execute

	add_timer(&my_timer);					//start the timer!
	return 0;
}

void cleanup(void)
{
	/* remove timer */

	printk(KERN_ALERT "Unloading extimer ...\n");
	del_timer(&my_timer);					//Removes the timer
}

module_init(init);
module_exit(cleanup);

