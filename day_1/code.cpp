#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>

void pre_process(std::string &in) {
	in = std::regex_replace(in, std::regex("one"), "one1one");
	in = std::regex_replace(in, std::regex("two"), "two2two");
	in = std::regex_replace(in, std::regex("three"), "three3three");
	in = std::regex_replace(in, std::regex("four"), "four4four");
	in = std::regex_replace(in, std::regex("five"), "five5five");
	in = std::regex_replace(in, std::regex("six"), "six6six");
	in = std::regex_replace(in, std::regex("seven"), "seven7seven");
	in = std::regex_replace(in, std::regex("eight"), "eight8eight");
	in = std::regex_replace(in, std::regex("nine"), "nine9nine");
}

int process(std::stringstream &in) {
	char first = 'a', last = 'a';
	std::for_each(std::istreambuf_iterator<char>(in),
               	  std::istreambuf_iterator<char>(),
                  [&first, &last](char ch) {
				   if (isdigit(ch)) {
					first = (first == 'a') ? ch : first;
					last = ch;
				   }
				  });

	std::string combined({first, last});
	return stoi(combined);
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
			std::stringstream ss(line);
			sum += process(ss);
		}
		file_in.close();
	}

	std::cout << sum << std::endl;

	return 0;
}
