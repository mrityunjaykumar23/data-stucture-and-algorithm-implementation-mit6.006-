#include <bits/stdc++.h>
#include<iostream>       //implementing  in place priorityqueue sort 
using namespace std;
class inplacepriorityqueue{
    private:
    vector<int>container;
    int n;

    void max_heapify_up(int index){
        while(index>0){
            int parent=(index-1)/2;
            if(container[parent]<container[index]){
                swap(container[parent],container[index]);
                index=parent;
            }else{
                break;
            }
        }
    }

    void max_heapify_down(int index){
        int left=2*index+1;
        int right=2*index+2;
        int largest=index;
        if(left<n && container[left]>container[largest]){
            largest=left;
        }
        if(right<n && container[right]>container[largest]){
            largest=right;
        }
        if(largest!=index){
        swap(container[index],container[largest]);
        max_heapify_down(largest);}
    }

public:
    inplacepriorityqueue(vector<int>&array){
        this->container=array;
        this->n=0;
    }

    void insert(){
        if(!(n<container.size())){
            throw runtime_error("insert into full priority queue");
        }
        n++;
        max_heapify_up(n-1);
    }

    void delete_max(){
        if(n<1){
            throw runtime_error("delete from empty priority queue");
        }
        swap(container[0],container[n-1]);
        n--;
        max_heapify_down(0);
    }

    vector<int> sort(vector<int>&array){
        inplacepriorityqueue pq(array);
        //building max heap first;
        for(int i=0;i<array.size();i++){
            pq.insert();
        }
        //deleting the item 
        for(int i=0;i<array.size()-1;i++){
            pq.delete_max();
        }
        return pq.container;
    }
};
int main()
{
    vector<int>first={38,12,21,10,76,56,23,98,75};
inplacepriorityqueue pq(first);
vector<int>result=pq.sort(first);
for(auto i:result){
    cout<<i<<" ";
}

 return 0;
}