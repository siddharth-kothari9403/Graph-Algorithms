//using edge list

#include <bits/stdc++.h>
using namespace std;

struct Graph{
    int vertices;
    vector<pair<int,int>> adj;
    Graph(int v){
        vertices = v;
        adj = {};
    }
};

void addEdge(struct Graph &g, int s, int e){
    g.adj.push_back(make_pair(s,e));
}

void bfs(struct Graph g, int s){
    vector<bool> visited;
    vector<int> phi;

    int n = g.vertices;
    vector<pair<int,int>> list = g.adj;

    queue<int> q;
    for (int i=0; i<n; i++){
        phi.push_back(-2);
        visited.push_back(false);
    }

    q.push(s);
    phi[s]= -1;
    visited[s]= true;

    while (!q.empty()){
        int u= q.front();
        cout<<u<<" ";
        q.pop();
        for (int i=0; i<list.size(); i++){
            if (list[i].first == u){
                int v = list[i].second;
                if (visited[v]==false){
                    q.push(v);
                    phi[v]= u;
                    visited[v]= true;
                }
            }
        }
    }
    cout<<endl;
}


int main(){
    Graph g = Graph(4);
    addEdge(g,0,1);
    addEdge(g,0,2);
    addEdge(g,1,2);
    addEdge(g,2,0);
    addEdge(g,2,3);

    bfs(g,2);
}