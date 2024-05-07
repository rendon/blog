# Topological sorting
2016-02-18 2024-05-07 #algorithms #post

<p>Let's start this topic with an example, we have some tasks to do, some tasks are independent of each other, but some tasks depend on other tasks and those tasks must be done before these tasks. We can model this problem with a graph, the tasks are vertices and the dependencies are edges. Topological sorting is an algorithm that helps us to find an ordering of tasks such that for every task $u$ that has to be done before task $v$, $u$ comes before $v$ in the ordering.</p>

<p>Topological sorting works on <a href="http://en.wikipedia.org/wiki/Directed_acyclic_graph" target="_blank">DAGs</a>, that is, graphs wit no cycles, if the graph contains a cycle it's impossible to find a solutions. For example, if task $A$ depends on task $B$ and task $B$ depends on task $A$ then it's impossible to determine which task has to be done first, see <a href="http://en.wikipedia.org/wiki/Chicken_or_the_egg" target="_blank">Chicken or Egg</a>.</p>

## Example problem
<p>Here you have a problem where you have to literally find an ordering for tasks: <a href="http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1246" target="_blank">10305 - Ordering Tasks</a>. Here is a working implementation of Topological sorting.</p>

Embed: `src.cpp`

<p>The solutions works as follows:</p>

<ol>
  <li>If task $u$ has to be done before task $v$ create a directed edge from $v$ to $u$.</li>
  <li>Create a table $visited[]$ such that $visited[u]$ is true if node $u$ has been visited.</li>
  <li>Run a [Depth-First Search](recipe-002-dfs) on all nodes that has not been visited yet and print the nodes in reverse order, we can do that by printing node $u$ before leaving the recursive function.</li>
</ol>

<p>The resulting sequence of nodes is a valid ordering. Notice that it's possible to have multiple valid solutions.</p>

<p>The previous problem is easy because is the classical example to explain Topological sorting. However, most of the time these problems are not so obvious and we have to work a bit to uncover the underlying problem, for example <a href="http://lightoj.com/volume_showproblem.php?problem=1034" target="_blank">1034 - Hit the Light Switches</a> (hint, think a bout connected components).</p>

## References

- [Algorithms, 4th Edition](http://algs4.cs.princeton.edu/home/)
