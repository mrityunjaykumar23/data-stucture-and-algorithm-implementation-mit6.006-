#include<iostream>
using namespace std;
class dynamicarray{
    public:
    int * oldarray;
    int size;
    int capacity;
    int r;
    int lower; 
    int upper;

void computebounds(){
    upper=capacity;
    lower=capacity/(r*r);
}
void copyforward(int i,int n,int *newarray,int j){  //j is the index of newarray from where the copy will start
    for(int k=0;k<n;k++){
        newarray[k+j]=oldarray[k+i];
    }
}
void copybackwards(int i,int n,int *newarray,int j){
    for(int k=n-1;k>=0;k--){
        newarray[j+k]=oldarray[i+k];
    }
}

void resize(int n){
    if(lower<n && n<upper){
        return;
    }
    int newcapacity=max(n,1)*r;
    int *newarray=new int[newcapacity];
    copyforward(0,size,newarray,0);
    delete[] oldarray;                  //here by deleting wont delete the oldarray pointer it only delete the memory occupancy of the element
    oldarray=newarray;
    capacity=newcapacity;
    computebounds();
}

dynamicarray(int r=2){
    this->r=r;
    this->size=0;
    this->capacity=0;
    oldarray=NULL;
    computebounds();
    resize(0);
 }

 ~dynamicarray(){
    delete[] oldarray;
 }
int getsize(){
    return size;
}
void insertlast(int x){
    resize(size +1);
    oldarray[size]=x;
    size++;
}

void deletelast(){
    if(size>0){
        oldarray[size-1]=0;
        size--;
        resize(size);
    }
}

void insertatindx(int i,int x){         //inserting x at index i
    insertlast(0);
    copybackwards(i,size-(i+1),oldarray,i+1);
    oldarray[i]=x;
}

int deleteat(int i){
    int x=oldarray[i];
    copyforward(i+1,size-(i+1),oldarray,i);
    deletelast();
    return x;
}

void inserfirst(int x){
    insertatindx(0,x);
}
int  deletefirst(){
    return deleteat(0);
}

void display(){
    for(int i=0;i<size;i++){
        cout<<oldarray[i]<<" ";
    }
}
};
int main()
{
    dynamicarray arr;
    arr.insertlast(10);
    arr.insertlast(20);
    arr.insertlast(30);
    arr.display();
    cout<<arr.size<<" ";
    cout<<arr.capacity;

 return 0;
}



