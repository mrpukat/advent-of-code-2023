#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>

#include "../utils.cpp"

void process(std::string &in, std::vector<long long> &current, std::vector<long long> &future) {

	std::vector<long long> tmp;

	aoc::for_all_numbers<long long>(in, [&tmp](long long number, int, int){
		tmp.push_back(number);
	});

	long long destination{tmp.at(0)};
	long long source{tmp.at(1)};
	long long range{tmp.at(2)};
 
	for(auto it = current.begin(); it != current.end();) {
		long long diff = *it - source;
		if (0 <= diff && diff < range) {
			future.push_back(destination + diff);
			it = current.erase(it);
		} else {
			++it;
		}
	}
}

int main() {
	std::string line;
	std::ifstream file_in;
	long long min_value{0};

	file_in.open ("data.txt", std::ifstream::in);

	std::vector<long long> current;
	std::vector<long long> future;
	if (file_in.is_open())
	{

		getline(file_in, line);
		aoc::for_all_numbers<long long>(line, [&current](long long number, int, int){
			current.push_back(number);
		});

		while(getline(file_in, line)) {
			if(!line.empty()) {

				if (line.find(":") != std::string::npos) {
					for (long long el : current) {
						future.push_back(el);
					}
					current = future;
					future.clear();

				} else if (!current.empty()) {
					process(line, current, future);
				}
			}
		}

		for (long long el : current) {
			future.push_back(el);
		}
		current = future;
		future.clear();


		min_value = *std::min_element(current.begin(),current.end());

		file_in.close();
	}

	std::cout << min_value << std::endl;

	return 0;
}
