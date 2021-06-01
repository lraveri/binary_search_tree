#include <iostream>
#include <memory>
#include <utility>

/**
 * struct that implements a node of the tree.
 */
template <typename T>
struct node {

	T elem;

	using value_type = T;

	std::unique_ptr<node> left;
	std::unique_ptr<node> right;

	node * parent;					

	node() = default;

	node(T e): elem{e},left{nullptr},right{nullptr},parent{nullptr} {};

	node(T e, node * p): elem{e},left{nullptr},right{nullptr},parent{p} {};

	node(const node& n) : elem{n.elem}, left{nullptr}, right{nullptr}, parent{n.parent} {}

	~node() noexcept= default;
};