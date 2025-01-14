#include<iostream>
using namespace std;
class binarynode{
    public:
    int data;
    binarynode *left;
    binarynode *right;
    binarynode *parent;

    binarynode(int x){
        data=x;
        this->left=NULL;
        this->right=NULL;
        this->parent=NULL;
    }


    void subtree_iter(){
        if(left!=NULL){
            left->subtree_iter();   //recursively going in left 
        }
        cout<<this->data<<" ";
        if(right!=NULL){             //recursively going in right
            right->subtree_iter();
        }
    }

    binarynode* subtree_first(){      
        if(left!=NULL){
            return left->subtree_first();
        }
        return this;
    }

    binarynode* subtree_last(){
        if(right!=NULL){
            return right->subtree_last();
        }
        return this;
    }
    
    binarynode* successor(){
        if(right!=NULL){
            return right->subtree_first();
        }
        binarynode *current=this;
        while(current->parent && current==current->parent->right){
            current=current->parent;
        }
        return current->parent;
    }

    binarynode* predecessor(){
        if(left!=NULL){
            return left->subtree_last();
        }
        binarynode* current=this;
        while(current->parent && current==current->parent->left){
            current=current->left;
        }
        return current->parent;
    }

    void subtree_insertafter(binarynode* newnode){
        if(right){
           successor()->left=newnode;
            newnode->parent=successor();
            //writing explicitly
            // binarynode* first = right->subtree_first();
            // first->left = newnode;
            // newnode->parent = first;
        }
        right=newnode;
        newnode->parent=this;
    }

    void subtree_insertbefore(binarynode* newnode){
        if(left){
            predecessor()->right=newnode;
            newnode->parent=predecessor();

        }
        left=newnode;
        newnode->parent=this;
    }

    binarynode* subtree_delete(){
        if(left || right){   //by default it will chose the predecessor
            binarynode *replacement=(left)? predecessor():successor();
            data=replacement->data;
            return replacement->subtree_delete();
        }
        if(parent){
            if(parent->left==this){
                parent->left=NULL;
            }else{
                parent->right=NULL;
            }
        }
        return this;
    }
};
int main()
{
     binarynode* root = new binarynode(10);
    binarynode* node5 = new binarynode(5);
    binarynode* node15 = new binarynode(15);
    binarynode* node3 = new binarynode(3);
    binarynode* node7 = new binarynode(7);
    binarynode* node12 = new binarynode(12);
    binarynode* node18 = new binarynode(18);

    root->subtree_insertbefore(node5);  // Insert 5 before 10
    root->subtree_insertafter(node15);  // Insert 15 after 10
    node5->subtree_insertbefore(node3); // Insert 3 before 5
    node5->subtree_insertafter(node7);  // Insert 7 after 5
    node15->subtree_insertbefore(node12); // Insert 12 before 15
    node15->subtree_insertafter(node18);  // Insert 18 after 15

    cout << "In-order traversal: ";
    root->subtree_iter();
    cout << endl;

    // cout<<node7->predecessor()->data;
    // node7->subtree_delete();
    // cout << "In-order traversal: ";
    // root->subtree_iter();
    // cout << endl;
 return 0;
}