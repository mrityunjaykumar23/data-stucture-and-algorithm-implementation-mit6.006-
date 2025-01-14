#include<iostream>
using namespace std;
class arraycrea{
    public:
        int *arr;
        int size;
        int capacity;

 public:
    arraycrea(int cap=10){
        size=0;
        arr=new int[cap];
        capacity=cap;
    }    
    ~arraycrea(){
        delete[] arr;
    }  

    int length(){
        return size;
    }
    void build(int arr1[],int n){    //here we are making an array from items in array
        if(n>capacity){
            capacity=n;
            delete[] arr;
            arr=new int[capacity];
            for(int i=0;i<n;i++){
                arr[i]=arr1[i];
            }
            size=n;
        }
    }
    int get_at(int i){
        if(i<0 || i>=size){
            cout<<"element is not available as it is out of bond";
            return -1;
        }
        return arr[i];
    }

    void set_at(int i,int value){
        if(i<0 || i>=size){
            cout<<"element is not available as it is out of bond";
            return ;
        }
        arr[i]=value;
    }
    void copyforward(arraycrea name,int n,int i,int j,int arr1[]){
        for(int k=0;k<n;k++){               //here copying is done from a object to an array of length n and first element i .
            arr1[i+k]=name.arr[j+k];
        }
    }
   void copybackward(arraycrea name,int n,int i,int j,int arr1[]){
        for(int k=n-1;k>=0;k--){
            arr1[i+k]=name.arr[j+k];
        }
   }
};
int* insert(int i,int x,int arr[],int n){
    int *arr2=new int[n+1];  //if normally allocated like new int[] then it will be allocated on stack if function call removed then it removes from stack
    for(int k=0;k<i;k++){
        arr2[k]=arr[k];
    }
    arr2[i]=x;
    for(int k=i;k<n+1;k++){
        arr2[k+1]=arr[k];
    }
    return arr2;   //for returning a array you have to return its pointer
}

int main()
{
    int arr[5]={1,2,3,4,5};
    int *array=insert(3,19,arr,5);
    for(int i=0;i<6;i++){
        cout<<array[i];
    }
 return 0;
}