#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
vector<int>bfs(vector<vector<int>>&adjacency,int source){
    int vertex=adjacency.size();   
    vector<int>parent(vertex,-1);   //making a parent array to keep track of previous vertex
    parent[source]=source;          //initialising the source as source
    vector<vector<int> >level;      //initialising the level sets
    level.push_back({source});      //as initial level is the source only
    int i=0;
    while(!level[i].empty()){        
        level.push_back(vector<int>());
        for(int u:level[i]){        //lopping over all the level
            for(int v:adjacency[u]){    //so looping over all the next element of the level[i]
                if(parent[v]==-1){
                    parent[v]=u;        //so that parent of that is the previous one
                    level[i+1].push_back(v);    //so putting that v in next level
                }
            }
        }
        i++;
    }
    return parent;
}
vector<int>shortest_unweighted_path(vector<vector<int>> &adjacency,int source ,int destination){
    vector<int>parent=bfs(adjacency,source);
    vector<int>path={destination};
    if(parent[destination]==-1){
        return {};
    }
    int i=destination;
    while(i!=source){
        i=parent[i];
        path.push_back(i);
    }
    reverse(path.begin(),path.end());
    return path;
}
int main()
{
    vector<vector<int> > adjacencylist={{1,4,3},{0},{3},{0,2},{0}};
    // for(auto item:adjacencylist){
    //     for(auto items:item){
    //         cout<<items<<" ";
    //     }
    // }
    // vector<int>result=bfs(adjacencylist,0);
    // for(auto res:result){
    //     cout<<res<<" ";
    // }
    vector<int>result2=shortest_unweighted_path(adjacencylist,1,4);
    cout<<"the shortest path of the graph from the given source and destination are:"<<endl;
    for(auto res:result2){
        cout<<res<<" ";
    }

 return 0;
}