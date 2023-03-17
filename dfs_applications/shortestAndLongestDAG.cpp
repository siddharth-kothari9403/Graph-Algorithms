#include<bits/stdc++.h>
using namespace std;

struct Graph{
    int vertices;
    vector<vector<pair<int, int>>> adj;
    Graph(int n){
        vertices = n;
        vector<pair<int, int>> temp = {};
        adj.resize(n, temp);
    }
};

void printVector(vector<int> arr){
    for (int i=0; i<arr.size(); i++){
        cout<<arr[i]<<" ";
    }
    cout<<endl;
}

void addEdge(struct Graph &g, int s, int e, int weight){
    g.adj[s].push_back(make_pair(e, weight));
}

void DFS(struct Graph g, int u, vector<int> &phi, vector<bool> &visited, vector<int> &discovery, vector<int> &finish, int &count){
    visited[u]=true;
    discovery[u]=count++;
    vector<vector<pair<int, int>>> list = g.adj;

    for (int v=0; v<list[u].size(); v++){
        if (visited[list[u][v].first]==false){
            phi[list[u][v].first]=u; DFS(g, list[u][v].first, phi, visited, discovery, finish, count);
        }
    }

    finish[u]=count++;
}

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

pair<vector<int>, vector<int>> paths(Graph g, vector<int> order, int s){
    int n = g.vertices;
    vector<int> longest(n), shortest(n);

    vector<int> phi1(n), phi2(n);
    for (int i=0; i<n; i++){
        longest[i]=INT_MIN; shortest[i]=INT_MAX;
        phi1[i]=-2; phi2[i]=-2;
    }

    longest[s]= 0; shortest[s]=0; phi1[s]=-1; phi2[s]=-1;

    vector<vector<pair<int, int>>> list = g.adj;
    for (int i=0; i<n; i++){
        int u = order[i];
        for (int v=0; v<list[u].size(); v++){
            if (shortest[list[u][v].first] > shortest[u]+ list[u][v].second){
                shortest[list[u][v].first] = shortest[u]+ list[u][v].second;
                phi1[list[u][v].first] = u;
            }

            if (longest[list[u][v].first] < longest[u]+ list[u][v].second){
                longest[list[u][v].first] = longest[u]+ list[u][v].second;
                phi2[list[u][v].first] = u;
            }
        }
    }

    cout<<"Phi1- "<<endl;
    printVector(phi1);

    cout<<"Phi2- "<<endl;
    printVector(phi2);

    return make_pair(shortest, longest);
}

int main(){
    Graph g= Graph(5);
    addEdge(g, 0, 1, 2);
    addEdge(g, 0, 2,-4);
    addEdge(g, 1, 3, 8);
    addEdge(g, 2, 4, -1);
    //addEdge(g, 4, 1);
    addEdge(g, 1, 2, 3);
    addEdge(g, 4, 3, 5);

    vector<int> results = recursiveDFS(g);
    vector<int> results1 = topological_sort(results);

    //printVector(results1);
    pair<vector<int> , vector<int>> answer = paths(g, results1, 0); 
    printVector(answer.first);
    printVector(answer.second);
}