struct list_head *list;
struct task_struct *task;

list_for_each(list, &s->children)
    task = list_entry(list, struct task_struct, sibling);
