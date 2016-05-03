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
