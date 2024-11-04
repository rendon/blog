---
tags:
    - algorithms
    - post
created: 2016-05-02
updated: 2024-05-06
---
# Russian peasant multiplication

I learned this one from [Intro to Algorithms](https://classroom.udacity.com/courses/cs215).

- Q: How would you multiply two numbers without using the `*` operator?
- A: Using the Russian peasant multiplication algorithm and bitshift operators.

## Code
Some tests:

```go
package mult

import "testing"

func TestMultNegative(t *testing.T) {
	if v := Mult(-1, -4); v != 4 {
		t.Fatalf("Expected %v to be 4", v)
	}
}

func TestMultPositive(t *testing.T) {
	if v := Mult(7, 9); v != 63 {
		t.Fatalf("Expected %v to be 63", v)
	}
}

func TestMultPositiveAndNegative(t *testing.T) {
	if v := Mult(-8, 9); v != -72 {
		t.Fatalf("Expected %v to be -72", v)
	}
}
```

Implementation:

```go
package mult

func sign(x int) int {
	if x < 0 {
		return -1
	}
	return 1
}

func abs(x int) int {
	if x < 0 {
		return -x
	}
	return x
}

func Mult(a, b int) int {
	// Handle the case with negative values for a and b
	as := sign(a)
	a = abs(a)
	bs := sign(b)
	b = abs(b)

	// Actual multiplication
	x := uint(a)
	y := uint(b)
	z := uint(0)
	for x > 0 {
		if x%2 == 1 {
			z += uint(y)
		}
		x >>= 1
		y <<= 1
	}
	return int(z) * as * bs
}
```

Pretty cool, huh?
