package timer

import (
	"fmt"
	"time"
)

type SimpleTimer struct {
	start int64
	end   int64
	marks map[string]int64
}

func NewSimpleTimer() *SimpleTimer {
	start := time.Now().UnixNano()
	marks := make(map[string]int64)
	marks["start"] = start

	return &SimpleTimer{
		start: start,
		end:   0,
		marks: marks,
	}
}

func (t *SimpleTimer) Mark(name string) {
	t.marks[name] = time.Now().UnixNano()
}

func (t *SimpleTimer) Stop() {
	t.end = time.Now().UnixNano()
	t.marks["end"] = t.end
}

func (t *SimpleTimer) Elapsed() time.Duration {
	return time.Duration(t.end - t.start)
}

func (t *SimpleTimer) MarkElapsed(name string) (time.Duration, error) {
	mark, ok := t.marks[name]
	if !ok {
		return 0, fmt.Errorf("mark '%s' not found", name)
	}

	return time.Duration(mark - t.start), nil
}

func (t *SimpleTimer) MarkElapsedFromMark(markName string, name string) (time.Duration, error) {
	mark, ok := t.marks[markName]
	if !ok {
		return 0, fmt.Errorf("mark '%s' not found", markName)
	}

	mark2, ok := t.marks[name]
	if !ok {
		return 0, fmt.Errorf("mark '%s' not found", name)
	}

	return time.Duration(mark2 - mark), nil
}

func (t *SimpleTimer) PrintResults() string {
	numMarks := len(t.marks)

	marks := make([]string, 0, numMarks)
	for k := range t.marks {
		marks = append(marks, k)
	}

	prevMark := "start"
	result := "Timer results:\n"

	for _, mark := range marks[1 : numMarks-1] {
		elapsed, _ := t.MarkElapsedFromMark(prevMark, mark)
		result += fmt.Sprintf("- Mark '%s' elapsed: %s\n", mark, elapsed)
		prevMark = mark
	}

	result += fmt.Sprintf("Total elapsed: %s\n", t.Elapsed())

	return result
}
