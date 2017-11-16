/**
    @author Stefano Nuvoli
*/
#ifndef CG3_AABBTREE_H
#define CG3_AABBTREE_H

#include <vector>
#include <utility>

#include "includes/treecommon.h"

#include "includes/iterators/treeiterator.h"
#include "includes/iterators/treereverseiterator.h"
#include "includes/iterators/treeinsertiterator.h"

#include "includes/nodes/aabbnode.h"

#include "includes/aabbhelpers.h"

namespace cg3 {

/**
 * @brief An autobalancing (AVL) AABB tree
 *
 * No duplicates are allowed. It has been implemented as
 * a FAT AABB tree: the AABB of each node is the AABB
 * containing the entire childhood AABBs.
 */
template <int D, class K, class T = K>
class AABBTree
{

public:

    /* Typedefs */

    typedef AABBNode<D,K,T> Node;

    typedef LessComparatorType<K> LessComparator;

    typedef AABBValueExtractorType<K> AABBValueExtractor;
    typedef KeyOverlapCheckerType<K> KeyOverlapChecker;

    typedef TreeGenericIterator<AABBTree<D,K,T>, Node> generic_iterator;

    typedef TreeIterator<AABBTree<D,K,T>, Node, T> iterator;
    typedef TreeIterator<AABBTree<D,K,T>, Node, const T> const_iterator;

    typedef TreeReverseIterator<AABBTree<D,K,T>, Node, T> reverse_iterator;
    typedef TreeReverseIterator<AABBTree<D,K,T>, Node, const T> const_reverse_iterator;

    typedef TreeInsertIterator<AABBTree<D,K,T>, K> insert_iterator;



    /* Constructors/destructor */

    AABBTree(const AABBValueExtractor customAABBExtractor,
             const LessComparator customComparator = &cg3::defaultComparator<K>);
    AABBTree(const std::vector<std::pair<K,T>>& vec,
             const AABBValueExtractor customAABBExtractor,
             const LessComparator customComparator = &cg3::defaultComparator<K>);
    AABBTree(const std::vector<K>& vec,
             const AABBValueExtractor customAABBExtractor,
             const LessComparator customComparator = &cg3::defaultComparator<K>);

    ~AABBTree();



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

    template <class OutputIterator>
    void aabbOverlapQuery(
            const K& key,
            OutputIterator out,
            KeyOverlapChecker keyOverlapChecker = nullptr);

    bool aabbOverlapCheck(
            const K& key,
            KeyOverlapChecker keyOverlapChecker = nullptr);


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

    const AABBValueExtractor aabbValueExtractor;


private:

    /* Private methods */

    void initialize();

};

}


#include "aabbtree.tpp"

#endif // CG3_AABBTREE_H




