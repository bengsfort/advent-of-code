package part_two

import (
	"fmt"
	"strconv"
	"strings"
)

func Solve(input []byte) (string, error) {
	lines := strings.Split(string(input), "\n")

	left := make([]int, 0)
	rightCount := make(map[int]int)

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

		left = append(left, leftInt)

		rightCount[rightInt]++
	}

	numItems := len(left)
	result := 0

	for i := 0; i < numItems; i++ {
		count := rightCount[left[i]]
		result += left[i] * count
	}

	return fmt.Sprintf("%d", result), nil
}
