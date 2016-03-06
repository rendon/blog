struct task_struct {
    volatile long state;	/* -1 unrunnable, 0 runnable, >0 stopped */
    void *stack;
    atomic_t usage;
    unsigned int flags;	/* per process flags, defined below */
    unsigned int ptrace;

    ...

    pid_t pid;
    pid_t tgid;

    ...
    char comm[TASK_COMM_LEN]; /* executable name excluding path
                     - access with [gs]et_task_comm (which lock
                       it with task_lock())
                     - initialized normally by setup_new_exec */

    ...

    /*
     * children/sibling forms the list of my natural children
     */
    struct list_head children;	/* list of my children */
    struct list_head sibling;	/* linkage in my parent's children list */
    ...
}
