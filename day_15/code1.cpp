#include <iostream>
#include <fstream>
#include <regex>
#include <map>

#include "../utils.cpp"

void pre_process(std::string &in) {

}

unsigned long long process(std::string &in) {

	std::map<int, std::vector<std::pair<std::string, int>>> lence;
	unsigned long long sum{0};

	aoc::for_all_substrings(in, ",", [&lence](std::string hash){

		unsigned long long tmp{0};

        size_t i{0};
        i = hash.find_first_of("-=");
        std::string lable = hash.substr(0, i);
		hash.erase(0, i);
		for(int i{0}; i < lable.size(); ++i) {
			tmp += lable.at(i);
			tmp *= 17;
			tmp = tmp % 256;
		}
		//std::cout << lable << " " << tmp << std::endl;

		auto it = std::find_if(lence[tmp].begin(), lence[tmp].end(),
			[&lable](std::pair<std::string, int> i) { 
				return i.first == lable; 
				});

		if(hash.at(0) == '=') {
			if (it != lence[tmp].end()) {
				it->second = hash.at(1) - '0';
			} else {
				lence[tmp].push_back({lable, hash.at(1) - '0'});
			}
			//std::cout << "Box " << tmp << ": [" << lable << " " << hash.at(1) << "]" << std::endl;
		} else if (it != lence[tmp].end()) {
			lence[tmp].erase(it);
		}

	});

	for (auto const& [box, slot] : lence)
	{
		int nr{0};
		for (auto const& [label, strenth] : slot)
		{
			++nr;
			// Problem map is unorderd and does not follow the order of insertion
			sum += (box + 1)*nr*strenth;
			//std::cout << label << " " << (box + 1)*nr*strenth << ": " << (box + 1) << " " << nr << " " << strenth << std::endl;
		}

	}

	return sum;

}

int main() {
	std::string line;
	std::ifstream file_in;
	unsigned long long sum{0};

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
