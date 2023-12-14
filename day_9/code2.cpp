#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>

#include "../utils.cpp"

long process(std::string &in) {

	std::vector<long> seq;
	std::vector<long> next;

	for_all_numbers<long>(in, [&seq](long number, int, int){
		seq.push_back(number);
	});

	std::vector<long> last;
	bool not_all_zero{true};
	while(not_all_zero) {
		not_all_zero = false;
		last.push_back(seq.at(0));
		for(int i{1}; i < seq.size(); ++i) {
			next.push_back(seq.at(i) - seq.at(i - 1));
			not_all_zero = (next.back() != 0) ? true : not_all_zero;
		}
		seq = next;
		next.clear();
	}

	long res{0};
	while(!last.empty()) {
		res = last.back() - res;
		last.pop_back();
	}
	std::cout << std::endl;

	return res;
}

int main() {
	std::string line;
	std::ifstream file_in;
	long sum{0};

	file_in.open ("data.txt", std::ifstream::in);

	if (file_in.is_open())
	{
		while(getline(file_in, line)) {
			sum += process(line);
		}

		file_in.close();
	}

	std::cout << sum << std::endl;

	return 0;
}
