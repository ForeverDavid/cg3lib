/**
    @author Stefano Nuvoli
*/
#ifndef CG3_AVLINNER_H
#define CG3_AVLINNER_H

#include <vector>
#include <utility>

#include "includes/tree_common.h"

#include "includes/iterators/tree_iterator.h"
#include "includes/iterators/tree_reverseiterator.h"
#include "includes/iterators/tree_insertiterator.h"

#include "includes/nodes/avl_node.h"

namespace cg3 {

/**
 * @brief An autobalancing AVL binary search tree
 *
 * Keys and values are saved in all nodes, not only in the leaves. The implementation
 * is performed following "Introduction to Algorithms" (Cormen, 2011).
 * No duplicates are allowed.
 */
template <class K, class T = K>
class AVLInner
{

public:

    /* Typedefs */

    typedef AVLNode<K,T> Node;

    typedef LessComparatorType<K> LessComparator;

    typedef TreeGenericIterator<AVLInner<K,T>, Node> generic_iterator;

    typedef TreeIterator<AVLInner<K,T>, Node, T> iterator;
    typedef TreeIterator<AVLInner<K,T>, Node, const T> const_iterator;

    typedef TreeReverseIterator<AVLInner<K,T>, Node, T> reverse_iterator;
    typedef TreeReverseIterator<AVLInner<K,T>, Node, const T> const_reverse_iterator;

    typedef TreeInsertIterator<AVLInner<K,T>, K> insert_iterator;



    /* Constructors/destructor */

    AVLInner(const LessComparator customComparator = &cg3::defaultComparator<K>);
    AVLInner(const std::vector<std::pair<K,T>>& vec,
             const LessComparator customComparator = &cg3::defaultComparator<K>);
    AVLInner(const std::vector<K>& vec,
             const LessComparator customComparator = &cg3::defaultComparator<K>);

    ~AVLInner();



    /* Public methods */

    void construction(const std::vector<K>& vec);
    void construction(const std::vector<std::pair<K,T>>& vec);

    iterator insert(const K& key);
    iterator insert(const K& key, const T& value);

    bool erase(const K& key);
    void erase(generic_iterator it);

    iterator find(const K& key);


    TreeSize size();
    bool empty();

    void clear();

    TreeSize getHeight();


    template <class OutputIterator>
    void rangeQuery(
            const K& start, const K& end,
            OutputIterator out);



    /* Iterator Min/Max Next/Prev */

    iterator getMin();
    iterator getMax();

    generic_iterator getNext(const generic_iterator it);
    generic_iterator getPrev(const generic_iterator it);



    /* Iterators */

    iterator begin();
    iterator end();

    const_iterator cbegin();
    const_iterator cend();

    reverse_iterator rbegin();
    reverse_iterator rend();

    const_reverse_iterator crbegin();
    const_reverse_iterator crend();

    insert_iterator inserter();


protected:

    /* Protected fields */

    Node* root;

    TreeSize entries;

    const LessComparator lessComparator;


private:

    /* Private methods */

    void initialize();

};

}


#include "avlinner.tpp"

#endif // CG3_AVLINNER_H



