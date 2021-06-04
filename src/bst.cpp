#include <vector>
#include "../include/bst.hpp"

template <class Tk,class Tv,class Tc>
typename bst<Tk,Tv,Tc>::Iterator bst<Tk,Tv,Tc>::begin() noexcept {
	if(root) {
		node_type* n = root.get();
		while(n->left) {
			n = n->left.get();
		}
		return Iterator{n};
	} else {
		return Iterator{nullptr};
	}
}

template <class Tk,class Tv,class Tc>
typename bst<Tk,Tv,Tc>::Const_iterator bst<Tk,Tv,Tc>::begin() const noexcept {
	if(root) {
		node_type* n = root.get();
		while(n->left) {
			n = n->left.get();
		}
		return Const_iterator{n};
	} else {
		return Const_iterator{nullptr};
	}
}

template <class Tk,class Tv,class Tc>
typename bst<Tk,Tv,Tc>::Const_iterator bst<Tk,Tv,Tc>::cbegin() const noexcept {
	if(root) {
		node_type* n = root.get();
		while(n->left) {
			n = n->left.get();
		}
		return Const_iterator{n};
	} else {
		return Const_iterator{nullptr};
	}
}

template <class Tk,class Tv,class Tc>
std::pair<typename bst<Tk,Tv,Tc>::Iterator, bool> bst<Tk,Tv,Tc>::insert(const std::pair<const Tk, Tv>& x) {
	if(!root){
		root.reset(new node_type(x));
		return std::make_pair(Iterator{root.get()},true);
	}
	node_type * node = root.get();
	while(true) {
		if(comp(node->elem.first, x.first)) {
			if(!(node->right.get())) {
				node->right.reset(new node_type(x,node));
				return std::make_pair(Iterator{node->right.get()},true);
			} else {
				node = node->right.get();
			}
		} else if (comp(x.first, node->elem.first)) {
			if(!(node->left.get())) {
				node->left.reset(new node_type(x,node));
				return std::make_pair(Iterator{node->right.get()},true);
			} else {
				node = node->left.get();
			}
		} else {
			return std::make_pair(Iterator{node},false);
		}
	}
}

template <class Tk,class Tv,class Tc>
std::pair<typename bst<Tk,Tv,Tc>::Iterator, bool> bst<Tk,Tv,Tc>::insert(std::pair<const Tk, Tv>&& x) {
	if(!root){
		root.reset(new node_type(std::move(x)));
		return std::make_pair(Iterator{root.get()},true);
	}
	node_type * node = root.get();
	while(true) {
		if(comp(node->elem.first, x.first)) {
			if(!(node->right.get())) {
				node->right.reset(new node_type(std::move(x),node));
				return std::make_pair(Iterator{node->right.get()},true);
			} else {
				node = node->right.get();
			}
		} else if (comp(x.first, node->elem.first)) {
			if(!(node->left.get())) {
				node->left.reset(new node_type(std::move(x),node));
				return std::make_pair(Iterator{node->right.get()},true);
			} else {
				node = node->left.get();
			}
		} else {
			return std::make_pair(Iterator{node},false);
		}
	}
}

template <class Tk,class Tv,class Tc>
typename bst<Tk,Tv,Tc>::Iterator bst<Tk,Tv,Tc>::find(const Tk& x) {
	auto tmp=root.get();
	while(tmp) {
		if(!comp(tmp->elem.first, x) && !comp(x,tmp->elem.first)) {
			return Iterator{tmp};
		} else if(comp(tmp->elem.first,x)) {                             
			tmp=tmp->right.get();
		} else {
			tmp=tmp->left.get();	
		}				           
	}
	return end();
}

template <class Tk,class Tv,class Tc>
typename bst<Tk,Tv,Tc>::Const_iterator bst<Tk,Tv,Tc>::find(const Tk& x) const {
	auto tmp=root.get();
	while(tmp) {
		if(!comp(tmp->elem.first, x) && !comp(x,tmp->elem.first)) {
			return Const_iterator{tmp};
		} else if(comp(tmp->elem.first,x)) {                            
			tmp=tmp->right.get();
		} else {
			tmp=tmp->left.get();	
		}				           
	}
	return cend();
}

template <class Tk,class Tv,class Tc>
Tv& bst<Tk,Tv,Tc>::operator[](const Tk& x) {
	auto tmp = insert(std::make_pair(x, Tv{}));
	return (*(tmp.first)).second;
}

template <class Tk,class Tv,class Tc>
Tv& bst<Tk,Tv,Tc>::operator[](Tk&& x) {
	auto tmp = insert(std::make_pair(std::move(x), Tv{}));
	return (*(tmp.first)).second;
}	

template<class Tk, class Tv, class Tc>
void bst<Tk,Tv,Tc>::copy(const std::unique_ptr<node_type>& n) {
	if(n) {
		insert(n->elem);
		copy(n->left);
		copy(n->right);
	}
}

template <class Tk,class Tv,class Tc>
void bst<Tk,Tv,Tc>::erase(const Tk& x) {

    if(!root) return;
    auto it = find(x);
    if(it==end()) return;
    auto n=it.current;                                           		// n is the node to erase
    
    if(n->left && n->right) {                                    		// Case: n has two children
        ++it;
        auto s = it.current;                                     		// s is the successor
        s->left = std::move(n->left); 
        s->left->parent = s;
        if(!n->parent) {                                        		// Subcase: n is the root
            n->right->parent = nullptr;
            root = std::move(n->right);
        } else if(n->parent->right.get()==n) {							// Subcase: n is a right child												
            n->right->parent = n->parent;
            n->parent->right = std::move(n->right);
        } else {														// Subcase: n is a left child										
            n->right->parent = n->parent;
            n->parent->left = std::move(n->right);
        }
    } else if ((!(n->left) && n->right) || (n->left && !(n->right))) {  // Case: n has one child
        if(!n->parent) {												// Subcase: n is the root
            if (n->right) {
                n->right->parent = nullptr;
                root = std::move(n->right);
            } else {
                n->left->parent = nullptr;
                root = std::move(n->left);
            }
        } else if(n->parent->right.get()==n) {							// Subcase: n is a right child
            if(n->right) {
                n->right->parent = n->parent;
                n->parent->right = std::move(n->right);
            } else {
                n->left->parent = n->parent;
                n->parent->right = std::move(n->left);
            }
        } else {														// Subcase: n is a left child
            if(n->right) {
                n->right->parent = n->parent;
                n->parent->left = std::move(n->right);
            } else {
                n->left->parent = n->parent;
                n->parent->left = std::move(n->left); 
            }
        }
    } else {                                                            // Case: n has no children
        if(!n->parent) {												// Subcase: n is the root
            root.reset();
        } else if(n->parent->right.get()==n) {							// Subcase: n is a right child
            n->parent->right.reset();
        } else {
            n->parent->left.reset();									// Subcase: n is a left child
        }
    }
}

template <class Tk,class Tv,class Tc>
void bst<Tk,Tv,Tc>::balance() {
	Iterator it{this->begin()}; 				
	Iterator end{this->end()};
	if(it == end){
		return;
	} else {											
		std::vector<std::pair<Tk, Tv>> v;
		for(; it != end; ++it) {
			v.push_back(*it);
		}
		this->clear();
		balance_aux(v, 0, v.size()-1);					
	}
}

// recursive auxiliary method for balance
template <class Tk,class Tv,class Tc>
void bst<Tk,Tv,Tc>::balance_aux(std::vector<std::pair<Tk, Tv>>& v,int start, int end) {
	if(start > end) {
		return;
	}
	int mid = (start + end) / 2;
	insert(v[mid]);
	balance_aux(v, start, mid - 1);
	balance_aux(v, mid + 1, end);
}

template <class Tk, class Tv, class Tc>
void bst<Tk,Tv,Tc>::printNode(Tk a) {
	auto it = bst<Tk,Tv,Tc>::find(a);  
	auto n = it.current;      																			
	if (n) {														
		std::cout<<"node = " << n->elem.first<<" -> ";		
		if(!(n->left)) {										
			std::cout<<"left child = null, ";
		} else {						
			std::cout<<"left child = "<<n->left->elem.first<<", ";
		}			
		if(!(n->right)) {										
			std::cout<<"right child = null, ";	
		} else {					
			std::cout<<"right child = "<<n->right->elem.first<<", ";	
		}		
		if(!(n->parent)) {
			std::cout<<"parent = null"<<std::endl;
		} else {
			std::cout<<"parent = "<<n->parent->elem.first<<std::endl;
		}
	}																
	return;
}