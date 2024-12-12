#include<bits/stdc++.h>
#include<iostream>
using namespace std;
class cpqueue{                      //hash table implementation
    private:
    unordered_map<int,int>A;

public:
void insert(int label,int key){
    A[label]=key;
}

int extract_min(){
    int min_label;
    int min_key=numeric_limits<int>::max();
    for(const auto&pair:A){
        if(pair.second<min_key){
            min_key=pair.second;
            min_label=pair.first;
        }
    }
        A.erase(min_label);
        return min_label;
}
void decresase_key(int label,int key){
    if(A.find(label)!=A.end() && key<A[label]){
        A[label]=key;
    }
}
};

struct item{
    int key;
    int label;
    item(int first,int second){
        this->key=first;
        this->label=second;
    }
};

class cpqueueheap{
    private:
    vector<item>container;  //binaryheap array
    unordered_map<int,int>label2idx; //maps label to index in the heap

    void min_heapify_up(int c){
        if(c==0){return;} 
        int p=(c-1)/2;
        if(container[p].key > container[c].key){
            swap(container[p],container[c]);
            label2idx[container[p].label]=p;
            label2idx[container[c].label]=c;
            min_heapify_up(p);
        }
    }

    void min_heapify_down(int p){
        int l=2*p+1;
        int r=2*p+2;
        int smallest=p;
        if(l<container.size() && container[l].key<container[smallest].key){
            smallest=l;
        }
        if(r<container.size() && container[r].key<container[smallest].key){
            smallest=r;
        }
        if(smallest!=p){
            swap(container[p],container[smallest]);
            label2idx[container[p].label]=p;
            label2idx[container[smallest].label]=smallest;
            min_heapify_down(smallest);
        }
        
    }
public:
void insert(int label,int key){
    container.emplace_back(label,key);
    int idx=container.size()-1;
    label2idx[label]=idx;
    min_heapify_up(idx);
}

int extract_min(){
    if(!container.empty()){
        throw runtime_error("priorityqueue is empty");
    }
    swap(container[0],container.back());
    label2idx[container[0].label]=0;
    label2idx.erase(container.back().label);
    int min_label=container.back().label;
    container.pop_back();
    if(!container.empty()){
        min_heapify_down(0);
    }
    return min_label;   
}

void decrease_key(int label,int key){
    if(label2idx.find(label)!=label2idx.end()){
        int idx=label2idx[label];
        if(key<container[idx].key){
            container[idx].key=key;
            min_heapify_up(idx);
        }
    }
}

};
int main()
{
 return 0;
}