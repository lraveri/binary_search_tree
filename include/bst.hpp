#include <iostream>
#include <memory>
#include <vector>
#include <utility>
#include <iterator>

#include "node.hpp"
#include "iterator.hpp"

/**
 * class that implements a binary search tree
 */
template <class Tk,class Tv,class Tc = std::less<Tk>>
class bst {

public:

	  using pair_type = std::pair<const Tk,Tv>;
	  using node_type = node<pair_type>;
	  using Iterator = iterator<node_type, typename node_type::value_type>;
	  using Const_iterator = iterator<node_type, const typename node_type::value_type>;

private:

	// fields

	std::unique_ptr<node_type> root;

	Tc comp;

	// auxiliary methods

	node_type* _begin() const noexcept;

	template <typename T>
	std::pair<Iterator,bool> _insert(T&& x);

	node_type* _find(const Tk& x);

	void copy(const std::unique_ptr<node_type>& n);

	void balance_aux(std::vector<std::pair<Tk, Tv>>& v,int start, int end);

public:

	// constructors

	bst() noexcept = default;

	bst(std::pair<const Tk,Tv> element): root{new node_type{element}} {};

	explicit bst(Tc x): comp{x}{};

	// copy semantics

	bst(const bst& tree) {copy(tree.root);}

	bst& operator=(const bst& tree) {
		clear();
		copy(tree.root);
		return *this;
	}

	// move semantics

	bst(bst&& tree) noexcept : root{std::move(tree.root)} {}

	bst& operator=(bst&& tree) noexcept;

	// operator []

	Tv& operator[](const Tk& x);

	Tv& operator[](Tk&& x);

	// operator <<

	friend
	std::ostream& operator<<(std::ostream& os, const bst& x) {
		for (const auto& pair : x ) {
			os << "["<<pair.first<<","<<pair.second<<"] ";
		}
		return os;
	};

	// begin & end methods

	Iterator begin() noexcept;

	Iterator end() { return Iterator{nullptr}; };

	Const_iterator begin() const noexcept;

	Const_iterator cbegin() const noexcept;

	Const_iterator end()  const noexcept { return Const_iterator{nullptr}; };

	Const_iterator cend() const noexcept { return Const_iterator{nullptr}; };

	// insert methods

	std::pair<Iterator, bool> insert(const pair_type& x);

	std::pair<Iterator, bool> insert(pair_type&& x);

	// emplace method

	template< class... Types >
	std::pair<Iterator,bool> emplace(Types&&... args) {
		return insert(std::make_pair(std::forward<Types>(args)...)); 
	}

	// clear method

	void clear() noexcept { root.reset(); };

	// find methods

	Iterator find(const Tk& x);

	Const_iterator find(const Tk& x) const;

	// balance method

	void balance();

	// erase method

	void erase(const Tk& x);

	// debug method

	void printNode(Tk a);

};