/*
 * bst.h
 *
 *  Created on: 10 feb 2021
 *      Author: LucaRaveri
 */

#ifndef BST_H_
#define BST_H_

class bst {
public:
	bst();
	virtual ~bst();
	bst(const bst &other);
	bst(bst &&other);
	bst& operator=(const bst &other);
	bst& operator=(bst &&other);
};

#endif /* BST_H_ */
