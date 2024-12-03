package main

import (
	"fmt"
	"os"

	"github.com/bengsfort/advent-of-code/2024/one/part_one"
	"github.com/bengsfort/advent-of-code/2024/one/part_two"
	"github.com/bengsfort/advent-of-code/2024/utils/args"
	"github.com/bengsfort/advent-of-code/2024/utils/timer"
)

func main() {
	clock := timer.NewSimpleTimer()
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

	clock.Mark("input read")
	result, err := part_one.Solve(input)

	if err != nil {
		fmt.Println(err)
		return
	}

	fmt.Printf("Part 1 result: %s\n", result)
	clock.Mark("solved part 1")

	result2, err := part_two.Solve(input)
	if err != nil {
		fmt.Println(err)
		return
	}

	fmt.Printf("Part 2 result: %s\n\n", result2)
	clock.Mark("solved part 2")

	clock.Stop()
	fmt.Print(clock.PrintResults())
}
