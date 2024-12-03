package main

import (
	"fmt"
	"os"

	"github.com/bengsfort/advent-of-code/2024/one/solver"
	"github.com/bengsfort/advent-of-code/2024/utils/args"
)

func main() {
	in, err := args.GetStrArg("--in", true)
	if err != nil {
		fmt.Println(err)
		return
	}

	fmt.Printf("Using file %s\n", in)
	input, err := os.ReadFile(in)
	if err != nil {
		panic(err)
	}

	result, err := solver.Solve(input)
	if err != nil {
		fmt.Println(err)
		return
	}

	fmt.Printf("Done!\nResult: %s", result)
}
