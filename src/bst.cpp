/*
 * bst.cpp
 *
 *  Created on: 10 feb 2021
 *      Author: LucaRaveri
 */

#include "bst.h"

template <class Tk,class Tv,class Tc>
typename bst<Tk,Tv,Tc>::node_type*  bst<Tk,Tv,Tc>::_begin() const noexcept {
	if(root!=nullptr) {
		node_type* n = root.get();
		while(n->left) {
			n = n->left.get();
		}
        return n;
    } else {
        return nullptr;
    }
}

template <class Tk,class Tv,class Tc>
typename bst<Tk,Tv,Tc>::Iterator bst<Tk,Tv,Tc>::begin() noexcept {
        return Iterator{_begin()};
}

template <class Tk,class Tv,class Tc>
typename bst<Tk,Tv,Tc>::Const_iterator bst<Tk,Tv,Tc>::begin() const noexcept {
            return Const_iterator{_begin()};

}

template <class Tk,class Tv,class Tc>
typename bst<Tk,Tv,Tc>::Const_iterator bst<Tk,Tv,Tc>::cbegin() const noexcept {
	return Const_iterator{_begin()};
}

template <class Tk,class Tv,class Tc>
template <typename T>
std::pair<typename bst<Tk,Tv,Tc>::Iterator, bool> bst<Tk,Tv,Tc>::_insert(T&& x) {
	if(!root){
		root.reset(new node_type{std::forward<T>(x)});
		return std::make_pair(Iterator{root.get()},true);
	}
	node_type * node = root.get();
	while(true) {
		if(comp(node->elem.first, x.first)) {
			if(node->right.get()==nullptr) {
				node->right.reset(new node_type{std::forward<T>(x),node});
				return std::make_pair(Iterator{node->right.get()},true);
			} else {
				node = node->right.get();
			}
		} else if (op(x.first, node->elem.first)) {
			if(node->left.get()==nullptr) {
				node->left.reset(new node_type{std::forward<T>(x),node});
				return std::make_pair(Iterator{node->right.get()},true);
			} else {
				node = node->left.get();
			}
		} else {	// usare find all'inizio?
			std::cout<<"The key: ["<<x.first<<"] is already present"<<std::endl;
			return std::make_pair(Iterator{node},false);
		}
	}
}

template <class Tk,class Tv,class Tc>
std::pair<typename bst<Tk,Tv,Tc>::Iterator, bool> bst<Tk,Tv,Tc>::insert(const std::pair<const Tk, Tv>& x) {
	return _insert(x);
}

template <class Tk,class Tv,class Tc>
std::pair<typename bst<Tk,Tv,Tc>::Iterator, bool> bst<Tk,Tv,Tc>::insert(std::pair<const Tk, Tv>&& x) {
	return _insert(std::move(x));
}
