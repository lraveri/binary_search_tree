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
#include <iomanip>      // sgamo->avoid

#include "Node.h"
#include "iterator.h"

template <class Tk,class Tv,class Tc = std::less<Tk>>
class bst {

public:

	  using pair = std::pair<const Tk,Tv>;
	  using node_type = node<pair>;
	  using Iterator = iterator<node_type, typename node_type::value_type>;
	  using Const_iterator = iterator<node_type, const typename node_type::value_type>;

private:

	std::unique_ptr<node_type> root;

	Tc comp;

	bst() noexcept = default;
	bst(std::pair<const Tk,Tv> element): root{new node_type{element}} {};
	explicit bst(Tc x): comp{x}{};

	// TODO: copy semantics

	// TODO: move semantics

	// TODO: subscription operator[]

	// TODO: put to operator<<

	// TODO: iterator begin and end

	// TODO: const iterator begin and end

	// TODO: insert

	// TODO: emplace

	// TODO: clear

	// TODO: find

	// TODO: balance

	// TODO: erase

	// TODO: print

};

#endif /* BST_H_ */
