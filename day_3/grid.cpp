#include <string>
#include <vector>

#include "../utils.cpp"

class towd_array {

    std::vector<std::string> array;

    void push_cord_to_vector(std::vector<std::string> &pos, int y, int x) {
        std::string a;
        a.append(std::to_string(y));
        a.append(",");
        a.append(std::to_string(x));
        pos.push_back(std::move(a));
    }

    void has_neighbor_at(int x, int y, char cmp, std::vector<std::string> &pos) {

        if (x > 0) {
            if(array.at(y).at(x - 1) == cmp) {
                push_cord_to_vector(pos, y, x-1);
            }
        }
        if (x < higth() - 1) {
            if(array.at(y).at(x + 1) == cmp) {
                push_cord_to_vector(pos, y, x+1);
            }
        }

        if (y > 0) {
            if(array.at(y - 1).at(x) == cmp) {
                push_cord_to_vector(pos, y-1, x);
            }
            if (x > 0) {
                if(array.at(y - 1).at(x - 1) == cmp) {
                    push_cord_to_vector(pos, y-1, x-1);
                }
            }
            if (x < higth() - 1) {
                if(array.at(y - 1).at(x + 1) == cmp) {
                    push_cord_to_vector(pos, y-1, x+1);
                }
            }
        }

        if (y < with() - 1) {
            if(array.at(y + 1).at(x) == cmp) {
                push_cord_to_vector(pos, y+1, x);
            }
            if (x > 0) {
                if(array.at(y + 1).at(x - 1) == cmp) {
                    push_cord_to_vector(pos, y+1, x-1);
                }
            }
            if (x < higth() - 1) {
                if(array.at(y + 1).at(x + 1) == cmp) {
                   push_cord_to_vector(pos, y+1, x+1);
                }
            }
        }
    }

    public:

    int higth() {return array.size();}
    int with() {return array.at(0).length();}

    void append_line(std::string &line) {
        array.push_back(line);
    }

    void for_all_numbers_in_line(int y, std::function< void( int, int, int ) >&& f) {
        std::string in = array.at(y);
        for_all_numbers<int>(std::move(in), std::move(f));
    }

    std::string digit_has_neighbor_at(int y, int digit, int start, int stop) {
        std::vector<std::string> pos_list;
        const char *cmp = "X";
        for (int x{start}; x < stop; ++x) {
            std::vector<std::string> pos;
            has_neighbor_at(x, y, *cmp, pos);

            for (auto &tmp : pos) {  
                if (std::find(pos_list.begin(), pos_list.end(), tmp) == pos_list.end()) {
                    pos_list.push_back(tmp);
                }
            }
        }

        std::ostringstream posstr;
        std::copy(pos_list.begin(), pos_list.end(), std::ostream_iterator<std::string>(posstr, "_"));

        return posstr.str();
    }

};