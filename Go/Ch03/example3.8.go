package main

import "fmt"

func main() {
	x := []int{1, 2, 3, 4}
	y := x[:2:2]
	z := x[2:4:4]

	fmt.Println(x)
	fmt.Println(y)
	fmt.Println(z)
}