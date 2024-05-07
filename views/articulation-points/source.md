# Articulation points
2016-02-18 2024-05-07 #algorithms #data-structures #post

## Welcome

Hey guys! Currently I am training for a programming contest and I have no time to publish. I am learning many interesting topics about algorithms and programming and I want to share that with you. However, to write an article consumes much of my time and I'm devising a format that is both brief and useful: Algorithm or Data structure, brief info, sample problem, solution and references.

## Articulation points

Today's topic is about [graph theory](http://en.wikipedia.org/wiki/Graph_theory), articulation points. Here a [brief info from Dave Mount](http://www.cs.umd.edu/~samir/451/bc.ps):

<div class="box">
  **Articulation Points and Biconnected Graphs:** Today we discuss another application of DFS, this time to a problem on undirected graphs. Let *G = (V, E)* be a ** connected** undirected graph. Consider de following definitions.

  **Articulation Point( or Cut Vertex):** Is any vertex whose removal(together with the removal of any incident edges) results in a disconnected graph.
</div>

![Articulation points example](/articulation-points/artpoints.svg)

## Sample problem

A problem where you can put in practice this topic is [1063 Ant Hills](http://lightoj.com/volume_showproblem.php?problem=1063) from [lightoj.com](http://lightoj.com).

## Solution to sample problem

Embed: `sol.cpp`

## References

<table border="0">
  <tr><td>1</td>   <td>[Articulation Points and Biconnected Components](http://www.cs.umd.edu/~samir/451/bc.ps)</td></tr>
  <tr><td>2</td>   <td>[Articulation Points Detection Algorithm](http://www.ibluemojo.com/school/articul_algorithm.html)</td></tr>
  <tr><td>3</td><td>[Biconnected component](http://en.wikipedia.org/wiki/Biconnected_component)</td></tr>
</table>

