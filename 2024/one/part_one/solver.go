package part_one

import (
	"fmt"
	"slices"
	"strconv"
	"strings"
)

func Solve(input []byte) (string, error) {
	lines := strings.Split(string(input), "\n")

	left := make([]int, 0)
	right := make([]int, 0)

	injected := false
	for _, line := range lines {
		if line == "" {
			continue
		}

		midPoint := len(line) / 2

		leftHalf := strings.Trim(line[:midPoint], " ")
		rightHalf := strings.Trim(line[midPoint:], " ")

		leftInt, err := strconv.Atoi(leftHalf)
		if err != nil {
			return "", err
		}

		rightInt, err := strconv.Atoi(rightHalf)
		if err != nil {
			return "", err
		}

		if !injected {
			injected = true
			left = append(left, leftInt)
			right = append(right, rightInt)
			continue
		}

		if !injected || leftInt > left[0] {
			injected = true
			left = append(left, leftInt)
		} else {
			left = append([]int{leftInt}, left...)
		}

		if rightInt > right[0] {
			right = append(right, rightInt)
		} else {
			right = append([]int{rightInt}, right...)
		}
	}

	if len(left) == 0 || len(right) == 0 {
		return "", fmt.Errorf("lists are empty")
	}

	if len(left) != len(right) {
		return "", fmt.Errorf("lists are not the same length")
	}

	slices.SortFunc(left, func(a, b int) int {
		return a - b
	})

	slices.SortFunc(right, func(a, b int) int {
		return a - b
	})

	numItems := len(left)
	result := 0

	for i := 0; i < numItems; i++ {
		if left[i] > right[i] {
			result += left[i] - right[i]
		} else {
			result += right[i] - left[i]
		}
	}

	return fmt.Sprintf("%d", result), nil
}
