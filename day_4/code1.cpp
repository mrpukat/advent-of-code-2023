#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>

#include "../utils.cpp"

void pre_process(std::string &in) {
	in = std::regex_replace(in, std::regex("Card .{1,3}: "), "");
}


int process(std::string &in) {

	int sum{0};
	std::vector<int> winning;

	for_all_substrings(in, "|", [&sum, &winning](std::string token){

		bool first = winning.empty();

		for_all_numbers<int>(token, [&sum, first, &winning](int number, int, int){

			if (first) {
				winning.push_back(number);
			} else {

                if (std::find(winning.begin(), winning.end(), number) != winning.end()) {
					sum = (sum == 0) ? 1 : sum*2;
                }
			}

		});

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
		while(getline(file_in, line)) {
			pre_process(line);
			sum += process(line);
		}
		file_in.close();
	}

	std::cout << sum << std::endl;

	return 0;
}
