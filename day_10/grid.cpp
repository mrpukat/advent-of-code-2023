#include <string>
#include <vector>
#include <sstream>
#include <queue>
#include <iostream>

struct node {
    node *upp{nullptr}, *down{nullptr}, *rigth{nullptr}, *left{nullptr};
    char type;
    bool traveld{false};
    int cost{-1};
};

class towd_array {

    std::vector<std::vector<node>> array;

    void for_each_neigbur(int x, int y, std::function< void(node &, int) >&& f) {

        // .2.
        // 1S3
        // .4.

        if (x > 0) {
            f(array.at(y).at(x - 1), 1);
        }
        if (x < higth() - 1) {
            f(array.at(y).at(x + 1), 3);
        }

        if (y > 0) {
            f(array.at(y - 1).at(x), 2);
        }

        if (y < with() - 1) {
            f(array.at(y + 1).at(x), 4);
        }
    }

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

    bool is_connected(const node &a, const node &b, int p) {
        if (b.type == '.' || a.type == '.') return false;


        //std::cout << a.type << " " << b.type << " " << p << std::endl;
        if (p == 1) {
            bool center = a.type == '-' || a.type == 'J' || a.type == '7' || a.type == 'S';
            bool connect = b.type == '-' || b.type == 'L' || b.type == 'F' || b.type == 'S';
            return center && connect;
        }
        if (p == 2) {
            bool center = a.type == '|' || a.type == 'J' || a.type == 'L' || a.type == 'S';
            bool connect = b.type == '|' || b.type == '7' || b.type == 'F' || b.type == 'S';
            return center && connect;
        }
        if (p == 3) {
            bool center = a.type == '-' || a.type == 'L' || a.type == 'F' || a.type == 'S';
            bool connect = b.type == '-' || b.type == 'J' || b.type == '7' || b.type == 'S';
            return center && connect;
        }
        if (p == 4) {
            bool center = a.type == '|' || a.type == 'F' || a.type == '7' || a.type == 'S';
            bool connect = b.type == '|' || b.type == 'L' || b.type == 'J' || b.type == 'S';
            return center && connect;
        }

        throw;
    }

    node *build_grid() {
        node *start;
        for (int i{0}; i < array.size(); ++i) {
            for (int j{0}; j < array.at(i).size(); ++j) {
                node &center = array.at(i).at(j);
                //std::cout << center.type << " ";
                if (center.type == 'S') {
                    start = &center;
                    //std::cout << ":()" << std::endl;
                }
                for_each_neigbur(j, i, [&center, this, i, j](node &n, int p){
                    //std::cout << center.type << " " << n.type << " " << p << std::endl;
                    //std::cout << i << " " << j << std::endl;
                    if (is_connected(center, n, p)) {
                        //std::cout << "!" << std::endl;
                        if (p == 1) {
                            center.left = &n;
                        } else if (p == 2) {
                            center.upp = &n;
                        } else if (p == 3) {
                            center.rigth = &n;
                        } else if (p == 4) {
                            center.down = &n;
                        }
                    }
                });
            }
            //std::cout << std::endl;
        }
        return start;
    }

    int search_grid(node *start) {
        start->traveld = true;
        start->cost = 0;
        std::queue<node *> q;
        q.push(start);
        int largest{0};

        while (!q.empty()) {

            node *curent = q.front();
            q.pop();
            largest = (largest < curent->cost) ? curent->cost : largest;
            //std::cout << curent->type << std::endl;

            if(curent->down != nullptr && !curent->down->traveld) {
                curent->down->traveld = true;
                curent->down->cost = curent->cost +1;
                q.push(curent->down);
            }
            if(curent->upp != nullptr && !curent->upp->traveld) {
                curent->upp->traveld = true;
                curent->upp->cost = curent->cost +1;
                q.push(curent->upp);
            }
            if(curent->rigth != nullptr && !curent->rigth->traveld) {
                curent->rigth->traveld = true;
                curent->rigth->cost = curent->cost +1;
                q.push(curent->rigth);
            }
            if(curent->left != nullptr && !curent->left->traveld) {
                curent->left->traveld = true;
                curent->left->cost = curent->cost +1;
                q.push(curent->left);
            }

        }

        return largest;

    }

};