#include<bits/stdc++.h>
using namespace std;

struct Graph {
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

void DFS(struct Graph g, int u, vector<int> &phi, vector<bool> &visited, vector<int> &discovery, vector<int> &finish, int &count){
    visited[u]=true;
    discovery[u]=count++;
    vector<vector<int>> list = g.adj;

    for (int v=0; v<list[u].size(); v++){
        if (visited[list[u][v]]==false){
            phi[list[u][v]]=u; DFS(g, list[u][v], phi, visited, discovery, finish, count);
        }
    }

    finish[u]=count++;
}


//DFSvisit function, starts from 0
vector<int> recursiveDFS(struct Graph g){
    int n = g.vertices;

    vector<int> phi(n), finish(n), discovery(n);
    vector<bool> visited(n);

    for (int i=0; i<n; i++){
        phi[i]=-2;
        discovery[i]=0; finish[i]=0; visited[i]=false;
    }

    int count = 1; 
    for (int i=0; i<n; i++){
        if (visited[i]==false){
            phi[i]=-1; DFS(g, i, phi, visited, discovery, finish, count);
        }
    }

    /*cout<<"Phi- "<<endl;
    printVector(phi);

    cout<<"Discovery- "<<endl;
    printVector(discovery);

    cout<<"Finished- "<<endl;
    printVector(finish); */

    return finish;
}

vector<int> topological_sort(vector<int> finish){
    vector<pair<int, int>> pairs;
    for (int i=0; i<finish.size(); i++){
        pair<int,int> temp = make_pair(finish[i], i);
        pairs.push_back(temp);
    }

    sort(pairs.begin(), pairs.end());
    vector<int> results(finish.size());
    for (int i=0; i<finish.size(); i++){
        results[i]=pairs[i].second;

    }

    reverse(results.begin(), results.end());

    return results;
}

int main(){
    Graph g= Graph(5);
    addEdge(g, 0, 1);
    addEdge(g, 0, 2);
    addEdge(g, 1, 3);
    addEdge(g, 2, 4);
    //addEdge(g, 4, 1);
    addEdge(g, 1, 2);
    addEdge(g, 4, 3);

    vector<int> results = recursiveDFS(g);
    vector<int> results1 = topological_sort(results);
    printVector(results1);
}
