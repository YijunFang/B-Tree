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
			pointee_{pointee}, index_{maxNum}, btree_{btree}{
				// printf("btree_iterator()\n");
			}

	//getter and setter
	size_t getIndex(){
		return index_;
	}

private:
	typename btree<T>::Node *pointee_;
	size_t 					index_;
	const btree<T> 			*btree_;
};

template <typename T> typename btree_iterator<T>::reference 
btree_iterator<T>::operator*() const {
	// std:: cout << "index = "<< index_<< std::endl;
	// if(pointee_->parent_ != nullptr)
	// 	std::cout << pointee_->parent_-> elem_[0]<< std::endl;
	return pointee_->elem_[index_];
}
#endif

template<typename T> bool
btree_iterator<T>::operator ==(const btree_iterator<T>& other) const {
	return (btree_ == other.btree_ 
		&& pointee_ == other.pointee_ 
		&& index_ == other.index_);
}

template<typename T> btree_iterator<T>&
btree_iterator<T>::operator ++() {
	if(pointee_ == nullptr){
		pointee_ = btree_->_head;
		index_ = 0;
	}else if(pointee_->children_[index_+1] != nullptr){
		pointee_ = pointee_->children_[index_+1];
		index_ = 0;
		moveDown();
	}else if(index_ < pointee_->usedSpace_-1){
		index_++;
	}else{
		moveUp(currElement());
	}
	return *this;
}

template<typename T> void
btree_iterator<T>::moveUp(value_type element ){
	if(pointee_->parent_ == nullptr){
		pointee_ = nullptr;
		index_ = 0;
		return;
	}else{
		pointee_ = pointee_->parent_;
		for(index_ = 0; index_ < pointee_->usedSpace_;++index_){
			if (currElement()> element){
				return;
			}
		}
		moveUp(currElement());
	}
}

template<typename T> void
btree_iterator<T>::moveDown(){
	
	if(pointee_->children_[0] == nullptr) return;
	pointee_ = pointee_->children_[0];
	moveDown();
	return;
}





