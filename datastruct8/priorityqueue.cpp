#include<iostream>
#include<vector>
#include<algorithm>
#include<utility>
using namespace std;
class priorityqueue{       //it is just a interface of a priority queue that i am going to implement with different data structures
public:
    vector<int>container;
    priorityqueue(){}
    virtual void insert(int x){
        container.push_back(x);
    }

    virtual int delete_max(){    //here function to be overided
        if(container.size()<1){
            throw runtime_error("poping from the empty directory");
        }
        int maximum=container.back();  //here not necesarily the maximum element just making an interface
        container.pop_back();
        return maximum;         //not necessarily maximum
    }

    vector<int> sort(vector<int>&input){
        priorityqueue pq;
        vector<int>out;
        for(int x:input){
            pq.insert(x);
        }
        for(int i=0;i<input.size();i++){
            out.push_back(pq.delete_max());
        }
        reverse(out.begin(),out.end());
        return out;
    }
};

class priorityqueuearray:public priorityqueue{   //override is written to confirm about the overwriting(polymorphism)
public:
    int delete_max()override{
        if(container.empty()){
            throw runtime_error("pop from empty priority queue");
        }
        int mainindex=0;              //it is just selection sort
        for(int i=0;i<container.size();i++){
            if(container[mainindex]<container[i]){
                mainindex=i;
            }
        }
        swap(container[mainindex],container[container.size()-1]);
        return priorityqueue::delete_max();
    }
};

class prioritysortedarray:public priorityqueue{
    public:                                 //here delete_max will work automatically
    void insert(int x) override{
        priorityqueue::insert(x);
        int i=container.size()-2;
        while(i>=0 && container[i]>x){   //insertion sort
            container[i+1]=container[i];
            i--;
        }
        container[i+1]=x;
    }
};

class pq_heap:public priorityqueue{
    public:
    void insert(int value){
        priorityqueue::insert(value);
        int n=container.size();
        max_heapify_up(n-1,n);
    }

    int delete_max(){
        if(container.size()<=1){
            return priorityqueue::delete_max();
        }
        swap(container[0],container.back());
        int max_value=container.back();   
        container.pop_back(); 
        max_heapify_down(0,container.size());
        return max_value;
    }

private:
    int parent(int i){
        int p= (i-1)/2;
        return (p>0)? p:i;
    }
    int left(int i,int n){
        int l=2*i+1;
        return (l<n)? l:i;
    }
    int right(int i,int n){
        int r=2*i+2;
        return (r<n)? r:i;
    }

    void max_heapify_up(int i,int n){
        int p=parent(i);
        while(i>0 && container[p]<container[i]){
            swap(container[p],container[i]);
            i=p;
            p=parent(i);     //instead of recursion loop is written
        }
    }

    void max_heapify_down(int i,int n){
        int l=left(i,n);
        int r=right(i,n);
        int c;
        if(container[l]<container[r]){
            c=r;
        }else{
            c=l;
        }
        if(container[i]<container[c]){
            swap(container[i],container[c]);
            max_heapify_down(c,n);
        }
    }
void max_heapify_down1(vector<int>&array,int i,int n){
    int l=left(i,n);
        int r=right(i,n);
        int c;
        if(container[l]<container[r]){
            c=r;
        }else{
            c=l;
        }
        if(container[i]<container[c]){
            swap(container[i],container[c]);
            max_heapify_down(c,n);
        }
}
void buid_max_heap(vector<int>&array){
    int n=array.size();
    for(int i=n/2-1;i>=0;i--){
        max_heapify_down1(array,i,n);
    }
}
};


int main()
{
    // priorityqueuearray pq;     //insert is called of main class
    // pq.insert(2);
    // pq.insert(10);
    // pq.insert(8);
    // while(!pq.container.empty()){
    // cout<<pq.delete_max()<<endl;
    // }



 return 0;
}