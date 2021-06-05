#include <iostream>
#include <utility>
#include <memory>
#include "bst.cpp"

int main() {

	std::pair<const int, int> pair1{1,1};
	std::pair<const int, int> pair2{2,1};
	std::pair<const int, int> pair3{3,1};
	std::pair<const int, int> pair4{4,1};
	std::pair<const int, int> pair5{5,1};
	std::pair<const int, int> pair6{6,1};
	std::pair<const int, int> pair7{7,1};
	std::pair<const int, int> pair8{8,1};
	std::pair<const int, int> pair9{9,1};
	std::pair<const int, int> pair10{10,1};

	std::cout<<"******************************************************************************"<<std::endl;
	std::cout<<"Test: Constructors & insert"<<std::endl;
	std::cout<<"******************************************************************************"<<std::endl;

	bst<int,int> tree{pair1};
	tree.insert(pair7);
	tree.insert(pair3);
	tree.insert(pair5);
	tree.insert(pair6);
	tree.insert(pair4);
	tree.insert(pair8);
	tree.insert(pair8);

	std::cout<<"Expected:"<<std::endl;
	std::cout<<"[1,1] [3,1] [4,1] [5,1] [6,1] [7,1] [8,1]"<<std::endl;
	std::cout<<"Result:"<<std::endl;
	std::cout<<tree<<std::endl;

	bst<int,int> tree_bis{};
	tree_bis.insert(pair7);
	tree_bis.insert(pair3);
	tree_bis.insert(pair5);
	tree_bis.insert(pair6);
	tree_bis.insert(pair4);
	tree_bis.insert(pair8);
	tree_bis.insert(pair1);

	std::cout<<"Expected:"<<std::endl;
	std::cout<<"[1,1] [3,1] [4,1] [5,1] [6,1] [7,1] [8,1]"<<std::endl;
	std::cout<<"Result:"<<std::endl;
	std::cout<<tree_bis<<std::endl;

	std::cout<<"******************************************************************************"<<std::endl;
	std::cout<<"Test: find"<<std::endl;
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
	std::cout<<"******************************************************************************"<<std::endl;

	std::cout<<"Expected:"<<std::endl;
	std::cout<<"4"<<std::endl;
	std::cout<<"Result:"<<std::endl;

	int key3{77};
	std::pair<const int, int> pair77{77,4};
	tree.insert(pair77);
	auto value = tree[key3];
	std::cout<<value<<std::endl;

	std::cout<<"Expected:"<<std::endl;
	std::cout<<"0"<<std::endl;
	std::cout<<"Result:"<<std::endl;

	int key4{88};
	auto new_val = tree[key4];
	std::cout<<new_val<<std::endl;

	std::cout<<"******************************************************************************"<<std::endl;
	std::cout<<"Test: clear"<<std::endl;	
	std::cout<<"******************************************************************************"<<std::endl;

	std::cout<<"Expected:"<<std::endl;
	std::cout<<"[11,1]"<<std::endl;
	std::cout<<"Result:"<<std::endl;

	tree.clear();
	std::pair<const int, int> pair11{11,1};
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
	std::cout<<"[1,1] [2,1] [3,1] [4,1] [5,1] [6,1] [7,1] [8,1]"<<std::endl;
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
	std::cout<<"[1,1] [2,1] [3,1] [4,1] [5,1] [6,1] [7,1] [8,1]"<<std::endl;
	std::cout<<"Result:"<<std::endl;
	std::cout<<tree3<<std::endl;

	std::cout<<"******************************************************************************"<<std::endl;
	std::cout<<"Test: move semantics."<<std::endl;
	std::cout<<"******************************************************************************"<<std::endl;

	bst<int,int> tree4{std::move(tree)};
	tree.clear();
	std::cout<<"Expected:"<<std::endl;
	std::cout<<"[1,1] [2,1] [3,1] [4,1] [5,1] [6,1] [7,1] [8,1]"<<std::endl;
	std::cout<<"Result:"<<std::endl;
	std::cout<<tree4<<std::endl;

	tree3.clear();
	tree3 = std::move(tree4);
	tree4.clear();
	std::cout<<"Expected:"<<std::endl;
	std::cout<<"[1,1] [2,1] [3,1] [4,1] [5,1] [6,1] [7,1] [8,1]"<<std::endl;
	std::cout<<"Result:"<<std::endl;
	std::cout<<tree3<<std::endl;

	std::cout<<"******************************************************************************"<<std::endl;
	std::cout<<"Test: erase"<<std::endl;
	std::cout<<"******************************************************************************"<<std::endl;

	// std::cout<<"Expected:"<<std::endl;
	// std::cout<<"[1,1] [2,1] [3,1] [4,1] [5,1] [6,1] [7,1]"<<std::endl;
	// std::cout<<"Result:"<<std::endl;

	tree.insert(pair5);
	tree.insert(pair4);
	tree.insert(pair7);
	tree.insert(pair6);
	tree.insert(pair8);

	tree.erase(7);

	std::cout<<tree<<std::endl;

	tree.printNode(5);
	tree.printNode(4);
	tree.printNode(8);
	tree.printNode(6);

	tree.clear();

	tree.insert(pair5);
	tree.insert(pair4);
	tree.insert(pair7);
	tree.insert(pair6);
	tree.insert(pair8);

	tree.erase(5);

	std::cout<<tree<<std::endl;

	tree.printNode(7);
	tree.printNode(6);
	tree.printNode(8);
	tree.printNode(4);

	tree.clear();

	tree.insert(pair5);
	tree.insert(pair7);
	tree.insert(pair6);
	tree.insert(pair8);

	tree.erase(5);

	std::cout<<tree<<std::endl;

	tree.printNode(7);
	tree.printNode(6);
	tree.printNode(8);

	tree.clear();

	tree.insert(pair5);
	tree.insert(pair4);
	tree.insert(pair7);
	tree.insert(pair6);
	tree.insert(pair8);
	tree.insert(pair9);

	tree.erase(8);

	std::cout<<tree<<std::endl;

	tree.printNode(5);
	tree.printNode(4);
	tree.printNode(7);
	tree.printNode(6);
	tree.printNode(9);

	tree.clear();

	tree.insert(pair5);
	tree.insert(pair4);
	tree.insert(pair7);
	tree.insert(pair6);
	tree.insert(pair8);

	tree.erase(8);

	std::cout<<tree<<std::endl;

	tree.printNode(5);
	tree.printNode(4);
	tree.printNode(7);
	tree.printNode(6);

	tree.clear();
	
	tree.insert(pair5);

	tree.erase(5);

	std::cout<<tree<<std::endl;	

	std::cout<<"******************************************************************************"<<std::endl;
	std::cout<<"Test: balance"<<std::endl;
	std::cout<<"******************************************************************************"<<std::endl;

	// std::cout<<"Tree:"<<std::endl;
	// std::cout<<tree<<std::endl;	

	tree.insert(pair1);
	tree.insert(pair2);
	tree.insert(pair3);
	tree.insert(pair4);
	tree.insert(pair5);
	tree.insert(pair6);
	tree.insert(pair7);
	tree.insert(pair8);
	tree.insert(pair9);
	tree.insert(pair10);

	std::cout<<"Tree before balance invocation:"<<std::endl;

	tree.printNode(1);
	tree.printNode(2);
	tree.printNode(3);
	tree.printNode(4);
	tree.printNode(5);
	tree.printNode(6);
	tree.printNode(7);
	tree.printNode(8);
	tree.printNode(9);
	tree.printNode(10);

	tree.balance();

	std::cout<<"Tree after balance invocation:"<<std::endl;

	tree.printNode(1);
	tree.printNode(2);
	tree.printNode(3);
	tree.printNode(4);
	tree.printNode(5);
	tree.printNode(6);
	tree.printNode(7);
	tree.printNode(8);
	tree.printNode(9);
	tree.printNode(10);

	std::cout<<"******************************************************************************"<<std::endl;
	std::cout<<"Test: emplace"<<std::endl;
	std::cout<<"******************************************************************************"<<std::endl;

	tree.emplace(11,2);

	std::cout<<"Expected:"<<std::endl;
	std::cout<<"[1,1] [2,1] [3,1] [4,1] [5,1] [6,1] [7,1] [8,1] [9,1] [10,1] [11,2]"<<std::endl;
	std::cout<<"Result:"<<std::endl;
	std::cout<<tree<<std::endl;

	return 0;
}