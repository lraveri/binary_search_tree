#include <iostream>
#include <utility>
#include <memory>
#include "bst.cpp"
#include "../include/iterator.hpp"

int main(int argc, char **argv) {

	std::cout<<"Test: ctor & insert"<<std::endl;

    std::pair<const int, int> pair1{1,1};
    std::pair<const int, int> pair2{8,1};
    std::pair<const int, int> pair3{10,1};
    std::pair<const int, int> pair4{1,1};
    std::pair<const int, int> pair5{3,1};
    std::pair<const int, int> pair6{7,1};
    std::pair<const int, int> pair7{14,1};
    std::pair<const int, int> pair8{4,1};
    std::pair<const int, int> pair9{6,1};

    bst<int,int> tree{pair1};
    tree.insert(pair2);
    tree.insert(pair3);
    tree.insert(pair4);
    tree.insert(pair5);
    tree.insert(pair6);
    tree.insert(pair7);
    tree.insert(pair8);
    tree.insert(pair9);

    std::cout<<"Expected:"<<std::endl;
    std::cout<<tree<<std::endl;

	return 0;
}
