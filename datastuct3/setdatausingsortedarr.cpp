#include<iostream>
#include<vector>
using namespace std;
class sortedarrayset{
 public:
    vector<int>array;

public:
int length(){
    return array.size();
}

void build(vector<int> &x){
    array=x;       //building it from an unsorted array and it is dynamic too
    sort(array.begin(),array.end());
}

int binarysearch(int key,int start,int end){
    if(start>end){
        return start;    //here it is for getting the element close to thaat
    }
    int m=start+(end-start)/2;
    if(array[m]==key){
        return m;
    }
    else if(array[m]>key){
        return binarysearch(key,start,m-1);
    }
    else if(array[m]<key){
        return binarysearch(key,m+1,end);
    }
}

int min(){
    if(!array.empty()){
        return array[0];
    }
    else return -1;
}

int max(){
    if(!array.empty()){
        return array[array.size()-1];
    }
    else return -1;
}

int findelement(int k){
    if(array.empty()){
        return -1;
    }
    int index=binarysearch(k,0,array.size()-1);
    if(array[index]==k){
        return array[index];
    }else{
        return -1;
    }
}

int findnextgreater(int key){
    if(array.empty()){
        return -1;
    }
    int i=binarysearch(key,0,array.size()-1);
    if(array[i]>key){
        return array[i];
    }
    if(i+1<array.size()){
        return array[i+1];
    }
    return -1;
}

int findprevsmaller(int key){
    if(array.empty()){
        return -1;
    }
    int i=binarysearch(key,0,array.size()-1);
    if(array[i]<key){
        return array[i];
    }
    if(i-1>=0){
        return array[i-1];
    }
    return -1;
}

bool insert(int x){
    if(array.empty()){
        array.push_back(x);
        return true;
    }else{
        int i=binarysearch(x,0,array.size()-1);
        if(array[i]==x){
            return false;
        }
        if(array[i]>x){array.insert(array.begin()+i,x);}
        else{
            array.insert(array.begin()+i+1,x);
        }
        return true;
    }
}

bool deletelement(int k){
    int i=binarysearch(k,0,array.size()-1);
    if(array[i]==k){
        array.erase(array.begin()+i);
    }
    return true;
}
};

int main()
{
 return 0;
}