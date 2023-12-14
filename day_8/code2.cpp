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

bool all_end_with(const std::vector<std::string> &v, char c) {
	bool res{true};
	for (const auto &el : v) {
		res = res && (el.back() == c);
	}
	return res;
}

int main() {
	std::string line;
	std::ifstream file_in;
	long long steps{0};

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

		std::vector<std::string> posisions;
		for (const auto el : rmap) {
			if (el.first.back() == 'A') {
				posisions.push_back(el.first);
			}
		}

		while(!all_end_with(posisions, 'Z')) {
			for(const char &c : instuctions) {
				if (c == 'R') {
					for (auto &pos : posisions) {
						pos = rmap[pos];
					}
					steps++;
				}
				else if (c == 'L') {
					for (auto &pos : posisions) {
						pos = lmap[pos];
					}
					steps++;
				}
				if (all_end_with(posisions, 'Z')) {break;}
				//std::copy(posisions.begin(), posisions.end(), std::ostream_iterator<std::string>(std::cout, " "));
				//std::cout << std::end;
			}
			std::cout << steps << std::endl;
		}

		file_in.close();
	}

	std::cout << steps << std::endl;

	return 0;
}
