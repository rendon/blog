#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/list.h>
#include <linux/types.h>
#include <linux/slab.h>
#include <linux/sched.h>
#include <linux/string.h>

void pstree(struct task_struct *s, int sum)
{
    struct list_head *list;
    struct task_struct *task;

    int i;
    for (i = 0; i < sum; i++)
        printk(" ");
    printk("|-->%s\n", s->comm);
    sum = sum + strlen(s->comm);
    list_for_each(list, &s->children) {
        task = list_entry(list, struct task_struct, sibling);
        pstree(task, sum);
    }
}


int simple_init(void)
{
    struct task_struct *parent = current;
    while (parent->pid != 1)
        parent = parent->parent;
    
    pstree(parent, 0);

    return 0;
}

void simple_exit(void)
{
    printk("Bye!\n");
}

module_init(simple_init);
module_exit(simple_exit);

MODULE_LICENSE("GPLv3");
MODULE_DESCRIPTION("Playing with processes.");
MODULE_AUTHOR("Rafael Rendón Pablo");
