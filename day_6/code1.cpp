#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>
#include <math.h>

#include "../utils.cpp"

void pre_process(std::string &in) {
	in = std::regex_replace(in, std::regex(" "), "");
}

long process(long time, long record) {

	long double time2 = time;
	time2 /= 2;
	long double rec2 = record;
	
	rec2 = sqrt(time2*time2 - rec2);
	return (long)(time2 + rec2 -0.00001) - (long)((time2 - rec2) +0.00001);
}

int main() {
	std::string line;
	std::ifstream file_in;
	long sum{1};

	file_in.open ("data.txt", std::ifstream::in);

	std::vector<long> time;
	std::vector<long> distance;
	if (file_in.is_open())
	{

		getline(file_in, line);
		pre_process(line);
		aoc::for_all_numbers<long>(line, [&time](long number, int, int){
			time.push_back(number);
		});

		getline(file_in, line);
		pre_process(line);
		aoc::for_all_numbers<long>(line, [&distance](long number, int, int){
			distance.push_back(number);
		});

		for (int i{0}; i < time.size(); ++i) {
			sum *= process(time.at(i), distance.at(i));
		}


		file_in.close();
	}

	std::cout << sum << std::endl;

	return 0;
}
