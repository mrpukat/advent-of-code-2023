#include <string>
#include <vector>
#include <sstream>
#include <queue>
#include <iostream>

using cord = std::pair<int, int>;

struct node {
    char type = '.';
};

class towd_array {

    std::vector<std::vector<node>> array;

    public:

    int higth() {return array.size();}
    int with() {return array.at(0).size();}

    void append_line(std::string &line) {
        array.push_back(
            std::vector<node>()
        );
        for(char c : line) {
            node n;
            n.type = c;
            array.back().push_back(n);
        }
    }

    std::string get_row(int y) {
        std::string res;
        for (int i{0}; i < with(); ++i) {
            res.push_back(array.at(y).at(i).type);
        }

        return std::move(res);
    }

    std::string get_col(int x) {
        std::string res;
        for (int i{0}; i < higth(); ++i) {
            res.push_back(array.at(i).at(x).type);
        }

        return std::move(res);
    }


    

};