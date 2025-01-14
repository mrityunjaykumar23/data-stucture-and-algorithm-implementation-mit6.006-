#include<iostream>
#include<algorithm>
#include<vector>
#include<list>
#include<cstdlib>
using namespace std;

class hashtable{
    public:
    int r;
    int size;   //size of hashtable it means no of unique element in it
    int lower;
    int upper;
    int p,a;
    vector<list<int> >many;

public:
int hash(int k,int m){         //hash(O(1))
    return (((a*k)%p)%m);
}

void compute_bounds(){
    upper=many.size();
    lower=(many.size()*100*100)/(r*r);
}

void resize(int n){                // resize:(O(n))
    if(n<=lower|| n>=upper){
        int f=r/100;
        if(r%100){f+=1;}
        int m=max(n,1)*f;
        vector<list<int> >newa(m);
        for(const auto &chain:many){
            for(int x:chain){
                int h=hash(x,m);
                newa[h].push_back(x);
            }
        }
        many=move(newa);
        compute_bounds();
    }
}

hashtable(int r=200){
    size=0;
    p=2147483647;
    a=rand()%(p-1)+1;
    compute_bounds();
    resize(0);
}

bool insert(int x){             //insert:(O(1))
    resize(size+1);
    int h=hash(x,many.size());
    for(int element:many[h]){
        if(element==x){
            return false;
        }
    }
    many[h].push_back(x);
    size++;
    return true;
}

bool find(int k){                   //find:(O(1))
    int h=hash(k,many.size());
    for(int ele:many[h]){
        if(ele==k){
            return true;
        }
    }
    return false;
}

bool erase(int k){            //delete(O(1))
    int h=hash(k,many.size());
    auto &chain=many[h];
    for(auto it=chain.begin();it!=chain.end();++it){
        if(*it==k){
            chain.erase(it);
            size--;
            resize(size);
            return true;
        }
    }
    return false;
}

int find_min(){                             //find_min(O(n))
    int min=__INT_MAX__;
    for(const auto& chain:many){
        for(int ele:chain){
            if(min==__INT_MAX__||ele<min){
                min=ele;
            }
        }
    }
    return min;
}

int find_max(){                                  //find_max(O(n))
    int max=-1;
    for(const auto &chain:many){
        for(int ele:chain){
            if(max==-1 || ele>max){
                max=ele;
            }
        }
    }
    return max;
}

int find_nextbigger(int k){                      //find_nextbigger(O(n))
    int min=-1;
    for(const auto&chain:many){
        for(int ele:chain){
            if(ele>k){
                if(min==-1 || ele<min){
                    min=ele;
                }
            }
        }
    }
    return min;
}

int findprev_smaller(int k){                     //findprev_smaller(O(n))
    int out=-1;
    for(const auto&chain:many){
        for(int ele:chain){
            if(ele<k){
                if(out==-1||ele>out){
                    out=ele;
                }
            }
        }
    }
    return out;
}

void printorder(){                               //printorder(O(n^2))
    int x=find_min();
    while(x!=-1){
        cout<<x<<endl;
    x=find_nextbigger(x);
    }
}
};

int main()
{
    hashtable ht;
    ht.insert(5);
    ht.insert(6);
    ht.insert(4);
    ht.insert(2);

ht.printorder();

 return 0;
}