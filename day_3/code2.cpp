#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>
#include <map>

#include "../utils.cpp"

void pre_process(std::string &in, towd_array &grid) {
	in = std::regex_replace(in, std::regex("[^0-9\\.\\*]+"), ".");
	in = std::regex_replace(in, std::regex("\\*"), "X");
	grid.append_line(in);
}

void process(towd_array &grid, int y, std::map<std::string, std::vector<int>> &gers) {

	grid.for_all_numbers_in_line(y, [y, &grid, &gers](int digit, int start, int end){

		std::string poss = grid.digit_has_neighbor_at(y, digit, start, end);

		for_all_substrings(poss, "_", [digit, &gers](std::string pos){
			gers[pos].push_back(digit);
		});

	});
}

int main() {
	std::string line;
	std::ifstream file_in;
	int sum{0};

	file_in.open ("data.txt", std::ifstream::in);

	if (file_in.is_open())
	{
		towd_array grid;
		while(getline(file_in, line)) {
			pre_process(line, grid);
		}
		std::map<std::string, std::vector<int>> gers;
		for (int i{0}; i < grid.higth(); ++i) { // can use algorith, need wrapper for each
			process(grid, i, gers);
		}

		for (auto const& [key, val] : gers)
		{
			if(val.size() == 2) {
				sum += val[0]*val[1];
			}
		}


		file_in.close();
	}

	std::cout << sum << std::endl;

	return 0;
}
