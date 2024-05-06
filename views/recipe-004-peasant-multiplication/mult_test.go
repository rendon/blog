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
