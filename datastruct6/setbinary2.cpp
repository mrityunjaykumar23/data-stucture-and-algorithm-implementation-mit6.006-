#include<iostream>   //for whole previously is for subtree
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
        if(left || right){
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

class bstnode : public binarynode{
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



class setbinarytree{    //here you are not inheriting any class but using all its functions using the composition as you have used instance of that class 
public:
    bstnode *root;     //instance used by defining any variable
    int size;

    setbinarytree(){
        this->root=NULL;
        this->size=0;
    }

    ~setbinarytree(){
        delete_tree(root);
    }

    void delete_tree(bstnode *node){
        if(node){
            if(node->left){
                delete_tree(static_cast<bstnode*>(node->left));}
            if(node->right){
                delete_tree(static_cast<bstnode*>(node->right));}
            delete node;
        }
    }

    void insert(int value){
        bstnode *newnode=new bstnode(value);
        if(root==NULL){
            root=newnode;
            size++;
            // return true;
        }else{
            root->subtree_insert(newnode);
        }
    }

    bool find(int value){
        if(root==NULL){
            return false;
        }else{
            return root->subtree_find(value);
        }
    }

    int find_min(){
        if(root==NULL){
            throw std::runtime_error("tree is empty");
        }
        else{
            return root->subtree_first()->data;
        }
    }

    int find_max(){
        if(root==NULL){
            throw std::runtime_error("tree is empty");
        }else{
            return root->subtree_last()->data;
        }
    }

    int find_next(int value){
        if(root==NULL){
            throw std::runtime_error("tree is empty");
        }
        bstnode* newnode=root->subtree_find_next(value);
        if(newnode==NULL){
            throw::std::runtime_error("no larger element is found");
        }else{
            return newnode->data;
        }
    }

    int find_prev(int value){
        if(root==NULL){
            throw std::runtime_error("tree is empty");
        }
        bstnode* newnode=root->subtree_find_prev(value);
        if(newnode==NULL){
            throw std::runtime_error("no smaller element is found");
        }else{
            return newnode->data;
        }
    }

    bool delete_value(int value){
        if(root==NULL){
            return false;
        }
        bstnode *node=root->subtree_find(value);
        if(node==NULL){
            return false;
            throw std::runtime_error("node not found");
        }
        bstnode* ext=static_cast<bstnode*>(node->subtree_delete());
        if(ext->parent==NULL){
            root=NULL;
        }
        size--;
        return true;
    }

void inorder_traversal(bstnode *node){
    if(node==NULL){
        return;
    }
    inorder_traversal(static_cast<bstnode*>(node->left));
    cout<<node->data<<" ";
    inorder_traversal(static_cast<bstnode*>(node->right));
}

void iterate(){
    if(root==NULL){
        cout<<"tree is empty";
        return;
    }
    inorder_traversal(root);
    cout<<endl;
}

};
int main()
{
setbinarytree tree;
tree.insert(28);
tree.insert(18);
tree.insert(38);
tree.insert(48);
cout<<"inorder traversal of the tree";
tree.iterate();
cout<<tree.find(18)<<endl;
cout<<tree.find_min()<<endl;
cout<<tree.find_max()<<endl;
cout<<tree.find_next(28)<<endl;
cout<<tree.find_prev(28)<<endl;
 return 0;
}
