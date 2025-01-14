#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
pair<int,string> longestcommonsubsequence(string &first,string &second){
    int len1=first.size();
    int len2=second.size();
    vector<vector<int>> memo(len1+1,vector<int>(len2+1,0));
    for(int i=len1-1;i>=0;i--){
        for(int j=len2-1;j>=0;j--){
            if(first[i]==second[j]){
                memo[i][j]=memo[i+1][j+1]+1;
            }else{
                memo[i][j]=max(memo[i+1][j],memo[i][j+1]);
            }
        }
    }

    //backtracking to get to the final answer here we are doing the parent pointer approach not explcitly writing the direction
    int i=0,j=0;
    string answer=" ";
    while(i<len1 && j<len2){
        if(first[i]==second[j]){
            answer+=first[i];
            j++;
            i++;
        }else if(memo[i+1][j]>memo[i][j+1]){
            i++;
        }else{
            j++;
        }
    }
    return {memo[0][0],answer};
}

int longestincreasingsubsequence(vector<char>&first){    //to see how to backtrack it
    int len=first.size();
    vector<int>memo(len,1);
    for(int i=len-1;i>=0;i--){
        for(int j=i+1;j<len;j++){
            if(first[j]>first[i]){
                memo[i]=max(memo[i],1+memo[j]);
            }
        }
    }
                    // here memo[0] cannot be the answer as it is possible that first is Z
    return *max_element(memo.begin(),memo.end());

}

 pair<int,string>lISparentpointers(vector<char>&first){    //to see how to backtrack it
    int len=first.size();
    string answer=" ";
    vector<int>memo(len,1);
    vector<int>parent(len,-1);
    for(int i=len-1;i>=0;i--){
        for(int j=i+1;j<len;j++){
            if(first[j]>first[i]&& memo[i]<memo[j]+1){
                memo[i]=memo[j]+1;
                parent[i]=j;
            }
        }
    }
    int startindex=-1;
    int max_length=0;
    for(int i=0;i<len;i++){
        if(memo[i]>max_length){
            startindex=i;
            max_length=memo[i];
        }
    }
    int curr_index=startindex;
    while(curr_index!=-1){
        answer+=first[curr_index];
        curr_index=parent[curr_index];
    }
    return {max_length,answer};
}

int main()
{
    string a="habit";
    string b="their"; 
    pair<int,string>answer=longestcommonsubsequence(b,a);
    cout<<answer.first<<endl;
    cout<<answer.second<<endl;
    vector<char>first={'c','a','r','b','o','h','y','d','r','a','t','e'};
    longestincreasingsubsequence(first);
    pair<int,string>result=lISparentpointers(first);
cout<<"maximum length of the longest increasing subsequence are:"<<result.first<<endl;
cout<<"THE Longest increasing subsequence are:"<<result.second;
 return 0;
}