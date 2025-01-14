#include<iostream>
#include<vector>
class item{
    public:
    int key;
};

class obj {
public:
    vector<int> digits;
    int item;
    int key;
};

using namespace std;
void directacesssort(vector<int>&input){
    int maxkey= *max_element(input.begin(),input.end());   //finding the maximum element
    vector<int> temporary(maxkey+1);      //making vector of that size for direct access array
    for(int i=0;i<input.size();i++){
        temporary[input[i]]=input[i];        
    }
    int index=0;
    for(int i=0;i<maxkey+1;i++){         //going through the direct access array and putting in original one for sorted
        if(temporary[i]){
            input[index++]=temporary[i];
        }
    }
}

void countingsort1(vector<item> &input){   //for you can also add additional things in items
    int max_key=0;              
    for(const auto& item:input){        //for finding the maximum key
        max_key=max(max_key,item.key);
    }
    vector<vector<item> >direct(max_key+1); //initialising chain in direct access array as chain you can also do dynamic array(as here) or linked list(as in hashtable)
    for(const auto&item:input){              
        direct[item.key].push_back(item);
    }
    for(const auto&chain: direct){         //here we are like backtracking the elements
        for(auto&ele:chain){
            input.push_back(ele);
        }
    }
}

void countingsort2(vector<int>&input){      //here only for integer
    int max_key=*max_element(input.begin(),input.end());
    vector<int>count(max_key+1,0);
    for(int key:input){
        count[key]++;
    }
    for (int i = 0; i <= max_key; ++i) {
        for (int j = 0; j < count[i]; ++j) {
            input.push_back(i);
        }
    }
}

void countingsort3(vector<int>&input){
    int max_key=*max_element(input.begin(),input.end());
    vector<int>count(max_key+1,0);
    for(int key:input){
        count[key]++;
    }

    for(int k=1;k<=max_key;k++){             //cumulative counting the scores
        count[k]=count[k]+count[k-1];
    }
    vector<int>sorted(input.size());        //putting at the correct place
    for(int i=input.size()-1;i>=0;i--){     //here we can write it from i=0 also it does not affect it
        sorted[count[input[i]]-1]=input[i];  //for finding the correct place in sorted array and by cumulative count to get the correct position
        count[input[i]]--;                      //here updating the count array
    }
    input=sorted;
}


int main()
{
    vector<int>input={25,4,1,3,9,16};
    countingsort3(input);
    for(int i=0;i<input.size();i++){
        cout<<input[i]<<" ";
    }
 return 0;
}



