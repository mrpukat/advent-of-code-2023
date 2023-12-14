#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>

#include "../utils.cpp"
#include "grid.cpp"

void pre_process(std::string &in, towd_array &grid) {
	in = std::regex_replace(in, std::regex("[^0-9\\.]+"), "X");
	grid.append_line(in);
}


int process(towd_array &grid, int y) {

	int sum{0};

	grid.for_all_numbers_in_line(y, [&sum, &y, &grid](int digit, int start, int end){

		if(grid.digit_has_neighbor_at(y, digit, start, end).length() != 0) {
			sum += digit;
		}
	});

	return sum;
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
		for (int i{0}; i < grid.higth(); ++i) { // can use algorith, need wrapper for each
			sum += process(grid, i);
		}
		file_in.close();
	}

	std::cout << sum << std::endl;

	return 0;
}
