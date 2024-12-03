package args

import (
	"fmt"
	"os"
	"strings"
)

type ArgError struct {
	Arg   string
	Issue string
}

func (e ArgError) Error() string {
	return fmt.Sprintf("Error with arg '%s': %s", e.Arg, e.Issue)
}

func GetStrArg(argName string, required bool) (string, error) {
	var argStr string

	for arg := range os.Args {
		if !strings.Contains(os.Args[arg], argName) {
			continue
		}

		argStr = os.Args[arg]
		break
	}

	if argStr == "" && required {
		return "", &ArgError{
			Arg:   argName,
			Issue: "Required but not found",
		}
	}

	split := strings.Split(argStr, "=")
	if len(split) == 1 || split[1] == "" {
		return "", &ArgError{
			Arg:   argName,
			Issue: "Missing declaration (argName=value)",
		}
	}

	return split[1], nil
}
