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

    void expand(std::vector<int> &col, std::vector<int> &row) {

    	for(auto it = array.begin(); it != array.end(); ++it) {
            bool empty_row{true};
            for(auto jt = it->begin(); jt != it->end(); ++jt) {
                empty_row = (jt->type == '#') ? false : empty_row;
            }
            if (empty_row) {
                row.push_back(it - array.begin());
                //it = ++array.insert(it, std::vector<node>(with()));
            }
        }
        

        for (int i{0}; i < with(); ++i) {
            bool empty_col{true};
            for (int j{0}; j < higth(); ++j) {
                empty_col = (array.at(j).at(i).type == '#') ? false : empty_col;
            }
            if (empty_col) {
                /*
                for (int j{0}; j < higth(); ++j) {
                    array.at(j).insert(array.at(j).begin() + i, node());
                }
                ++i;
                */
               col.push_back(i);
            }
        }
    }


    void find_pairs(std::vector<cord> &pos, std::vector<int> &col, std::vector<int> &row, int force) {

        int col_tot{0};

    	for(auto it = array.begin(); it != array.end(); ++it) { // Collumn
//            if (!col.empty()) {
//                std::cout << "next col: " << col.front() << std::endl;            
//            }
            if (!col.empty() && col.front() == it - array.begin()) {
//                std::cout << "Col " << col.front() << std::endl;
                col_tot += force;
                col.erase(col.begin());
            }

            int row_tot{0};
            std::vector<int> tmp_row = row;
            for(auto jt = it->begin(); jt != it->end(); ++jt) { // Row
//                if (!tmp_row.empty()) {
//                    std::cout << "next row: " << tmp_row.front() << std::endl;            
//                }
                if (!tmp_row.empty() && tmp_row.front() == jt - it->begin()) {
//                    std::cout << "Row " << tmp_row.front() << std::endl;
                    row_tot += force;
                    tmp_row.erase(tmp_row.begin());
                }
//                std::cout << it - array.begin() + col_tot << " " << jt - it->begin() + row_tot << std::endl;

                if (jt->type == '#') {
//                    std::cout << "found #: " << it - array.begin() + col_tot << " " << jt - it->begin() + row_tot << std::endl;
                    pos.push_back(cord{it - array.begin() + col_tot, jt - it->begin() + row_tot});
                }
            }
        }
    }

};