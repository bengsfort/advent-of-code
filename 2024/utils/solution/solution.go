package solution

type Solution interface {
	ParseInput(input []byte) error
	Solve() (string, error)
}
