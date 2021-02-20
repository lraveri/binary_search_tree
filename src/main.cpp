#include <iostream>
#include <utility>
#include <memory>
#include "bst.cpp"

int main() {

	std::cout<<"******************************************************************************"<<std::endl;
	std::cout<<"Test: Constructors & insert"<<std::endl;
	std::cout<<"we construct a tree of int, we insert some values and we print the tree."<<std::endl;
	std::cout<<"******************************************************************************"<<std::endl;

    std::pair<const int, int> pair1{1,1};
    std::pair<const int, int> pair2{8,1};
    std::pair<const int, int> pair3{10,1};
    std::pair<const int, int> pair4{3,1};
    std::pair<const int, int> pair5{7,1};
    std::pair<const int, int> pair6{14,1};
    std::pair<const int, int> pair7{4,1};
    std::pair<const int, int> pair8{6,1};

    bst<int,int> tree{pair1};
    tree.insert(pair2);
    tree.insert(pair3);
    tree.insert(pair4);
    tree.insert(pair5);
    tree.insert(pair6);
    tree.insert(pair7);
    tree.insert(pair8);

    std::cout<<"Expected:"<<std::endl;
	std::cout<<"[1,1] [3,1] [4,1] [6,1] [7,1] [8,1] [10,1] [14,1]"<<std::endl;
	std::cout<<"Result:"<<std::endl;
    std::cout<<tree<<std::endl;

	std::cout<<"******************************************************************************"<<std::endl;
	std::cout<<"Test: insert"<<std::endl;
	std::cout<<"we insert a key already present in the tree."<<std::endl;
	std::cout<<"******************************************************************************"<<std::endl;

	std::cout<<"Expected:"<<std::endl;
	std::cout<<"[1,1] [3,1] [4,1] [6,1] [7,1] [8,1] [10,1] [14,1]"<<std::endl;
	std::cout<<"Result:"<<std::endl;

	std::pair<const int, int> pair9{1,1};
	tree.insert(pair9);
	std::cout<<tree<<std::endl;

	std::cout<<"******************************************************************************"<<std::endl;
	std::cout<<"Test: find"<<std::endl;
	std::cout<<"we find a key already present in the tree."<<std::endl;
	std::cout<<"******************************************************************************"<<std::endl;

	std::cout<<"Expected:"<<std::endl;
	std::cout<<"Key found."<<std::endl;
	std::cout<<"Result:"<<std::endl;

	int key1{8};
	if(tree.find(key1)==tree.end()) {
		std::cout<<"Key not found."<<std::endl;
	} else {
		std::cout<<"Key found."<<std::endl;
	}

	std::cout<<"******************************************************************************"<<std::endl;
	std::cout<<"Test: find"<<std::endl;
	std::cout<<"we find a key that is not present in the tree."<<std::endl;
	std::cout<<"******************************************************************************"<<std::endl;

	std::cout<<"Expected:"<<std::endl;
	std::cout<<"Key not found."<<std::endl;
	std::cout<<"Result:"<<std::endl;
	
	int key2{99};
	if(tree.find(key2)==tree.end()) {
		std::cout<<"Key not found."<<std::endl;
	} else {
		std::cout<<"Key found."<<std::endl;
	}

	std::cout<<"******************************************************************************"<<std::endl;
	std::cout<<"Test: operator[]"<<std::endl;
	std::cout<<"we access to a value throught the [] operator."<<std::endl;
	std::cout<<"******************************************************************************"<<std::endl;

	std::cout<<"Expected:"<<std::endl;
	std::cout<<"4"<<std::endl;
	std::cout<<"Result:"<<std::endl;

	int key3{77};
	std::pair<const int, int> pair10{77,4};
	tree.insert(pair10);
	auto value = tree[key3];
	std::cout<<value<<std::endl;

	std::cout<<"******************************************************************************"<<std::endl;
	std::cout<<"Test: clear"<<std::endl;	
	std::cout<<"we clear the tree, than we insert a new element."<<std::endl;
	std::cout<<"******************************************************************************"<<std::endl;

	std::cout<<"Expected:"<<std::endl;
	std::cout<<"[16,1]"<<std::endl;
	std::cout<<"Result:"<<std::endl;

	tree.clear();
	std::pair<const int, int> pair11{16,1};
	tree.insert(pair11);
	std::cout<<tree<<std::endl;

	std::cout<<"******************************************************************************"<<std::endl;
	std::cout<<"Test: copy semantics."<<std::endl;
	std::cout<<"******************************************************************************"<<std::endl;

    bst<int,int> tree2{}; 

	tree.clear();
    tree.insert(pair1);
    tree.insert(pair2);
    tree.insert(pair3);
    tree.insert(pair4);
    tree.insert(pair5);
    tree.insert(pair6);
    tree.insert(pair7);
    tree.insert(pair8);

    tree2=tree;
	tree.clear();
	std::cout<<"Expected:"<<std::endl;
	std::cout<<"[1,1] [3,1] [4,1] [6,1] [7,1] [8,1] [10,1] [14,1]"<<std::endl;
	std::cout<<"Result:"<<std::endl;
    std::cout<<tree2<<std::endl;

    tree.insert(pair1);
    tree.insert(pair2);
    tree.insert(pair3);
    tree.insert(pair4);
    tree.insert(pair5);
    tree.insert(pair6);
    tree.insert(pair7);
    tree.insert(pair8);

	bst<int,int> tree3{tree};
	std::cout<<"Expected:"<<std::endl;
	std::cout<<"[1,1] [3,1] [4,1] [6,1] [7,1] [8,1] [10,1] [14,1]"<<std::endl;
	std::cout<<"Result:"<<std::endl;
	std::cout<<tree3<<std::endl;

	std::cout<<"******************************************************************************"<<std::endl;
	std::cout<<"Test: move semantics."<<std::endl;
	std::cout<<"******************************************************************************"<<std::endl;

	bst<int,int> tree4{std::move(tree)};
	tree.clear();
	std::cout<<"Expected:"<<std::endl;
	std::cout<<"[1,1] [3,1] [4,1] [6,1] [7,1] [8,1] [10,1] [14,1]"<<std::endl;
	std::cout<<"Result:"<<std::endl;
	std::cout<<tree4<<std::endl;

	tree3.clear();
	tree3 = std::move(tree4);
	tree4.clear();
	std::cout<<"Expected:"<<std::endl;
	std::cout<<"[1,1] [3,1] [4,1] [6,1] [7,1] [8,1] [10,1] [14,1]"<<std::endl;
	std::cout<<"Result:"<<std::endl;
	std::cout<<tree3<<std::endl;

	std::cout<<"******************************************************************************"<<std::endl;
	std::cout<<"Test: erase"<<std::endl;
	std::cout<<"******************************************************************************"<<std::endl;

	std::cout<<"Expected:"<<std::endl;
	std::cout<<"[1,1] [3,1] [4,1] [6,1] [7,1] [8,1] [14,1]"<<std::endl;
	std::cout<<"Result:"<<std::endl;

    tree.insert(pair1);
    tree.insert(pair2);
    tree.insert(pair3);
    tree.insert(pair4);
    tree.insert(pair5);
    tree.insert(pair6);
    tree.insert(pair7);
    tree.insert(pair8);

	tree.erase(10);

	std::cout<<tree<<std::endl;

	std::cout<<"******************************************************************************"<<std::endl;
	std::cout<<"Test: printChildren"<<std::endl;
	std::cout<<"******************************************************************************"<<std::endl;

	std::cout<<"Expected:"<<std::endl;
	std::cout<<"node = 8 -> left child = 3, right child = 14"<<std::endl;
	std::cout<<"Result:"<<std::endl;

	tree.printChildren(8);

	std::cout<<"******************************************************************************"<<std::endl;
	std::cout<<"Test: balance"<<std::endl;
	std::cout<<"******************************************************************************"<<std::endl;
	
	std::cout<<"Tree:"<<std::endl;
	std::cout<<tree<<std::endl;	

	std::cout<<"Tree before balance invocation:"<<std::endl;

	tree.printChildren(1);
	tree.printChildren(3);
	tree.printChildren(4);
	tree.printChildren(6);
	tree.printChildren(7);
	tree.printChildren(8);
	tree.printChildren(14);
	
	tree.balance();

	std::cout<<"Tree after balance invocation:"<<std::endl;

	tree.printChildren(1);
	tree.printChildren(3);
	tree.printChildren(4);
	tree.printChildren(6);
	tree.printChildren(7);
	tree.printChildren(8);
	tree.printChildren(14);

	std::cout<<"******************************************************************************"<<std::endl;
	std::cout<<"Test: emplace"<<std::endl;
	std::cout<<"******************************************************************************"<<std::endl;

	tree.emplace(5,2);

	std::cout<<"Expected:"<<std::endl;
	std::cout<<"[1,1] [3,1] [4,1] [5,2] [6,1] [7,1] [8,1] [14,1]"<<std::endl;
	std::cout<<"Result:"<<std::endl;
	std::cout<<tree<<std::endl;

	return 0;
}