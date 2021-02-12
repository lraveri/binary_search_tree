/*
 * bst.h
 *
 *  Created on: 10 feb 2021
 *      Author: LucaRaveri
 */

#ifndef BST_H_
#define BST_H_

#include <iostream>
#include <memory>
#include <vector>
#include <utility>
#include <iterator>

#include "Node.h"
#include "iterator.h"

template <class Tk,class Tv,class Tc = std::less<Tk>>
class bst {

public:

	  using pair_type = std::pair<const Tk,Tv>;
	  using node_type = node<pair_type>;
	  using Iterator = iterator<node_type, typename node_type::value_type>;
	  using Const_iterator = iterator<node_type, const typename node_type::value_type>;

private:

	std::unique_ptr<node_type> root;

	Tc comp;

	bst() noexcept = default;
	bst(std::pair<const Tk,Tv> element): root{new node_type{element}} {};
	explicit bst(Tc x): comp{x}{};

	// TODO: copy semantics

	bst(const bst& tree);

	bst& operator=(const bst& tree);

	// TODO: move semantics

	bst(bst&& tree) noexcept;

	bst& operator=(bst&&  tree) noexcept;

	// TODO: subscription operator[]

	Tv& operator[](const Tk& x);

	Tv& operator[](Tk&& x);

	// TODO: put to operator<< !

	friend
	std::ostream& operator<<(std::ostream& os, const bst& x);

	// TODO: iterator begin and end !

	Iterator begin();

	Iterator end();

	// TODO: const iterator begin and end !

	Const_iterator begin() const;

	Const_iterator cbegin() const;

	Const_iterator end() const;

	Const_iterator cend() const;

	// TODO: insert !

	std::pair<Iterator, bool> insert(const pair_type& x);

	std::pair<Iterator, bool> insert(pair_type&& x);

	// TODO: emplace

	template< class... Types >
	std::pair<Iterator,bool> emplace(Types&&... args);

	// TODO: clear !

	void clear();

	// TODO: find !

	Iterator find(const Tk& x);

	Const_iterator find(const Tk& x) const;

	// TODO: balance

	void balance();

	// TODO: erase

	void erase(const Tk& x);


};

#endif /* BST_H_ */
