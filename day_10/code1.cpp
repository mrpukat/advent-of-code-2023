#include <iostream>
#include <fstream>
#include <regex>

#include "../utils.cpp"
#include "grid.cpp"

void pre_process(std::string &in, towd_array &grid) {
	grid.append_line(in);
}

// BFS problem
void process(std::string &in) {

}

int main() {
	towd_array grid;
	std::string line;
	std::ifstream file_in;
	long sum{0};

	file_in.open ("data.txt", std::ifstream::in);

	if (file_in.is_open())
	{
		while(getline(file_in, line)) {
			pre_process(line, grid);
		}
		file_in.close();
	}
	node *start = grid.build_grid();

	sum = grid.search_grid(start);

	std::cout << sum << std::endl;

	return 0;
}
