#include<iostream>
#include<map>
#include<vector>
using namespace std;
class fibonachitopdpwn{
    unordered_map<int,int>memo;
    int function(int i){
        if(i<0){
            throw invalid_argument("the number is not defined for negative argument");
        }
        if(i<2){
            return i;
        }
        if(memo.find(i)==memo.end()){
            memo[i]=function(i-1)+function(i-2);
        }
        return memo[i];
    }
    public:
    int fib(int n){
        return function(n);
    }
};

int  fibonachiibottomup(int n){
    vector<int>memo(n);
    memo[0]=0;
    memo[1]=1;
    for(int i=2;i<=n;i++){
        memo[i]=memo[i-1]+memo[i-2];
    }
    return memo[n];
}

class bowl{
    unordered_map<int,int>memo;
    public:
    int b(int i,vector<int>v){
        if(i>=v.size()){
            return 0;
        }
        if(memo.find(i)==memo.end()){
            int bowlpinseperately,bowltwopins=0;
            int skippin=b(i+1,v);
             bowlpinseperately=b(i+1,v)+v[i];
             bowltwopins=i+1<v.size()?v[i]*v[i+1]+b(i+2,v):0;
            memo[i]=max({skippin,bowlpinseperately,bowltwopins});
        }
        return memo[i];
    }

    int bowling(vector<int>&v){
        return b(0,v);
    }
};

int bowlinbottomup(vector<int>& array) {
    int n = array.size();
    vector<int> memo(n + 2, 0); // Initialize memoization array with 0
    memo[n] = 0;               // Base case
    memo[n+1] = 0;             // Base case for out-of-bounds

    for (int i = n - 1; i >= 0; i--) {
        memo[i] = max({
            memo[i+1],                                // Skip pin i
            array[i] + memo[i+1],                    // Bowl pin i separately
            ((i+1 < n )? array[i] * array[i+1]+memo[i+2] : 0) // Bowl pins i and i+1 together
        });
    }

    return memo[0];
}


int main()
{
    vector<int>v={1,2,3,4};
    bowl game;
    cout<<game.bowling(v);
    // cout<<bowlinbottomup(v);
 return 0;
}

//memoization implementation