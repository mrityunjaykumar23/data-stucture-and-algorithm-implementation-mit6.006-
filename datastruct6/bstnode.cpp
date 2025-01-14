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

};

class bstnode : public binarynode{    //here you are inheriting the binarynode class
public:
    bstnode(int k):binarynode(k){   //here binarynode is called before the constructor of derived class
    }

    bstnode* subtree_find(int k){
        if(k==this->data){
            return this;
        }
        else if(k<this->data){
            return static_cast<bstnode*>(left)->subtree_find(k);
        }
        else{
            return static_cast<bstnode*>(right)->subtree_find(k);
        }
    }

    bstnode* subtree_find_next(int k){
        if(k>=this->data){
                return right? static_cast<bstnode*>(right)->subtree_find_next(k):NULL;
        }
        else{
            if(left){
                bstnode* leftresult=static_cast<bstnode*>(left)->subtree_find_next(k);
                return leftresult?leftresult:this;
            }
            return this;
        }
    }

    bstnode* subtree_find_prev(int k){
        if(k<=this->data){
            return left?static_cast<bstnode*>(left)->subtree_find_prev(k):NULL;
        }
        else{
            if(right){
                bstnode* rightresult=static_cast<bstnode*>(right)->subtree_find_next(k);
                return rightresult?rightresult:this;
            }
            return this;
        }
    }

    void subtree_insert(bstnode* node){
        if(node->data<this->data){
            if(left){
            static_cast<bstnode*> (left)->subtree_insert(node);}
        else{
            left=node;
            node->parent=this;
        }
        }
        else if(node->data>=this->data){
            if(right){
                static_cast<bstnode*>(right)->subtree_insert(node);}
                else{
                    right=node;
                    node->parent=this;
                }
            }

        }

        void subtree_iter(){
        if(left!=NULL){
            static_cast<bstnode*>(left)->subtree_iter();   //recursively going in left 
        }
        cout<<this->data<<" ";
        if(right!=NULL){             //recursively going in right
            static_cast<bstnode*>(right)->subtree_iter();
        }
    }

    bstnode* subtree_first(){
        if(left){
            return static_cast<bstnode*>(left)->subtree_first();
        }else{
            return static_cast<bstnode*>(this);
        }
    }

    bstnode* subtree_last(){
        if(right){
            return static_cast<bstnode*>(right)->subtree_last();
        }else{
            return static_cast<bstnode*>(this);
        }
    }
    
};


int main()
{
    bstnode* root = new bstnode(10);
    bstnode* node5 = new bstnode(5);
    bstnode* node15 = new bstnode(15);
    bstnode* node3 = new bstnode(3);
    bstnode* node7 = new bstnode(7);
    bstnode* node12 = new bstnode(12);
    bstnode* node121 = new bstnode(12);
    bstnode* node18 = new bstnode(18);
    root->subtree_insert(node5);
    root->subtree_insert(node15);
    root->subtree_insert(node3);
    root->subtree_insert(node7);
    root->subtree_insert(node12);
    root->subtree_insert(node18);
    root->subtree_insert(node121);

root->subtree_iter();
cout<<endl;
cout<<"next element of"<<" "<<root->subtree_find_next(7)->data<<endl;
cout<<"previous element is"<<" "<<root->subtree_find_prev(7)->data;
 return 0;
}