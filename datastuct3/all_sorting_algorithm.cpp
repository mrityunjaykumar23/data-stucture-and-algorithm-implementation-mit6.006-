#include<iostream>
#include<algorithm>
using namespace std;
void selectionsort(int *arr,int start,int end){  //selection sort
    
    for(int i=end-1;i>0;i--){
        int m=i;
        for(int j=i-1;j>=0;j--){
            // int maxi=0;
            if(arr[j]>arr[m]){
                // maxi=arr[j];
                m=j;
            }
        }
            swap(arr[i],arr[m]);
    }
}

void insertionsort(int *arr,int start,int end){    //insertion sort
    for(int i=1;i<end;i++){
        for(int j=i-1;j>=0;j--){
            if(arr[j]>arr[j+1]){
            swap(arr[j],arr[j+1]);
            }
            else{
                break;    //to just reduce the time complexity
            }
        }
    }
}

void merge(int *arr,int start,int end){             //merge sort
    int mid=start + (end-start)/2;
    int len1 = mid - start + 1;
    int len2 = end - mid;
    int *first=new int[len1];
    int *second=new int[len2];
    int index1=0;
    int index2=0;
    int mainindex=start;

    for(int i=0;i<len1;i++){
        first[i]=arr[mainindex++];
    }
    for(int j=0;j<len2;j++){
        second[j]=arr[mainindex++];
    }
    mainindex=start;
    while(index1<len1 && index2<len2){
        if(first[index1]<second[index2]){
            arr[mainindex++]=first[index1++];
        }else{
            arr[mainindex++]=second[index2++];
        }
    }

    while(index1<len1){
        arr[mainindex++]=first[index1++];
    }
    while(index2<len2){
        arr[mainindex++]=second[index2++];
    }
    delete[]first;
    delete[]second;

}
void mergesort(int *arr,int start,int end){
    if(start>=end){
        return;
    }
    int mid=start+(end-start)/2;
    mergesort(arr,start,mid);
    mergesort(arr,mid+1,end);
    merge(arr,start,end);
}

int main()
{
int arr[5]={23,1,0,35,12};
mergesort(arr,0,4);
for(int i=0;i<5;i++){
    cout<<arr[i]<<" ";
}
 return 0;
}