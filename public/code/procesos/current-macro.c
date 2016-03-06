struct task_struct *parent = current;
while (parent->pid != 1)
    parent = parent->parent;
