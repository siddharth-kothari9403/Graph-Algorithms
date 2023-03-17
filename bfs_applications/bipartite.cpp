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
    g.adj[e].push_back(s);
}

bool Bipartite(struct Graph g){
    int n = g.vertices;
    vector<vector<int>> list = g.adj;
    vector<bool> visited(n);
    vector<int> level(n);
    for (int i=0; i<n; i++){
        level[i]=-1;
    }
    
    for (int s=0; s<g.vertices; s++){      
        if (visited[s]==false){
            queue<int> q;
            q.push(s); level[s]=0;

            while (!q.empty()){
                int u = q.front();
                q.pop();
                for (int v=0; v<list[u].size(); v++){
                    if (level[list[u][v]] < 0){
                        q.push(list[u][v]);
                        level[list[u][v]]= level[u]+1;
                        visited[list[u][v]] = true;
                    }
                }
            }
        }
    }

    for (int i=0; i<n; i++){
        for (int j=0; j<list[i].size(); j++){
            if (level[i]%2 == level[list[i][j]]%2){
                return false;
            }
        }
    }
    return true; 
}

int main(){
    Graph g = Graph(4);
    addEdge(g, 0, 1);
    addEdge(g, 2, 1);
    addEdge(g, 2, 3);
    addEdge(g, 3, 0);

    Graph g1= Graph(3);
    addEdge(g1, 0, 1);
    addEdge(g1, 1, 2);
    addEdge(g1, 2, 0);

    Graph g2= Graph(3);
    addEdge(g2, 0, 1);
    addEdge(g2, 1, 2);


    cout<<Bipartite(g)<<endl;
    cout<<Bipartite(g1)<<endl;
    cout<<Bipartite(g2)<<endl;
}