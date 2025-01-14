#include<iostream>
#include<bits/stdc++.h>
using namespace std;
class binarynode{
    public:
    int data;
    int height;
    binarynode *left;
    binarynode *right;
    binarynode *parent;

    binarynode(int x){
        this->height=1;
        data=x;
        this->left=NULL;
        this->right=NULL;
        this->parent=NULL;
    }

    int getheight(binarynode* node){
        if(node){
            return node->height;
        }else{
            return -1;
        }
    }

    void updateheight(){
        height=1+max(getheight(left),getheight(right));
    }
    
    int skew(){
        return getheight(right)-getheight(left);
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
        }else{
        right=newnode;
        newnode->parent=this;}
        maintain();
    }

    void subtree_insertbefore(binarynode* newnode){
        if(left){
            predecessor()->right=newnode;
            newnode->parent=predecessor();

        }else{
        left=newnode;
        newnode->parent=this;}
        maintain();
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
            parent->maintain();
        }
        return this;
    }

    void rotateright(binarynode* nodeD){
        if(nodeD==NULL || nodeD->left==NULL){  //we ensure nodeD not to be null and left of that also
            return;
        }
        binarynode* nodeB=nodeD->left;
        binarynode *nodeE=nodeD->right;
        binarynode *nodeA=nodeB->left;
        binarynode *nodeC=nodeB->right;
        binarynode *temp;
        temp=nodeB;   //this whole swapping is done so that after executing we can return same node node5 not nodeB(in other case)
        nodeB=nodeD;
        nodeD=temp;


        swap(nodeB->data,nodeD->data);
        nodeB->left=nodeA;
        nodeB->right=nodeD;
        nodeD->left=nodeC;
        nodeD->right=nodeE;

        if(nodeA!=NULL){
            nodeA->parent=nodeB;
        }
        if(nodeE!=NULL){nodeE->parent=nodeD;}
        
        nodeB->updateheight();
        nodeD->updateheight();
        // return nodeB;
    }

    void rotateleft(binarynode* nodeB){
        if(nodeB==NULL || nodeB->left==NULL){
            return;
        }
        binarynode* nodeA=nodeB->left;
        binarynode* nodeD=nodeB->right;
        binarynode* nodeC=nodeD->left;
        binarynode* nodeE=nodeD->right;
        binarynode *temp;
        temp=nodeB;
        nodeB=nodeD;
        nodeD=temp;
        swap(nodeB->data,nodeD->data);
        nodeD->left=nodeB;
        nodeD->right=nodeE;
        nodeB->right=nodeC;
        nodeB->left=nodeA;
        if(nodeE){
            nodeE->parent=nodeD;
        }
        if(nodeA){
            nodeA->parent=nodeB;
        }
        nodeD->updateheight();
        nodeB->updateheight();
    }

    void rebalance(){
        if(skew()==2){
            if(right && right->skew()<0){
                right->rotateright(right);
                rotateleft(this);
            }else{
                if(right&& right->skew()>=0){
                    rotateleft(this);
                }
            }
        }else if(skew()==-2){
            if(left && left->skew()>0){
                left->rotateleft(left);
                rotateright(this);
            }else{
                if(left && left->skew()<0){
                    rotateright(this);
                }
            }
        }
        }

        void maintain(){
            rebalance();
            updateheight();
            if(parent){
                parent->maintain();
            }
        }
};

class size_node:public binarynode{
    public:
    int size;
    size_node(int x):binarynode(x){
        size=1;
    }

    void subtree_update(){
        binarynode::updateheight();     //here it is showing that we are using function of binarynode class we can do it without using it also
        size=1;
        if(left){
            size=size+static_cast<size_node*>(left)->size;   //it is a type of casting process in c++ and another one is dynamic cast which is to be done if we are not sure whether it is wrote or wrong (so it checks at runtime)
        }
        if(right){
            size=size+static_cast<size_node*>(left)->size;
        }
    }

    size_node* subtree_at(int i){
        if(i<0){
            throw std::runtime_error("index is not valid");
        }
        int leftsize=(left)?static_cast<size_node*>(left)->size:0;
        if(i<leftsize){
            return static_cast<size_node*>(left)->subtree_at(i);
        }
        else if(i>leftsize){
            return static_cast<size_node*>(right)->subtree_at(i-leftsize-1);
        }
        else{
            return this;
        }
    }
};

class sequence_binarytree{
    public:
    size_node *root;
    int size;
    sequence_binarytree(){
        this->root=NULL;
        this->size=0;
    }

    void build(vector<int>&array){
        root=build_subtree(array,0,array.size()-1);
        size=root->size;
    }

    size_node* build_subtree(vector<int>&array,int i,int j){
        if(i>j){
            return NULL;
        }
        int mid=(i+j)/2;
        size_node *root=new size_node(array[mid]);
        if(i<mid){
            root->left=build_subtree(array,i,mid-1);
            static_cast<size_node*>(root->left)->parent=root;
        }
        if(i>mid){
            root->right=build_subtree(array,mid+1,j);
            static_cast<size_node*>(root->right)->parent=root;
        }
        root->subtree_update();
        return root;
    }

    int get_at(int i){
        assert(root!=NULL);
        return root->subtree_at(i)->data;
    }
    
    void set_at(int i,int x){
        assert(root!=NULL);
       size_node *node= root->subtree_at(i);
       node->data=x;
    }

    void insert_at(int i,int x){
       binarynode* newnode=new binarynode(x);
       if(i==0){
        if(root!=NULL){
            binarynode *node=root->subtree_first();
            node->subtree_insertbefore(newnode);
        }
        else{
            root=static_cast<size_node*>(newnode);
        }
       }else{
        binarynode* node=root->subtree_at(i-1);
        node->subtree_insertafter(newnode);
       }
       size++;
    }

    int delete_at(int i){
        assert(root!=NULL);
        binarynode* node=root->subtree_at(i);
        binarynode* ext=node->subtree_delete();
        if(ext->parent==NULL){
            root=NULL;
        }
        size--;
        return ext->data;
    }

    void insert_first(int x){
        insert_at(0,x);
    }
    void insert_last(int x){
        insert_at(size,x);
    }
    int delete_first(){
        return delete_at(0);
    }
    int delete_last(){
        return delete_at(size-1);
    }
};
int main()
{
    
    // Create a small tree
    size_node* root = new size_node(10);
    size_node* left_child = new size_node(5);
    size_node* right_child = new size_node(15);

    root->left = left_child;
    root->right = right_child;
    left_child->parent = root;
    right_child->parent = root;

    // Update the tree sizes
    root->subtree_update();

    // Access nodes by index
    cout << "Node at index 0: " << root->subtree_at(0)->data << endl;  // Output: 5
    cout << "Node at index 1: " << root->subtree_at(1)->data << endl;  // Output: 10
    cout << "Node at index 2: " << root->subtree_at(2)->data << endl;  // Output: 15


 return 0;
}