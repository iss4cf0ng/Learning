package main

import "fmt"

func main() {
	x := []int{1, 2, 3, 4}
	y := x[:2]
	z := x[1:]

	x[1] = 20
	y[0] = 10
	z[1] = 30

	fmt.Println("x:", x)
	fmt.Println("y:", y)
	fmt.Println("z:", z)
}