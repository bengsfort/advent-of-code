package main

import (
	"github.com/bengsfort/advent-of-code/2024/.template/solution"
	"github.com/bengsfort/advent-of-code/2024/utils/solver"
)

func main() {
	err := solver.Solve(&solution.Solution{})
	if err != nil {
		panic(err)
	}
}