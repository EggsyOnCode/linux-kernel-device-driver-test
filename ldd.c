#include <linux/init.h>
#include <linux/proc_fs.h>
#include <linux/module.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("eggsyOnCode");
MODULE_DESCRIPTION("kernel device driver for test");

static struct proc_dir_entry *entry_proc_file;


static ssize_t eggsy_read(struct file *file_ptr, char __user *user_space_buffer, size_t count, loff_t *offset) {
    char msg[] = "Ack!\n";
    size_t len = strlen(msg);
    int res;

    if (*offset >= len) {
        return 0;
    }

    res = copy_to_user(user_space_buffer, msg, len);
    *offset += len;
    
    printk("proc file read \n");

    return len;
}


static struct proc_ops driver_proc_ops = {
    .proc_read = eggsy_read
};


static int eggsy_module_init(void) {

    printk("device drvier init start...\n");

    // creating a proc_file
    entry_proc_file = proc_create("eggsy_driver", 
                                    0, 
                                    NULL, 
                                    &driver_proc_ops);

    if (entry_proc_file == NULL) {
        printk("error during proc file creation");
        return -1;
    }   

    printk("device drvier init exit ...\n");

    return 0;
}

static void eggsy_module_exit(void) {
    printk("module exiting.....start \n");
    proc_remove(entry_proc_file);

    printk("module exiting..... end \n");
}

module_init(eggsy_module_init);
module_exit(eggsy_module_exit);