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

	iterator& operator++() {
		if (!current) {
			return *this;
		} else if(current->right) {
			current = current->right.get();
			while(current->left) {
				current = current->left.get();
			}
		} else {
			N * tmp{current->parent};
			while(tmp && current == tmp->right.get()) {
				current = tmp;
				tmp = tmp->parent;
			}
			current = tmp;
		}
		return *this;
	}

	iterator operator++(int) {
        	iterator it{*this};
        	++(*this);
        	return it;
    }

	bool operator==(const iterator& other) { return current == other.current; }

	bool operator!=(const iterator& other) { return current != other.current; }

	N * getCurrentNode() { return current; }

};
