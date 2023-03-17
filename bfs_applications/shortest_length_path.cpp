#include<bits/stdc++.h>
using namespace std;

struct Graph{
    int vertices;
    vector<vector<int>> adj;
    Graph(int n){
        vertices = n;
        vector<int> temp = {};
        adj.resize(n, temp);
    }
};

void printVector(vector<int> arr){
    for (int i=0; i<arr.size(); i++){
        cout<<arr[i]<<" ";
    }
    cout<<endl;
}

void addEdge(struct Graph &g, int s, int e){
    g.adj[s].push_back(e);
}

vector<int> shortest_length_path(struct Graph g, int s){
    int n= g.vertices;
    vector<vector<int>> list = g.adj;

    vector<int> phi(n), level(n);
    vector<bool> visited(n);

    for (int i =0 ; i<n; i++){
        phi[i]=-2; visited[i]=false;
        level[i]=INT_MAX;
    }

    queue<int> q;

    q.push(s);
    phi[s]=-1; visited[s]=true; level[s]=0;

    while (!q.empty()){
        int u = q.front();
        q.pop();
        for (int v=0; v<list[u].size(); v++){
            if (visited[list[u][v]]==false){
                q.push(list[u][v]);
                phi[list[u][v]]= u;
                visited[list[u][v]]=true;
                level[list[u][v]]=level[u]+1;
            }
        }
    }

    cout<<"Phi- "<<endl;
    printVector(phi);

    return level;
}

int main(){
    Graph g = Graph(5);
    addEdge(g, 0, 1);
    addEdge(g, 0, 2);
    addEdge(g, 1, 2);
    addEdge(g, 2, 4);
    addEdge(g, 4, 1);
    addEdge(g, 1, 3);
    addEdge(g, 4, 3);
    
    vector<int> results = shortest_length_path(g, 0);
    printVector(results);
}