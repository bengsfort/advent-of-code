#ifndef DAY5_SOLVER_H
#define DAY5_SOLVER_H

#include <string>

namespace day5
{

template<typename T> class solver
{
public:
	virtual void parse_line(int line_number, std::string* curr_line) = 0;
	virtual T get_result() = 0;
};

}

#endif DAY5_SOLVER_H
