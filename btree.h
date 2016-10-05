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
template<typename T> ostream &operator<<(ostream&, const btree<T>&);

template<typename T>
class btree {
public:
    friend class btree_iterator<T> ;
    typedef btree_iterator<T> iterator;

    //constructor
    btree(size_t maxNodeElems = 40);

    // Copy constructor
    btree(const btree<T>& original);

    // Move constructor
    btree(btree<T> && original);

    // Copy assignment 
    btree<T>& operator=(const btree<T>& rhs);

    //Move assignment 
    btree<T>& operator=(btree<T> && rhs);

    friend std::ostream& operator<<<T>(std::ostream& os, const btree<T>& tree);

    iterator begin() const;
    iterator end() const;

    iterator find(const T& elem);
    // const_iterator find(const T& elem) const;

    std::pair<iterator, bool> insert(const T& elem);

    ~btree();

    //helper function -update head and tail
    void update_HeadTail();
    
    void checkRoot(){
    //     std::cout << "->usedSpace_ is "<< _root->usedSpace_<< std::endl;
    //     std::cout << "->treesize is "<< _treeSize<< std::endl;
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
                        for (size_t i = 0; i < maxNodeElemt_ + 1; ++i) 
                            children_[i] = nullptr; };

        Node(size_t maxElem_ = 40, Node *parent_ = nullptr) :
                    elem_(new T[maxElem_]),
                    parent_(parent_),
                    children_(new Node*[maxElem_ + 1]()),
                    usedSpace_(0),
                    maxNodeElemt_(maxElem_) { 
                        for (size_t i = 0; i < maxNodeElemt_ +1; ++i) 
                            children_[i] = nullptr;};

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

#endif
