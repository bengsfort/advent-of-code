package solution

import (
	"fmt"
	"strconv"
	"strings"

	"github.com/bengsfort/advent-of-code/2024/utils/bmath"
)

type Solution struct{}

type Comparison struct {
	difference int
	direction  int
}

const max_threshold int = 3
const min_threshold int = 1

func compareNumbers(a, b int) Comparison {
	diff := a - b
	dir := bmath.IntSign(diff)
	return Comparison{
		difference: diff,
		direction:  dir,
	}
}

func isPairValid(current int, previous int, direction int, ignoreDirection bool) (valid bool, comparison Comparison) {
	if current == previous {
		fmt.Println("Same numbers!", current, "->", previous)
		return false, comparison
	}

	comparison = compareNumbers(current, previous)

	if !ignoreDirection && direction != comparison.direction {
		fmt.Println("Invalid direction change!", direction, "->", comparison.direction)
		return false, comparison
	}

	if comparison.difference > max_threshold || comparison.difference < min_threshold {
		fmt.Println("Exceeded thresholds! %d -> %d (diff: %d)", current, "->", previous, " (diff: ", comparison.difference, ")")
		return false, comparison
	}

	return true, comparison
}

func isReportValid(values []string, dampen bool) (bool, error) {
	var previous int
	var direction int
	dampenerActive := false

	for i, value := range values {
		if value == "" {
			fmt.Println("\tempty string!")
			continue
		}

		num, err := strconv.Atoi(value)
		if err != nil {
			return false, err
		}

		if i == 0 {
			previous = num
			fmt.Println("\tvalid pair (frist)!")
			continue
		}

		valid, comparison := isPairValid(num, previous, direction, i == 1)

		if valid {
			previous = num
			direction = comparison.direction
			fmt.Println("\tvalid pair!")
			continue
		}

		if dampen && !dampenerActive {
			fmt.Println("\tdampener active!")
			dampenerActive = true
			continue
		}

		fmt.Println("\tinvalid!\n")
		return false, nil
	}

	fmt.Println("\tvalid!\n")
	return true, nil
}

func (s *Solution) SolvePartOne(input []byte) (string, error) {
	lines := strings.Split(string(input), "\n")
	result := 0

	for _, line := range lines {
		if line == "" {
			continue
		}

		values := strings.Split(line, " ")
		fmt.Println("Validating report:", values)
		valid, err := isReportValid(values, false)
		if err != nil {
			return "", err
		}

		if valid {
			result++
		}
	}

	return fmt.Sprintf("%d", result), nil
}

func (s *Solution) SolvePartTwo(input []byte) (string, error) {
	lines := strings.Split(string(input), "\n")
	result := 0

	for _, line := range lines {
		if line == "" {
			continue
		}

		values := strings.Split(line, " ")
		fmt.Println("Validating report:", values)
		valid, err := isReportValid(values, true)
		if err != nil {
			return "", err
		}

		if valid {
			result++
		}
	}

	return fmt.Sprintf("%d", result), nil
}
