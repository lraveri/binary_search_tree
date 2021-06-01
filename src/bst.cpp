#include <vector>
#include "../include/bst.hpp"

template <class Tk,class Tv,class Tc>
typename bst<Tk,Tv,Tc>::node_type*  bst<Tk,Tv,Tc>::_begin() const noexcept {
	if(root) {
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
			if(!(node->right.get())) {
				node->right.reset(new node_type{std::forward<T>(x),node});
				return std::make_pair(Iterator{node->right.get()},true);
			} else {
				node = node->right.get();
			}
		} else if (comp(x.first, node->elem.first)) {
			if(!(node->left.get())) {
				node->left.reset(new node_type{std::forward<T>(x),node});
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
std::pair<typename bst<Tk,Tv,Tc>::Iterator, bool> bst<Tk,Tv,Tc>::insert(const std::pair<const Tk, Tv>& x) {
	return _insert(x);
}

template <class Tk,class Tv,class Tc>
std::pair<typename bst<Tk,Tv,Tc>::Iterator, bool> bst<Tk,Tv,Tc>::insert(std::pair<const Tk, Tv>&& x) {
	return _insert(std::move(x));
}

template <class Tk,class Tv,class Tc>
typename bst<Tk,Tv,Tc>::node_type* bst<Tk,Tv,Tc>::_find(const Tk& x) {
	auto tmp=root.get();
	while(tmp) {
		if(!comp(tmp->elem.first, x) && !comp(x,tmp->elem.first))  
			return tmp;
		else if(comp(tmp->elem.first,x))                              
        	tmp=tmp->right.get();
		else
			tmp=tmp->left.get();					           
	}
	return nullptr;
}

template <class Tk,class Tv,class Tc>
typename bst<Tk,Tv,Tc>::Iterator bst<Tk,Tv,Tc>::find(const Tk& x) {
	auto tmp=_find(x);
	if(!tmp) return end();
	else return Iterator{tmp};
}

template <class Tk,class Tv,class Tc>
typename bst<Tk,Tv,Tc>::Const_iterator bst<Tk,Tv,Tc>::find(const Tk& x) const {
   	auto tmp=_find(x);
    if(!tmp) return cend();
    else return Const_iterator{tmp};
}

template <class Tk,class Tv,class Tc>
Tv& bst<Tk,Tv,Tc>::operator[](Tk&& x) {
	auto it {insert(std::pair<Tk, Tv> {std::move(x),Tv{}}).first};
	return (*(it)).second;
}	

template <class Tk,class Tv,class Tc>
Tv& bst<Tk,Tv,Tc>::operator[](const Tk& x) {
	auto it {insert(std::pair<Tk, Tv> {x,Tv{}}).first};
	return (*(it)).second;
}

template<class Tk, class Tv, class Tc>
void bst<Tk,Tv,Tc>::copy(const std::unique_ptr<node_type>& n) {
	if(n) {
		(void)insert(n->elem);
		copy(n->left);
		copy(n->right);
	}
}

template<class Tk, class Tv, class Tc>
bst<Tk, Tv, Tc>& bst<Tk,Tv,Tc>::operator=(bst<Tk, Tv, Tc>&& tree) noexcept {
	root=std::move(tree.root);
	return *this;
}

template <class Tk,class Tv,class Tc>
void bst<Tk,Tv,Tc>::erase(const Tk& x) {

	if(!root) return;                                   // Case: empty bst

	auto i = find(x);

	if(i==end()) return;                                // Case: the node is not present in the bst

    auto n=i.current;     

	if(!(n->left) && !(n->right)) {                     // Case: the node is a leaf
		if(n->parent->right.get() == n) {               // Sub case: the node is the right child of the parent
			n->parent->right.reset();
		} else {                                        // Sub case: the node is the left child of the parent
			n->parent->left.reset();
		}
	}

	if (n->right && n->left) {                          // Case: the node has two children   
        ++i;
        auto next = i.current;
        next->left = std::move(n->left);  
        next->left->parent = next;
        n->right->parent = n->parent;
	}

	if(!(n->parent)) {                                  // Case: the node is the root
		n->right->parent = nullptr;	
		root = std::move(n->right);
	} else {                                            // Case: the node has one child  
		if(n->parent->right.get() == n) {               // Sub case: the node is the right child of the parent
			if(n->right) {                              // Sub case: the node has a right child
				n->right->parent = n->parent;	
				n->parent->right=std::move(n->right);
			} else if (n->left) {                       // Sub case: the node has a left child
				n->left->parent= n->parent;
				n->parent->right=std::move(n->left);
			}
		} else {                                        // Sub case: the node is the left child of the parent
			if(n->right) {                              // Sub case: the node has a right child
				n->right->parent= n->parent;
				n->parent->left=std::move(n->right);
			} else if (n->left) {                       // Sub case: the node has a left child
				n->left->parent=n->parent;
				n->parent->left=std::move(n->left);
			}			
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
void bst<Tk,Tv,Tc>::printChildren(Tk a) {
	auto i = bst<Tk,Tv,Tc>::find(a);  
	auto node = i.current;      																			
	if (node) {														
    	std::cout<<"node = " << node->elem.first<<" -> ";		
    	if(!(node->left)) {										
    		std::cout<<"left child = null, ";
		} else {						
    		std::cout<<"left child = "<<node->left->elem.first<<", ";
		}			
    	if(!(node->right)) {										
      	std::cout<<"right child = null"<<std::endl;	
		} else {					
      	std::cout<<"right child = "<<node->right->elem.first<<std::endl;	
		}		
  	}																
    return;
}