#include<iostream>    //given an array and to find a O(N) algorithm so that ith node of T traversal is ai.
#include<vector>
using namespace std;

class treenode{
    public:
    int data;
    treenode* left;
    treenode* right;
    treenode* parent;
    treenode(int value){
        this->data=value;
        this->left=NULL;
        this->right=NULL;
        this->parent=NULL;
    }
};

class binarytree{
    public:
    treenode* root;
    binarytree(){
        this->root=NULL;
    }

    treenode* build(vector<int> &array){
        return subtree(array,0,array.size()-1);
    }

    treenode* subtree(vector<int>&array,int i,int j){
        if(i>j){
            return NULL;
        }
        int mid=(i+j)/2;
        treenode* node=new treenode(array[mid]);
        node->left=subtree(array,i,mid-1);
        if(node->left){
            node->left->parent=node;
        }

        node->right=subtree(array,mid+1,j);
        if(node->right){
            node->right->parent=node;
        }
        return node;
    }

    public:
    void inordertraversal(treenode* node){
        if(!node){
            return;
        }
        inordertraversal(node->left);
        cout<<node->data<<" ";
        inordertraversal(node->right);
    }
    
};
int main()
{
    vector<int> store = {10,11,12,4,5,6,7,8,9};
    binarytree first;
    first.root=first.build(store);
    first.inordertraversal(first.root);
 return 0;
}

