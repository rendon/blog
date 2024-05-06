#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/list.h>
#include <linux/types.h>
#include <linux/slab.h>
#include <linux/sched.h>
#include <linux/string.h>

void pstree_coord(struct task_struct *s, int x, int y)
{
    struct list_head *list;
    struct task_struct *task;
    int i = 0, size = 0, offset = 15;
    printk("%s\\n[%d]:%d,%d,C\n", s->comm, s->pid, x, y);
    list_for_each(list, &s->children)
        size += offset;

    i = -size / 2;
    list_for_each(list, &s->children) {
        task = list_entry(list, struct task_struct, sibling);
        pstree_coord(task, x + i, y - 15);
        i += offset;
    }
}

void pstree(struct task_struct *s)
{
    struct list_head *list;
    struct task_struct *task;
    printk("%s\\n[%d],%s\\n[%d]\n",
           s->parent->comm, s->parent->pid, s->comm, s->pid);

    list_for_each(list, &s->children) {
        task = list_entry(list, struct task_struct, sibling);
        pstree(task);
    }
}


int simple_init(void)
{
    struct task_struct *parent = current;
    while (parent->pid != 1)
        parent = parent->parent;
    
    printk("[EDGES]\n");
    pstree(parent);
    printk("[VERTICES]\n");
    pstree_coord(parent, 0, 0);

    return 0;
}

void simple_exit(void)
{
    printk("======================= END =========================\n");
}

module_init(simple_init);
module_exit(simple_exit);

MODULE_LICENSE("GPLv3");
MODULE_DESCRIPTION("Playing with processes.");
MODULE_AUTHOR("Rafael Rendón Pablo");

