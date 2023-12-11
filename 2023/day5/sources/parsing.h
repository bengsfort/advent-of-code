#include <string>
#include <vector>
#include <array>

namespace day5
{

    void parse_seed_ids(std::string* curr_line, std::vector<long long>* results);

    std::string parse_map_title(std::string* curr_line);

    // Returns the parsed map line.
    // [dst_range_start, src_range_start, length]
    std::array<long long, 3> parse_map_line(std::string* curr_line);

	long long translate_to_range(long long id, std::array<long long, 3>* map);
}
