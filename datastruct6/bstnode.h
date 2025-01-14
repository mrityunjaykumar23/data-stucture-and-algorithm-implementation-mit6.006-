// bstnode.h
#ifndef bstnode_H   //here  i have made a header file for the bstnode class
#define bstnode_H

class binarynode{
    public:
    int data;
    binarynode *left;
    binarynode *right;
    binarynode *parent;
    binarynode(int x);
    binarynode* subtree_first();
    binarynode* subtree_last();
    binarynode* successor();
    binarynode* predecessor();
    binarynode* subtree_delete();
    void subtree_insertafter(binarynode* newnode);
    void subtree_insertbefore(binarynode* newnode);


};

class bstnode:public binarynode{
public:

    bstnode(int value); // Constructor declaration

    // Member function declarations
    bstnode* subtree_find(int value);
    bstnode* subtree_find_next(int value);
    bstnode* subtree_find_prev(int value);
    void subtree_insert(bstnode *node);
    bstnode* subtree_first();
    bstnode* subtree_last();
    void subtree_iter();
};

#endif
