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

Graph Transpose(Graph g){
    Graph result = Graph(g.vertices);
    vector<vector<int>> list = g.adj;

    for (int i=0; i<g.vertices; i++){
        for (int j=0; j<list[i].size(); j++){
            addEdge(result, list[i][j], i);
        }
    }

    return result;
}

void DFS2(Graph g, int u, vector<int> &scc, vector<bool> &visited, int SCCcounter){
    visited[u]=true;
    scc[u]=SCCcounter;
    
    vector<vector<int>> list = g.adj;
    for (int v=0; v<list[u].size(); v++){
        if (visited[list[u][v]] == false){
            DFS2(g, list[u][v], scc, visited, SCCcounter);
        }
    }
}

void printVector2D(vector<vector<int>> arr){
    for (int i=0; i<arr.size(); i++){
        cout<<i<<"-> ";
        for (int j=0; j<arr[i].size(); j++){
            cout<<arr[i][j]<<" ";
        }
        cout<<endl;
    }
}

vector<int> stronglyConnectedComponents(Graph g){
    vector<int> results = recursiveDFS(g);
    //printVector(results);
    vector<int> order = topological_sort(results);

    int n = g.vertices;
    Graph transpose(n);
    transpose = Transpose(g);

    //printVector2D(transpose.adj);


    vector<int> scc(n);
    vector<bool> visited(n);

    for (int i=0; i<n; i++){
        visited[i]=false;
    }

    int SCCcounter= 0;

    //iterate over order list obtained after topological sort
    for (int i=0; i<n; i++){
        if (visited[order[i]]== false){
            SCCcounter++;
            //cout<<SCCcounter<<endl;
            DFS2(transpose, order[i], scc, visited, SCCcounter);
        }
    }

    //printVector(order);
    return scc;
}

int main(){
    Graph g= Graph(5);
    addEdge(g, 0, 1);
    addEdge(g, 0, 2);
    addEdge(g, 1, 3);
    addEdge(g, 2, 4);
    addEdge(g, 4, 1);
    addEdge(g, 1, 2);
    addEdge(g, 4, 3);

    vector<int> results = stronglyConnectedComponents(g);
    printVector(results);
}