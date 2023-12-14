#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>

#include "../utils.cpp"

void pre_process(std::string &in) {
	in = std::regex_replace(in, std::regex("Game .{1,3}:"), "");
	in = std::regex_replace(in, std::regex("blue"), "b");
	in = std::regex_replace(in, std::regex("green"), "g");
	in = std::regex_replace(in, std::regex("red"), "r");
	in = std::regex_replace(in, std::regex(" "), "");
}


int process(std::string &in) {
	int r{0}, g{0}, b{0};

	for_all_substrings(in, ";", [&r,&g, &b](std::string token){

		for_all_substrings(std::move(token), ",", [&r,&g, &b](std::string subtoken){
			char last = subtoken.back();
			subtoken.pop_back();
			int nr = stoi(subtoken);

			switch (last) {
				case 'r': 
					r = (nr > r) ? nr : r;
					break;
				case 'g': 
					g = (nr > g) ? nr : g;
					break;
				case 'b': 
					b = (nr > b) ? nr : b;
					break;
			}

		});

	});

	return r*g*b;
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
