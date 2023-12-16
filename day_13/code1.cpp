#include <iostream>
#include <fstream>
#include <regex>

#include "../utils.cpp"
#include "grid.cpp"

void pre_process(std::string &in, towd_array &grid) {
	grid.append_line(in);
}

bool one_off_cmp(const std::string &a, const std::string &b) {

	if (a.size() != b.size()) {
		throw a + " " + b;
	}

	bool diff{false};
	for (int i{0}; i < a.size(); ++i) {
		if (a.at(i) != b.at(i)) {
			if (!diff) {
				diff = true;
			} else {
				return false;
			}
		}
	}

	return diff;
}

void process(towd_array &grid, long &col, long &row) {

	// Rowns

	for(int i{1}; i < grid.higth(); ++i) {
		
		int a{i-1}, b{i};
		bool mirror{true}, one_err{false};
		while(a >= 0 && b < grid.higth()) {
			std::string first = grid.get_row(a), secend = grid.get_row(b);
			if(first != secend) {
				bool one_off = one_off_cmp(first,secend);
				if(one_off && !one_err && false) {
					one_err = true;
				} else {
					mirror = false;
					break;
				}
			}
			--a;
			++b;
		}
		if (mirror) {
			row += i;
			std::cout << "Row at " << i << std::endl;
			return;
		}
	}


	// Cols

	for(int i{1}; i < grid.with(); ++i) {
		
		int a{i-1}, b{i};
		bool mirror{true}, one_err{false};
		while(a >= 0 && b < grid.with()) {
			std::string first = grid.get_col(a), secend = grid.get_col(b);
			if(first != secend) {
				bool one_off = one_off_cmp(first,secend);
				if(one_off && !one_err && false) {
					one_err = true;
				} else {
					mirror = false;
					break;
				}
			}
			--a;
			++b;
		}
		if (mirror) {
			col += i;
			std::cout << "Col at " << i << std::endl;
			return;
		}
	}
}

int main() {
	towd_array grid;
	std::string line;
	std::ifstream file_in;
	long row{0}, col{0};

	file_in.open ("data.txt", std::ifstream::in);

	if (file_in.is_open())
	{
		while(getline(file_in, line)) {

			if (!line.empty()) {
				pre_process(line, grid);
			} else {
				process(grid, col, row);
				grid = towd_array();
			}

		}
		file_in.close();
	}

	std::cout << row << " " << col << std::endl;
	std::cout << row*100 + col << std::endl;

	return 0;
}
