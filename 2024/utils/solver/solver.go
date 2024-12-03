package solver

import (
	"fmt"
	"os"

	"github.com/bengsfort/advent-of-code/2024/utils/args"
	"github.com/bengsfort/advent-of-code/2024/utils/timer"
)

type Solver interface {
	SolvePartOne([]byte) (string, error)
	SolvePartTwo([]byte) (string, error)
}

func Solve(s Solver) error {
	clock := timer.NewSimpleTimer()
	in, err := args.GetStrArg("--in", true)
	if err != nil {
		return err
	}

	fmt.Printf("Using file %s\n", in)
	input, err := os.ReadFile(in)
	if err != nil {
		return err
	}

	clock.Mark("input read")
	result, err := s.SolvePartOne(input)

	if err != nil {
		return err
	}

	fmt.Printf("Part 1 result: %s\n", result)
	clock.Mark("solved part 1")

	result2, err := s.SolvePartTwo(input)
	if err != nil {
		return err
	}

	fmt.Printf("Part 2 result: %s\n\n", result2)
	clock.Mark("solved part 2")

	clock.Stop()
	fmt.Print(clock.PrintResults())

	return nil
}
