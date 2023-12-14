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
	std::vector<int> row, col;
	grid.expand(col, row);
	std::vector<cord> pos;
	grid.find_pairs(pos, row, col, 999999); 
	// 1000000
	//  999999

	for (auto it = pos.begin(); it != pos.end(); ++it) {
		for (auto jt = it; jt != pos.end(); ++jt) {
			sum += abs(it->first - jt->first) + abs(it->second - jt->second);
		}
	}

	std::cout << sum << std::endl;

	return 0;
}
