# Recipe 002: Depth-First Search (DFS)
2016-02-18 2024-05-07 #algorithms #data-structures #post

[Depth-First Search](http://en.wikipedia.org/wiki/Depth-first_search) is one of the fundamental algorithms in [graph theory](https://en.wikipedia.org/wiki/Graph_theory). It's a must to know!

Nowadays it's a piece of cake, but I did struggle a bit to get my head around this and other graph theory algorithms.

![A graph.](/recipe-002-dfs/graph.svg)

## Common ways to represent graphs in a computer 

The most common representations for graphs are [Adjacency matrix](http://en.wikipedia.org/wiki/Adjacency_matrix) and [Adjacency list](http://en.wikipedia.org/wiki/Adjacency_list).

Embed: `src-matrix.cpp`

Example input (figure 1):

Embed: `input.txt`

Example output:
Embed: `output.txt`

Here is the version using adjacency "lists" (not necessarily linked lists).

Embed: `src-list.cpp`
