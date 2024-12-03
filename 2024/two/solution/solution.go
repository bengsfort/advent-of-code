package solution

import (
	"fmt"
	"strconv"
	"strings"

	"github.com/bengsfort/advent-of-code/2024/utils/bmath"
)

type Solution struct{}

const max_threshold int = 3
const min_threshold int = 1

func compareNumbers(a, b int) (dir, diff int) {
	diff = a - b
	dir = bmath.IntSign(diff)
	return dir, diff * dir
}

func isReportValid(values []string, dampen bool) (bool, error) {
	var previous int
	var direction int
	dampenerActive := false

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

		if num == previous {
			fmt.Printf("Invalid number! %d == %d\n", previous, num)

			if dampen && !dampenerActive {
				fmt.Printf("Dampener activated ")
				dampenerActive = true
				continue
			}

			return false, nil
		}

		dir, diff := compareNumbers(previous, num)

		if i == 1 {
			direction = dir
		} else if direction != dir {
			if dampen && !dampenerActive {
				fmt.Printf("Dampener activated ")
				dampenerActive = true
				continue
			}

			fmt.Printf("Invalid direction change! %d -> %d\n", direction, dir)
			return false, nil
		}

		if diff > max_threshold || diff < min_threshold {
			if dampen && !dampenerActive {
				fmt.Printf("Dampener activated ")
				dampenerActive = true
				continue
			}

			fmt.Printf("Invalid change! %d -> %d (diff %d)\n", previous, num, diff)
			return false, nil
		}

		previous = num
	}

	fmt.Printf("valid!\n")
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
		fmt.Printf("Validating report: %v ", values)
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
		fmt.Printf("Validating report: %v ", values)
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
