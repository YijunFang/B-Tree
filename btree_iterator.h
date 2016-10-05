#ifndef BTREE_ITERATOR_H
#define BTREE_ITERATOR_H

#include <iterator>
#include <cassert>


using namespace std;
template <typename T> class btree;

template <typename T>class btree_iterator{
public:
	typedef ptrdiff_t                  		difference_type;
	typedef std::bidirectional_iterator_tag	iterator_category;
	typedef T 						   		value_type;
	typedef T* 								pointer;
	typedef T& 								reference;

	reference       operator *() const;
	pointer         operator->() const { return &(operator*()); }
	btree_iterator& operator++();
	btree_iterator& operator--();
	bool			operator==(const btree_iterator& other) const;
	bool			operator!=(const btree_iterator& other) const
											{ return !operator==(other); }
	//helper function
	void moveUp(value_type element );
	void moveDown();
	value_type currElement(){return pointee_->elem_[index_];}

	//constructor
	btree_iterator(typename btree<T>::Node *pointee = nullptr, size_t maxNum = 0, 
			const btree<T> *btree = nullptr):
			pointee_{pointee}, index_{maxNum}, btree_{btree}{}

	//getter and setter
	size_t getIndex(){return index_; }

private:
	typename btree<T>::Node *pointee_;
	size_t 					index_;
	const btree<T> 			*btree_;
};

#include "btree_iterator.tem"
#endif


