#include<iostream>
using namespace std;
#include<iostream>
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
    cout<<"inorder traversal before";
    root->subtree_iter();
    cout<<endl;
    root->rotateright(root);
    root->subtree_iter();
    cout<<"height of the root"<<root->getheight(root);
    
 return 0;
}