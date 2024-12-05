package solution

import (
	"fmt"
	"strconv"
	"strings"
)

type Solution struct{}

const instruction = "mul"

type Instruction struct {
	cursor    int
	cursorEnd int
	operation string
	args      []string
	raw       string
}

type Config struct {
	argMaxLen int
	argMinLen int
	maxArgs   int
}

func parseConsecutiveNumbers(prog string, cursor int, config *Config) (string, int, error) {
	fmt.Printf("Parsing consecutive numbers from cursor %d\n", cursor)

	if cursor >= len(prog) {
		return "", cursor, fmt.Errorf("cursor is out of bounds")
	}

	virtualCursor := cursor
	parsedArg := ""
	group := prog[cursor : cursor+config.argMaxLen]

	for i := 0; i < len(group); i++ {
		if _, err := strconv.Atoi(string(group[i])); err != nil {
			fmt.Printf("Found non-numeric character at %d: %s\n", i, string(group[i]))
			break
		}

		parsedArg += string(group[i])
		virtualCursor++
	}

	if parsedArg == "" {
		return "", cursor, fmt.Errorf("no valid numbers found")
	}

	return parsedArg, virtualCursor, nil
}

// @todo - make an 'active cursor' and then cache the specific points?
func findNextInstruction(prog string, cursor int, config *Config) (*Instruction, int) {
	fmt.Printf("Finding next instruction from cursor %d\n", cursor)

	if cursor >= len(prog) {
		fmt.Printf("Cursor is out of bounds\n")
		return nil, -1
	}

	slice := prog[cursor:]
	activeCursor := strings.Index(slice, instruction)

	if activeCursor == -1 {
		fmt.Printf("No more instructions found from cursor %d\n", cursor)
		return nil, -1
	}

	fmt.Printf("Created virtual cursor at %d\n", activeCursor)
	instructionStart := activeCursor
	instructionEnd := instructionStart + len(instruction)
	operation := slice[instructionStart:instructionEnd]

	if operation != instruction {
		fmt.Printf("- Invalid instruction found at %d - %d: %s\n", instructionStart, instructionEnd, operation)
		return nil, -1
	}

	activeCursor = instructionEnd
	fmt.Printf("Found instruction at %d - %d: %s\n", instructionStart, instructionEnd, operation)
	fmt.Printf("Virtual cursor now at %d\n", activeCursor)

	if slice[activeCursor] != '(' {
		fmt.Printf("- Instruction not followed by parenthesis (found %s)\n", string(slice[activeCursor]))
		return nil, -1
	}
	fmt.Printf("Found instruction at %d: %s\n", instructionStart, operation)

	activeCursor++
	parsedAgs := make([]string, 0)

	for i := 0; i < config.maxArgs; i++ {
		parsed, endCursor, err := parseConsecutiveNumbers(slice, activeCursor, config)
		if err != nil {
			fmt.Printf("- Failed to parse argument: %s\n", err)
			return nil, -1
		}

		fmt.Printf("Parsed argument: %s (activeCursor %d, endCursor %d)\n", parsed, activeCursor, endCursor)
		parsedAgs = append(parsedAgs, parsed)
		activeCursor = endCursor

		if slice[activeCursor] == ')' {
			break
		}

		if slice[activeCursor] != ',' {
			fmt.Printf("- Expected comma or closing parenthesis, found %s\n", string(slice[activeCursor]))
			return nil, -1
		}

		activeCursor++
	}

	fmt.Printf("Parsed arguments: %v\n", parsedAgs)

	return nil, -1
}

func (s *Solution) SolvePartOne(input []byte) (string, error) {
	prog := string(input)

	cursor := 0
	instructions := make([]Instruction, 0)
	config := Config{
		argMaxLen: 3,
		argMinLen: 1,
		maxArgs:   2,
	}

	fmt.Printf("Finding valid instructions in program:\n%s\n", prog)
	for cursor != -1 {
		next, newCursor := findNextInstruction(prog, cursor, &config)
		if next != nil {
			instructions = append(instructions, *next)
		}

		cursor = newCursor
		fmt.Printf("Cursor is now at %d\n", cursor)
	}

	fmt.Printf("Found %d instructions\n", len(instructions))
	for i, instruction := range instructions {
		fmt.Printf("Instruction %d: %s\n", i, instruction.raw)
	}

	return "", nil
}

func (s *Solution) SolvePartTwo(input []byte) (string, error) {
	// @todo
	return "", nil
}
