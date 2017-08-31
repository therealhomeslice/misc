#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/netfilter.h>
#include <linux/netfilter_ipv4.h>

static struct nf_hook_ops nfho;
#define NF_IP_PRE_ROUTING 0


unsigned int drop_func(unsigned int hooknum, struct sk_buff **skb, const struct net_device *in, const struct net_device *out, int (*okfn)(struct sk_buff *))
{
	printk(KERN_INFO "dropping le packet");
	return NF_DROP;
}

int init_module()
{
	/*hooks and ladders */
	printk(KERN_INFO "LOADING MODULE");
	


	nfho.hook = drop_func;
	nfho.hooknum = NF_IP_PRE_ROUTING;
	nfho.pf = PF_INET;

	nfho.priority = NF_IP_PRI_FIRST;
	nf_register_hook(&nfho);

	return 0;


}

/*do we really need to unload?
*/

void cleanup_module()
{
	nf_unregister_hook(&nfho);
	printk(KERN_INFO "UNLOADING MODULE");
}
