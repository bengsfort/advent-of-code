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
		difference: diff * dir,
		direction:  dir,
	}
}

func isPairValid(current int, previous int, direction int) (valid bool, comparison Comparison) {
	if current == previous {
		fmt.Printf(" Same numbers! %d -> %d ", current, previous)
		return false, comparison
	}

	comparison = compareNumbers(current, previous)

	if direction != 0 && direction != comparison.direction {
		fmt.Printf(" Invalid direction change! %d -> %d ", direction, comparison.direction)
		return false, comparison
	}

	if comparison.difference > max_threshold || comparison.difference < min_threshold {
		fmt.Printf("Exceeded thresholds! %d -> %d (diff: %d) ", current, previous, comparison.difference)
		return false, comparison
	}

	return true, comparison
}

func isReportValid(values []string) (bool, error) {
	var previous int
	var direction int

	for i, value := range values {
		if value == "" {
			continue
		}

		num, err := strconv.Atoi(value)
		if err != nil {
			return false, err
		}

		if i == 0 {
			previous = num
			continue
		}

		valid, comparison := isPairValid(num, previous, direction)

		if !valid {
			fmt.Printf(" invalid!\n")
			return false, nil
		}

		previous = num
		direction = comparison.direction
	}

	fmt.Printf(" valid!\n")
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
		valid, err := isReportValid(values)
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
		fmt.Printf("Validating report: %v", values)
		valid, err := isReportValid(values)
		if err != nil {
			return "", err
		}

		if valid {
			result++
			continue
		}

		// @todo: could optimise by stopping if it fails on the first 3 values even when removing them
		// (if its always gonna fail on the first 3, no point checking the rest of the slice)
		fmt.Println("\tAttempting to dampen report...")
		for i := range values {
			omitted := append(make([]string, 0), values[:i]...)
			omitted = append(omitted, values[i+1:]...)

			fixed, err := isReportValid(omitted)
			if err != nil {
				return "", err
			}

			if fixed {
				fmt.Println(" Dampened report!")
				result++
				break
			}
		}
	}

	return fmt.Sprintf("%d", result), nil
}
