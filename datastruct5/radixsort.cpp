#include<iostream>
#include<vector>
#include<cmath>
using namespace std;
class obj {
public:
    vector<int> digits;
    int item;
    int key;
};

void countingsort(vector<obj>&input){
    int max_key=0;              
    for(const auto& item:input){      
        max_key=max(max_key,item.key);
    }
    vector<int>count(max_key+1,0);
    for(int i=0;i<input.size();i++){
        count[input[i].key]++;
    }

    for(int k=1;k<=max_key;k++){
        count[k]=count[k]+count[k-1];
    }

    vector<obj>sorted(input.size());
     for (int i = input.size() - 1; i >= 0; --i) {
        sorted[count[input[i].key] - 1] = input[i];     //here we are doing all sorting parallelly means all item keys and digits all 
        count[input[i].key]--;
    }

    for (int i = 0; i <input.size(); ++i) {
        input[i] = sorted[i];
    }
}

void radixsort(vector<int>&input){
    int max_key=*max_element(input.begin(),input.end());
    int noofdigit=1+log2(max_key)/log2(input.size());   //1 is important if we change the digit just means for 2 to 3
    vector<obj>tupple(input.size());
    for(int i=0;i<input.size();i++){
        tupple[i].item=input[i];
        int high=input[i];

        for(int k=0;k<noofdigit;k++){
            int low=high%input.size();
            tupple[i].digits.push_back(low);
            high=high/input.size();
        }
    }
    for (int i = 0; i < noofdigit; ++i) {
        for (int j = 0; j < input.size(); ++j) {
            tupple[j].key = tupple[j].digits[i];  // Assign key to each object based on the current digit
        }

        // Sort D based on the current digit (key)
        countingsort(tupple);                       //each time we are using counting sort to sort from least to most significant digit and we are maintaining previous round as we studied in copy
        for(int i=0;i<tupple.size();i++){
            cout<<tupple[i].item<<" ";
        }
        cout<<endl;
    }

    // Step 6: Output the sorted items back to A
    for (int i = 0; i < input.size(); ++i) {        //so as in each counting sort as we sort the keys it also accordingly sorted the item
        input[i] = tupple[i].item;
    }
}


int main()
{
    vector<int>input={123,216,66,77,215,67};
    radixsort(input);
    for(int i=0;i<input.size();i++){
        cout<<input[i]<<" ";
    }
 return 0;
}
