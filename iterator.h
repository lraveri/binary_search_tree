/*
 * iterator.h
 *
 *  Created on: 10 feb 2021
 *      Author: LucaRaveri
 */

#ifndef ITERATOR_H_
#define ITERATOR_H_

#include <iterator>

template <typename N, typename P >
class iterator {

	N * current;

public:

	using value_type= P;

	using reference=value_type&;

	using pointer=value_type*;

	using iterator_category=std::forward_iterator_tag;

	using difference_type = std::ptrdiff_t;

	iterator()  noexcept: current{nullptr} {};

	iterator(N * n) noexcept: current{n} {};

	pointer operator->() const noexcept { return &(*(*this)); }

	reference operator*() const noexcept {return current->elem;};

	// TODO: operator++

	bool operator==(const iterator& other) { return current == other.current; }

	bool operator!=(const iterator& other) { return current != other.current; }

	N * getCurrentNode() { return current; }

};

#endif /* ITERATOR_H_ */
