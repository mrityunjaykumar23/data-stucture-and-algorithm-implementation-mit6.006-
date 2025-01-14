#include<iostream>
using namespace std;
class node{
    public:
    int data;
    node* next;

node(int n){
    this->data=n;
    this->next=NULL;
}
};

void createcycle(node *head,int position){
    node *temp=head;
    int count=0;
    while(count<position){
        temp=temp->next;
        count++;
    }
    node *cyclenode=temp;
    while(temp->next!=NULL){
        temp=temp->next;
    }
    temp->next=cyclenode;
}

int cyclelength(node *head){
    node *fast=head;
    node *slow =head;
    while(fast!=NULL && fast->next!=NULL){
        fast=fast->next->next;
        slow=slow->next;
        if(fast==slow){
            int length=1;
            node*temp=slow;
            while(temp->next!=slow){
                temp=temp->next;
                length++;
            }
            return length;
        }
    }
    return 0;
}


void print(node *head){
    node *temp=head;
    while(temp!=NULL){
        cout<<temp->data<<" ";
        temp=temp->next;
    }
}
int main()
{
node *head=new node(10);
head->next=new node(20);
head->next->next=new node(20);
head->next->next->next=new node(20);
head->next->next->next->next=new node(20);
createcycle(head,1);
cout<<cyclelength(head);
 return 0;
}