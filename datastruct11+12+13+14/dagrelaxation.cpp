#include<iostream>
#include<utility>
#include<vector>
#include<queue>
using namespace std;
void dfs(const vector<vector<pair<int,int>>>&adj,int source,vector<bool>&visited,vector<int>&order){
    visited[source]=true;
    for(auto neighbour:adj[source]){
        int v=neighbour.first;
        if(!visited[v]){
            dfs(adj,v,visited,order);
        }
    }
    order.push_back(source);
}

void try_to_relax(vector<int>&d,vector<int>&parent,int u,int v,int weight){
    if(d[v]>d[u]+weight){
        d[v]=d[u]+weight;
        parent[v]=u;
    }
}

pair<vector<int>,vector<int>>dagrelaxation(const vector<vector<pair<int,int>>>&adj,int source){
    int n=adj.size();
    vector<int>order;
    vector<bool>visited(n,false);
    vector<int>d(n,__INT32_MAX__);
    vector<int>parent(n,-1);
    d[source]=0;
    parent[source]=source;
    //for getting in topological sort
    for(int i=0;i<n;i++){
        if(!visited[i]){
            dfs(adj,i,visited,order);
        }
    }
    reverse(order.begin(),order.end());
    for(int u:order){
        for(auto neighbour:adj[u]){
            int v=neighbour.first;
            int weight=neighbour.second;
            try_to_relax(d,parent,u,v,weight);  //relax edges from u to v
        }
    }
    return{d,parent};   //return the shortest path and parent pointers 
}


pair<vector<int>,vector<int>>belllman_ford(vector<vector<pair<int,int>>>&adj,int source){
    int vertices=adj.size();
    vector<int>d(vertices,__INT_MAX__);  //for writing the shortest path estimates
    vector<int>parent(vertices,-1);         //for maintaing parent pointers
    d[source]=0;
    parent[source]=source;

    //for relaxing v-1 vertices
    for(int i=0;i<vertices-1;i++){
        for(int u=0;u<vertices;u++){
            for(const auto neighbour:adj[u]){
                int v=neighbour.first;
                int weight=neighbour.second;
                try_to_relax(d,parent,u,v,weight);
            }
        }
    }

    //checking for negative weight cycles
    for(int u=0;u<vertices;u++){
        for(const auto neighbour:adj[u]){
            int v=neighbour.first;
            int weight=neighbour.second;
            if(d[u]!=__INT_MAX__ && d[v]>d[u]+weight){
                throw runtime_error("hey,there is a negative weight cycle");
            }
        }
    }
    return{d,parent};
}
struct compare{
    bool operator()(pair<int,int>a,pair<int,int>b){
        return a.second>b.second;
    }
};

pair<vector<int>,vector<int>>dijkstra(vector<vector<pair<int,int>>>&adj,int source){
    int n=adj.size();
    vector<int>distance(n,__INT_MAX__);
    vector<int>parent(n,-1);
    distance[source]=0;
    parent[source]=source;
    priority_queue<pair<int,int>,vector<pair<int,int>>,compare>pq;
    for(int i=0;i<n;i++){
        pq.push({distance[i],i});
    }
    while(!pq.empty()){
        int u=pq.top().second;
        pq.pop();

        for(auto i:adj[u]){
            int weight=i.second;
            int vertex=i.first;
            if(distance[vertex]>distance[u]+weight){
                try_to_relax(distance,parent,u,vertex,weight);
                pq.push({distance[vertex],vertex});
            }
        }

    }
    return{distance,parent};
}
int main()
{
    vector<vector<pair<int,int>>>adj(5);
    adj[0].emplace_back(1,10);
    adj[0].emplace_back(3,3);
    adj[1].emplace_back(2,2);
    adj[1].emplace_back(3,1);
    adj[2].emplace_back(4,7);
    adj[3].emplace_back(2,8);
    adj[3].emplace_back(4,2);
    adj[3].emplace_back(1,4);
    adj[4].emplace_back(2,5);
    // adj[0].emplace_back(1,5);
    // adj[0].emplace_back(2,3);
    // adj[1].emplace_back(2,2);
    // adj[1].emplace_back(3,6);
    // adj[2].emplace_back(3,7);
    // adj[3].emplace_back(4,2);
    // adj[4].emplace_back(5,1);

    // auto result=dagrelaxation(adj,0);
    // vector<int>d=result.first;
    // vector<int>parent=result.second;
    // cout<<"the shortest distances are as follows";
    // for(auto distances:d){
    //     cout<<distances<<" ";
    // }
    // cout<<endl;
    // cout<<"the parent in that path are as follows";
    // for(auto previous:parent){
    //     cout<<previous<<" ";
    // }
    auto result=dijkstra(adj,0);
    vector<int>d=result.first;
    vector<int>parent=result.second;
    cout<<"the shortest distances are as follows";
    for(auto distances:d){
        cout<<distances<<" ";
    }
    cout<<endl;
    cout<<"the parent in that path are as follows";
    for(auto previous:parent){
        cout<<previous<<" ";
    }
 return 0;
}