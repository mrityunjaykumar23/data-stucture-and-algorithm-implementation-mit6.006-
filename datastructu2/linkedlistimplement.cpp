#include<iostream>
using namespace std;
class Node{
    public:
        int data;
        Node *next;
   public:
        Node(int x){
            this->data=x;
            this->next=NULL;
        }
    ~Node(){
        int value=this->data;
        if(this->next!=NULL){
            this->next = NULL;
            delete next;
        }
        cout<<"the value for this node"<<value;
    }
};

void insertathead(Node *&head,Node *&tail,int x){
    Node *temp=new Node(x);
    if(head==NULL){  //for empty list
        head=temp;
        tail=temp;
    }else{
        temp->next=head;
        head=temp;
    }
}

void insertattail(Node *&head,Node *&tail,int x){
    Node *temp=new Node(x);
    if(head==NULL){
        head=temp;
        tail=temp;
    }else{
        tail->next=temp;
        tail=temp;
        tail->next=NULL;
    }
}

void insertionatmiddle(int position,int x,Node*&head,Node*&tail){
    if(position==1){
        insertathead(head,tail,x);
        return;
    }
    Node*temp=head;
    int count=1;
    while(count<position-1){
        temp=temp->next;
        count++;
    }
    if(temp->next==NULL){
        insertattail(head,tail,x);
        return;
    }
    Node *insertnode=new Node(x);
    insertnode->next=temp->next;
    temp->next=insertnode;
}

void deletenode(int position,Node *&head,Node *&tail){
    if(position==1){
        Node *temp=head;  //have taken temp to keep track of this only
        head=head->next;
        temp->next=NULL;
        delete temp;
        return;
    }
    Node *curr=head;
    Node *prev=NULL;
    int count=1;
    while(count<position){
        prev=curr;
        curr=curr->next;
        count++;
    }
    prev->next=curr->next;
    curr->next=NULL;
    if(curr=tail){
        tail=prev;
    }
    delete curr;
}

void print(Node *head){
    while(head!=NULL){
        cout<<head->data<<" ";
        head=head->next;
    }
}
int main()
{
    Node *head=NULL;
    Node* tail=NULL;
    insertathead(head,tail,10);
    insertattail(head,tail,12);
    print(head);

 return 0;
}