/**
 * The btree is a linked structure which operates much like
 * a binary search tree, save the fact that multiple client
 * elements are stored in a single node.  Whereas a single element
 * would partition the tree into two ordered subtrees, a node 
 * that stores m client elements partition the tree 
 * into m + 1 sorted subtrees.
 */

#ifndef BTREE_H
#define BTREE_H

#include <iostream>
#include <cstddef>
#include <utility>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

#include "btree_iterator.h"

template<typename T> class btree;
// template<typename T> ostream &operator<<(ostream&, const btree<T>&);

template<typename T>
class btree {
public:
    friend class btree_iterator<T> ;
    typedef btree_iterator<T> iterator;

    btree(size_t maxNodeElems = 40);

    // Copy constructor
    btree(const btree<T>& original);

    // Move constructor
    btree(btree<T> && original);

    // Copy assignment 
    btree<T>& operator=(const btree<T>& rhs);

    //Move assignment 
    btree<T>& operator=(btree<T> && rhs);

    // friend std::ostream& operator<<<T>(std::ostream& os, const btree<T>& tree);

    iterator begin() const;
    iterator end() const;

    iterator find(const T& elem);
    // const_iterator find(const T& elem) const;

    std::pair<iterator, bool> insert(const T& elem);

    ~btree();
    void update_HeadTail();
    void checkRoot(){
        std::cout << "->usedSpace_ is "<< _root->usedSpace_<< std::endl;
        std::cout << "->treesize is "<< _treeSize<< std::endl;
    }

private:

    struct Node {
        Node( const T& elem ,size_t maxElem_ = 40, Node *parent_ = nullptr) :
                    elem_(new T[maxElem_]),
                    parent_(parent_),
                    children_(new Node*[maxElem_ + 1]()),
                    usedSpace_(1),
                    maxNodeElemt_(maxElem_) { 
                        elem_[0] = elem; 
                        for (size_t i = 0; i < maxNodeElemt_ + 1; ++i) {
                            children_[i] = nullptr;
                        }
                        // printf("last is %lu\n",maxNodeElemt_ + 1 );
                    };
        Node(size_t maxElem_ = 40, Node *parent_ = nullptr) :
                    elem_(new T[maxElem_]),
                    parent_(parent_),
                    children_(new Node*[maxElem_ + 1]()),
                    usedSpace_(0),
                    maxNodeElemt_(maxElem_) { 
                        for (size_t i = 0; i < maxNodeElemt_ +1; ++i) {
                            children_[i] = nullptr;
                        }
                        // printf("last is %lu\n",maxNodeElemt_ + 1);
                    };

        ~Node() {
            for (size_t i = 0; i < maxNodeElemt_ + 1; ++i) {
                if(children_[i] != nullptr)
                    delete children_[i];
            }
            delete [] elem_;
            delete [] children_;
        };
        Node& operator=(const Node& rhs);


        inline bool   is_full() const { return usedSpace_ == maxNodeElemt_; };
        inline size_t size()    const { return usedSpace_; };
       
        T *elem_;               //array of element in this node
        Node *parent_;          //parent node of this node
        Node **children_;       //pointer to an array of pointer to node...haha
        size_t usedSpace_;
        size_t maxNodeElemt_;   //maximum number of elements in each node

    };

    Node *_root, *_head, *_tail;
    size_t _maxElemt;      // The maximum number of elements that can be
                                // stored in each B-Tree node
    size_t _treeSize;        // The size (node number) of the b-tree.
};

#include "btree.tem"
//#include "btree.tem.cpp"

template<typename T>
btree<T>::btree(size_t maxNodeElems) :
        _root(nullptr), _head(nullptr), _tail(nullptr), _maxElemt(maxNodeElems),
            _treeSize(0) {printf("btree()\n");}

template<typename T>
btree<T>::~btree() {
    printf("~btree()\n");
    delete _root;
}


template<typename T> typename btree<T>::iterator
btree<T>::begin() const {return iterator(_head, 0, this); }

template<typename T> typename btree<T>::iterator
btree<T>::end() const {return iterator(NULL, 0, this); }

template<typename T> typename btree<T>::iterator
btree<T>::find(const T& elem){}

template<typename T>
void btree<T>::update_HeadTail(){
    std::cout << "update_HeadTail(): ";
    Node *parent = _root;
    _head = _root;
    _tail = _root;

    while(parent->children_[0] != nullptr){
        parent = parent->children_[0];
    }
    _head = parent;
    std::cout <<"head is "<< _head->elem_[0] << "  ||  ";
    
    parent = _root;
    while (parent->usedSpace_!= 0){
        if(parent->children_[parent->usedSpace_]!=nullptr){
            parent = parent->children_[parent->usedSpace_];
        }else{
            break;
        }
        
    }
    _tail = parent;
    std::cout <<"tail is "<< _tail->elem_[parent->usedSpace_-1] << std::endl;
    // checkRoot();
}


template<typename T> std::pair<typename btree<T>::iterator, bool>
btree<T>::insert(const T& elem) {
    Node *parent = _root;
    Node *currNode = parent;
    size_t i = 0;

    while (true) {

        if (_root == nullptr) {
            _root= new Node(elem, _maxElemt, nullptr);
            ++_treeSize;
            update_HeadTail();
            return make_pair(iterator(_root, 0, this), true);

        }else if(currNode == nullptr){
            // std::cout << i << std::endl;
            parent ->children_[i] = new Node(elem, _maxElemt, parent);
            // printf("here\n");
            ++_treeSize;
            // std::cout << "insert at "<< i<< std::endl;
            update_HeadTail();
            return make_pair(iterator(parent ->children_[i] , 0, this), true);
    
        }else if(currNode != nullptr){// if tree not empty
             // std::cout << "currNode->usedSpace_ =  "<< currNode->usedSpace_<< std::endl;
            //at this level loop throught element
            for(i = 0 ; i <  _maxElemt; ++i){ 
               
                // std::cout << i << std::endl;

                if(currNode->elem_ [i] == elem && i< currNode->usedSpace_){
                    // printf("======================\n");
                    update_HeadTail();
                    return make_pair(iterator(currNode, i, this), false);

                //all smaller than element and have space at this level
                }else if (currNode->elem_[i] < elem && (i == currNode->usedSpace_-1)&& !(currNode->is_full()) ){
                        // printf("........................\n");
                        // std::cout << "insert at "<< currNode->usedSpace_<< std::endl;

                        currNode->elem_[currNode->usedSpace_] = elem;
                        currNode->usedSpace_++;
                        update_HeadTail();
                        return make_pair(iterator(currNode, currNode->usedSpace_-1, this), true);

                //all smaller than element and have no space
                }else if (currNode->elem_[i] < elem && (i == _maxElemt-1) && currNode->is_full() ){
                    // printf("+++++++++++++++++++\n");
                    parent = currNode;
                    currNode = currNode->children_[_maxElemt];
                    i = _maxElemt;
                    break;
                    
                }//value greater than element, insert at children
                else if (currNode->elem_[i] > elem  && i< currNode->usedSpace_){
                    // printf("---------------------\n");
                    parent = currNode;
                    currNode = currNode->children_[i];
                    // std::cout << i << std::endl;
                    break;
                }
            }
        }

    }

}


#endif
