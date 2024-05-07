# Recipe 002: Depth-First Search (DFS)
2016-02-18 2024-05-07 #algorithms #data-structures #post

<p><a href="http://en.wikipedia.org/wiki/Depth-first_search" target="_blank">Depth-First Search</a> is one of the fundamental algorithms in <a href="https://en.wikipedia.org/wiki/Graph_theory" target="_blank">graph theory</a>. It's a must to know!</p>

<p>Nowadays it's a piece of cake, but I did struggle a bit to get my head around this and other graph theory algorithms.</p>

![A graph.](/recipe-002-dfs/graph.svg)

## Common ways to represent graphs in a computer 

<p>The most common representations for graphs are <a href="http://en.wikipedia.org/wiki/Adjacency_matrix" target="_blank">Adjacency matrix</a> and <a href="http://en.wikipedia.org/wiki/Adjacency_list" target="_blank">Adjacency list</a>.</p>

Embed: `src-matrix.cpp`

Example input (figure 1):

Embed: `input.txt`

Example output:
Embed: `output.txt`

Here is the version using adjacency "lists" (not necessarily linked lists).

Embed: `src-list.cpp`
