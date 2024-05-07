# Jacobi method
2016-02-18 2024-05-07 #algorithms #math #post

Systems of linear equations are very important and has many applications in real life, from the most obvious to find the intersection point of many linear equations in the plane, upto the analysis of electronic circuits with Kirchhoff's laws or traffic flow in streets. 

I am not an expert in this topics but currently we are studying this topic  in my numerical methods course, since the course is about "numerical" methods, we don't study the Gaussian elimination method because it is more algebraic, instead we study Jacobi method. I am going to explain briefly the idea of the method and I give you a simple implementation in Java.

## Jacobi method

This was the first iterative method to solve systems of linear equations and was devised by [Carl Gustav Jacob Jacobi](http://en.wikipedia.org/wiki/Carl_Gustav_Jakob_Jacobi)(1804-1851). Lets define the system of linear equations as:

![Equation system](/jacobi-method/jacobi_1.png)

For each row *i* isolate the $x\_{i}$ variable.

![Isolate variables](/jacobi-method/jacobi_2.png)

Make an initial approximation of the solution $(x_{1}, x_{2}, x_{3},\ldots,x_{n})$, a good choice is to use zero to all variables. Substitute these values in the rewritten equation and update the values of the approximation. Repeat the process until the answer be acceptable.

## Stop condition

You can stop the iterations when $ |x\_{n+1} - x\_{n}| \leq \epsilon$ for all $x\_{i}$, $n$ is the number of iterations.

## Convergence condition

Only if  the coefficient matrix is [diagonally dominant](http://en.wikipedia.org/wiki/Diagonally_dominant_matrix) the method can guarantee a convergence to the solution. Sometimes the convergence can be achieved even if the conditions are not satisfied, but there is no guarantee.

## Implementation in Java

Embed: `jacobi.java`

## Gauss-Seidel Method

This is modification of the Jacobi method made by [Carl Friedrich Gauss](http://en.wikipedia.org/wiki/Carl_Friedrich_Gauss) and [Philipp L. Seidel](http://en.wikipedia.org/wiki/Philipp_Ludwig_von_Seidel) that can converge in less iterations than Jacobi method. 

In the Jacobi method the values of the approximations $x_{i}$ are used up to the next iteration of the method while in the Gauss-Seidel version each approximation $x_{i}$  is used as soon as it's ready, see the code to a better understanding. Since the two methods are very similar I show only the fragment where the codes differ.

Embed: `gauss-seidel.java`

The conditions for stopping and convergence are the same for both methods.

## Comparison

If we solve the following system of linear equations we get to the answer at different rates.

![Example](/jacobi-method/jacobi_3.png)

Jacobi's method needs 28 iterations:

<pre>
X_28 = {0.18611987381703476 0.3312302839116719 -0.42271293375394314 }
</pre>

while Gauss-Seidel only needs 17:

<pre>
X_17 = {0.18611987381703465 0.3312302839116719 -0.42271293375394325 }
</pre>

## Conclusion

I think these methods are easier to remember than the Gaussian elimination method and can be very useful when you have a computer and an approximated result is acceptable, for example, in a programming contest :). I hope it be useful for you, Bye!

## References

<table border="0">
  <tr><td>1</td>   <td>[Iterative methods for solving linear systems](http://college.cengage.com/mathematics/larson/elementary_linear/5e/students/ch08-10/chap_10_2.pdf)</td></tr>
  <tr><td>2</td>   <td>[Jacobi method, Wikipedia](http://en.wikipedia.org/wiki/Jacobi_method)</td></tr>
</table>
