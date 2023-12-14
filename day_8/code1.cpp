#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>
#include <map>

#include "../utils.cpp"

void pre_process(std::string &in) {
	in = std::regex_replace(in, std::regex(" "), "");
	in = std::regex_replace(in, std::regex("\\("), "");
	in = std::regex_replace(in, std::regex("\\)"), "");
}

void process(std::string &in, std::map<std::string, std::string> &rmap, std::map<std::string, std::string> &lmap) {

	std::string start;

	for_all_substrings(in, "=", [&rmap, &lmap, &start](std::string token){

		if(token.length() == 3) {
			start = token;
		} else {
			bool first{true};
			for_all_substrings(std::move(token), ",", [&rmap, &lmap, &start, &first](std::string subtoken){
				if (first) {
					first = false;
					lmap[start] = subtoken;
				} else {
					rmap[start] = subtoken;
				}
			});
		}

	});

}

int main() {
	std::string line;
	std::ifstream file_in;
	int steps{0};

	file_in.open ("data.txt", std::ifstream::in);

	std::map<std::string, std::string> rmap;
	std::map<std::string, std::string> lmap;	
	if (file_in.is_open())
	{

		std::vector<char> instuctions;
		getline(file_in, line);
		std::stringstream ss(line);
		std::for_each(std::istreambuf_iterator<char>(ss),
					std::istreambuf_iterator<char>(),
					[&instuctions](char ch) {
					instuctions.push_back(ch);
					});


		while(getline(file_in, line)) {
			if(!line.empty()) {
				pre_process(line);
				process(line, rmap, lmap);

			}
		}

		std::string posision = "AAA";

		while(posision != "ZZZ") {
			for(char i : instuctions) {
				if (i == 'R') {
					posision = rmap[posision];
					steps++;
				}
				else if (i == 'L') {
					posision = lmap[posision];
					steps++;
				}
				if (posision == "ZZZ") {break;}
			}
		}

		file_in.close();
	}

	std::cout << steps << std::endl;

	return 0;
}
