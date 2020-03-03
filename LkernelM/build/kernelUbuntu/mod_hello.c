/* mod_hello.c */
#include <linux/init.h> /* needed by the macros module_init and exit */
#include <linux/module.h> /* needed by all modules */
#include <linux/kernel.h> /* needed by KERN_ definition*/
/* passing parameter to module */
static int debug_enable = 0; /* default is disabled/off */
module_param(debug_enable, int, 0); /* macro defined in module.h)*/
MODULE_PARM_DESC(debug_enable, "Enable debug mode");

static int __init hello_init(void)
{
    printk(KERN_ALERT "Hello from kernel world - debug mode is %s\n",
            debug_enable ? "enabled" : "disabled");
    return 0; /*0 for success, negative for failure*/
}

static void __exit hello_cleanup(void)
{
    printk(KERN_ALERT "Goodbye from kernel world\n");
}

module_init(hello_init);/*macro to execute module's initialize routine */
module_exit(hello_cleanup);/*macro to execute module's exit routine */

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Cony Yang");
MODULE_DESCRIPTION("Simple Hello Module ");
MODULE_VERSION("V1");