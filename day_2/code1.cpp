#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>

#include "../utils.cpp"

int pre_process(std::string &in) {
	in = std::regex_replace(in, std::regex("Game "), "");
	std::string game_nr = in.substr(0, in.find(':'));
	in = std::regex_replace(in, std::regex("blue"), "b");
	in = std::regex_replace(in, std::regex("green"), "g");
	in = std::regex_replace(in, std::regex("red"), "r");
	in = std::regex_replace(in, std::regex(" "), "");
	in = std::regex_replace(in, std::regex(".*:"), "");

	return stoi(game_nr);
}

bool compare(int nr, char color) {
	int r{12}, g{13}, b{14};
	switch (color) {
		case 'r': 
			return nr > r;
		case 'g': 
			return nr > g;
		case 'b': 
			return nr > b;
	}
	return false;
}

int process(std::string &in, int game_nr) {

	bool possible{true};

	for_all_substrings(in, ";", [&possible](std::string token){

		for_all_substrings(std::move(token), ",", [&possible](std::string subtoken){
			char last = subtoken.back();
			subtoken.pop_back();
			possible = !compare(stoi(subtoken), last) && possible;
		});

	});

	return (possible) ? game_nr : 0;
}

int main() {
	std::string line;
	std::ifstream file_in;
	int sum{0};

	file_in.open ("data.txt", std::ifstream::in);

	if (file_in.is_open())
	{
		while(getline(file_in, line)) {
			int game_nr = pre_process(line);
			sum += process(line, game_nr);
		}
		file_in.close();
	}

	std::cout << sum << std::endl;

	return 0;
}
