
/*  
 * Simple Linux Kernel Module
 *    
*/

#include <linux/init.h>		/* Needed for macros */
#include <linux/kernel.h>	/* Needed for KERN_INFO */
#include <linux/module.h>	/* Needed by all modules */
#include <linux/mm.h>		/* si_meminfo */
#include <linux/proc_fs.h>	/* Access to /proc */
#include <linux/seq_file.h>	/* Access to seq file operations */

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Igore");
MODULE_DESCRIPTION("Getting information from the Kernel");
MODULE_VERSION("0.1");

#define PROCFS_MAX_SIZE		1024
#define PROCFS_NAME 		"igore"

static struct proc_dir_entry *Igore_Proc_File;

static int igore_proc_show(struct seq_file *m, void *v)
{
	/* meminfo returns the number of pages.
	 * For the memory size the pages need to
	 * be multiplied by the mem_unit size (in bytes)
	 * Then for kibibytes divide by 1024
	 */

	int kibiscale;
	struct sysinfo i;
	si_meminfo(&i);

	kibiscale = i.mem_unit / 1024;

	seq_printf(m, "Hi!\nGo cat yourself!\n");
	seq_printf(m, "Mem Total: %lu KiB\n", i.totalram * kibiscale);
	seq_printf(m, "Free RAM : %lu KiB\n", i.freeram * kibiscale);
	seq_printf(m, "Page size: %d bytes\n", i.mem_unit);

	return 0;
}

static int igore_proc_open(struct inode *inode, struct file *file)
{
	return single_open(file, igore_proc_show, NULL);
}

static const struct file_operations igore_proc_fops = {
	.owner = THIS_MODULE,
	.open = igore_proc_open,
	.read = seq_read,
	.llseek = seq_lseek,
	.release = single_release,
};

static int load_module(void)
{
	printk(KERN_INFO "Loading Igore Module.\n");

	/* create the /proc file */
	Igore_Proc_File =
	    proc_create(PROCFS_NAME, 0644, NULL, &igore_proc_fops);

	if (Igore_Proc_File == NULL) {
		remove_proc_entry(PROCFS_NAME, NULL);
		printk(KERN_ALERT "Error: Could not initialize /proc/%s\n",
		       PROCFS_NAME);
		return -ENOMEM;
	}

	printk(KERN_INFO "/proc/%s created\n", PROCFS_NAME);
	return 0;
}

static void unload_module(void)
{
	printk(KERN_INFO "Unloading Igore Module.\n");
	printk(KERN_INFO "Removing /proc/%s\n", PROCFS_NAME);
	remove_proc_entry(PROCFS_NAME, NULL);
	printk(KERN_INFO "/proc/%s removed.\n", PROCFS_NAME);
	printk(KERN_INFO "Igore module unloaded.\n");
}

module_init(load_module);
module_exit(unload_module);
