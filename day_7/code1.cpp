#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>
#include <map>

#include "../utils.cpp"

using bet = std::pair<std::string, int>;

std::map<char, int> g_rank {
	{'A', 14},
	{'K', 13},
	{'Q', 12},
	{'J', 0},
	{'T', 10},
	{'9', 9},
	{'8', 8},
	{'7', 7},
	{'6', 6},
	{'5', 5},
	{'4', 4},
	{'3', 3},
	{'2', 2},
	{'1', 1},
};

std::map<std::vector<int>, int> g_prank {
	{{5}, 7},
	{{4}, 6},
	{{3,2}, 5},
	{{2,3}, 5},
	{{3}, 4},
	{{2,2}, 3},
	{{2}, 2},
	{{}, 1},
};

int pair_rank(std::vector<int> &v, int w) {

	if (std::find(v.begin(), v.end(), 5) != v.end()) {
		return 7;
	}
	if (std::find(v.begin(), v.end(), 4) != v.end()) {
		if (w != 0) {
			return 7;
		}
		return 6;
	}


	if (std::find(v.begin(), v.end(), 3) != v.end()) {
		if (w != 0) {
			return 5 + w;
		}
		if (std::find(v.begin(), v.end(), 2) != v.end()) {
			return 5;
		}
		return 4;
	}

	if (std::find(v.begin(), v.end(), 2) != v.end()) {
		if (w == 1) {
			if (v.size() != 1) {
				return 5;
			}
			return 4;
		}
		if (w > 1) {
			return 4 + w;
		}
		if (v.size() == 1) {
			return 2;
		} else {
			return 3;
		}
	}

	if (!v.empty()) throw ":(";

	if (w == 1) {
		return 2;
	}
	if (w == 2) {
		return 4;
	}
	if (w == 3) {
		return 6;
	}
	if (w == 3) {
		return 6;
	}
	if (w > 3) {
		return 7;
	}

	return 1;
}

int get_order(const std::string &a) {
	std::vector<int> pars;
	std::vector<char> processed;
	int wildcards{0};
	for (const char el : a) {
		if (std::find(processed.begin(), processed.end(), el) != processed.end()) {
			continue;
		}
		int count{0};
		for (const char comp : a) {
			if(el == 'J') {
				wildcards += (el == comp) ? 1 : 0;
			} else {
				count += (el == comp) ? 1 : 0;
			}
		}
		if (count > 1) {
			pars.push_back(count);
		}
		processed.push_back(el);
	}

	int rank = pair_rank(pars, wildcards);
	//std::copy(pars.begin(), pars.end(), std::ostream_iterator<int>(std::cout, " "));
	//std::cout << " (" << wildcards << ") :" << rank << std::endl;


	return rank;
}

bool comparitor(const std::string &a, const std::string &b) {

	int oa{get_order(a)}, ob{get_order(b)};
	if (oa != ob) {
		return oa > ob;
	}

	for(int i{0}; i < a.size(); ++i) {
		if (g_rank[a.at(i)] != g_rank[b.at(i)]) {
			return g_rank[a.at(i)] > g_rank[b.at(i)];
		}
	}

	return true;

}

void process(std::string &in, std::vector<bet> &bets) {

	std::vector<std::string> tmp;
	aoc::for_all_substrings(in, " ", [&tmp](std::string str){
		tmp.push_back(str);
	});

	bets.push_back(bet{tmp.at(0),stoi(tmp.at(1))});
}

int main() {
	std::string line;
	std::ifstream file_in;
	long long res{0};

	file_in.open ("data.txt", std::ifstream::in);

	std::vector<bet> bets;
	if (file_in.is_open())
	{
		while(getline(file_in, line)) {
			process(line, bets);
		}

		file_in.close();
	}

	std::sort(bets.begin(), bets.end(), [](const bet &a, const bet &b){
		return !comparitor(a.first, b.first);
	});

	for(int i{0}; i < bets.size(); ++i) {
		res += bets.at(i).second * (i+1);
		std::cout << bets.at(i).first << std::endl;
	}

	std::cout << res << std::endl;

	return 0;
}
