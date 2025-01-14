#include<iostream>
#include<tuple>
#include<utility>
#include<vector>
using namespace std;
void dfs(vector<vector<int>>&adj,int source,vector<int>&order,vector<int>&parent){
    if(parent[source]==-1){
        parent[source]=source;          
    }
    for(int v:adj[source]){
        if(parent[v]==-1){
            parent[v]=source;
            dfs(adj,v,order,parent);
        }
    }
    order.push_back(source);
}

pair<vector<int>,vector<int>>full_dfs(vector<vector<int>>&adj){
    int vertex_count=adj.size();
    vector<int>parent(vertex_count,-1);
    vector<int>order;                   //dfs and full dfs will be same if with one vertex everything is possible
    for(int v=0;v<vertex_count;v++){
        if(parent[v]==-1){
            parent[v]=v;
            dfs(adj,v,order,parent);
        }
    }
    return make_pair(parent,order);
}
int main()
{
vector<vector<int>> adj = {{1,2},{0,3,4},{0,5},{1},{1,5},{2,4}};    
int vertex=adj.size();
    vector<int>parent(vertex,-1);
    vector<int>order;     //order vector is telling the sequence in which vertices finishing their DFS traversal
// dfs(adj,0,order,parent);
// cout<<"parent is in this way:"<<" ";
// for(int i:parent){
//     cout<<i<<" ";
// }
// cout<<endl;
// cout<<"order is in this way:"<<" ";
// for(int i:order){
//     cout<<i<<" ";
// }
pair<vector<int>,vector<int>>result=full_dfs(adj);
cout<<"parent of the pair is";
for(int i:result.first){
    cout<<i<<" ";
}
cout<<"order of the pair is";
for(int i:result.second){
    cout<<i<<" ";
}

 return 0;
}